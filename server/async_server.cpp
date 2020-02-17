#include "async_server.hpp"
#include "details.hpp"
#include <netinet/in.h>
#include <unistd.h>
#include <exception>
#include <iostream>

using namespace easy_socket;

void async_server::start() const {
  listen();
  auto listener = get_listener();
  fd_set cset{}, rset{};
  FD_SET(listener, &cset);
  int high_bound = listener;
  while (true) {
    memcpy(&rset, &cset, sizeof(cset));
    auto r = select(high_bound + 1, &rset, nullptr, nullptr, nullptr);
    if (FD_ISSET(listener, &rset)) {
      auto client = accept(listener, nullptr, nullptr);
      FD_SET(client, &cset);
      high_bound = std::max(high_bound, client);
      std::cout << "Open: " << client << std::endl;
    }
    for (auto sock = listener + 1; sock <= high_bound; ++sock) {
      if (!FD_ISSET(sock, &rset))
        continue;
      int i;
      switch (recv(sock, &i, sizeof(i), 0)) {
        case -1: break;
        case 0: {
          std::cout << "Close: " << sock << std::endl;
          FD_CLR(sock, &cset);
          close(sock);
          while (high_bound != listener && !FD_ISSET(high_bound, &cset))
            --high_bound;
        }
          break;
        default:std::cout << "Received: " << i << " [" << sock << "]" << std::endl;
      }
    }
  }
}