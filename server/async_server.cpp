#include "async_server.hpp"
#include "details.hpp"
#include <netinet/in.h>
#include <unistd.h>
#include <exception>
#include <iostream>

using namespace easy_socket;

void async_server::start() const {
  struct sockaddr_in bind_addr{
      .sin_family = AF_INET,
      .sin_port = htons(m_config.port),
      .sin_addr = {.s_addr = INADDR_ANY}
  };
  m_socket_descriptor = socket(AF_INET, SOCK_STREAM, m_config.proto);
  if (bind(m_socket_descriptor, (sockaddr *) &bind_addr, sizeof(bind_addr)) < 0) {
    throw std::runtime_error("Incorrect bind address");
  }
  listen(m_socket_descriptor, m_config.connection_queue_size);

  std::cout << "Server start on " << details::get_port_by_socket(m_socket_descriptor) << " port" << std::endl;
  fd_set cset{}, rset{};
  FD_SET(m_socket_descriptor, &cset);
  int high_bound = m_socket_descriptor;
  while (true) {
    memcpy(&rset, &cset, sizeof(cset));
    auto r = select(high_bound + 1, &rset, nullptr, nullptr, nullptr);
    if (FD_ISSET(m_socket_descriptor, &rset)) {
      auto client = accept(m_socket_descriptor, nullptr, nullptr);
      FD_SET(client, &cset);
      high_bound = std::max(high_bound, client);
      std::cout << "Open: " << client << std::endl;
    }
    for (auto sock = m_socket_descriptor + 1; sock <= high_bound; ++sock) {
      if (!FD_ISSET(sock, &rset))
        continue;
      int i;
      switch (recv(sock, &i, sizeof(i), 0)) {
        case -1: break;
        case 0: {
          std::cout << "Close: " << sock << std::endl;
          FD_CLR(sock, &cset);
          close(sock);
          while (high_bound != m_socket_descriptor && !FD_ISSET(high_bound, &cset))
            --high_bound;
        }
          break;
        default:std::cout << "Received: " << i << " [" << sock << "]" << std::endl;
      }
    }
  }
}

async_server::~async_server() {
  close_listener();
}

void async_server::close_listener() const noexcept {
  close(m_socket_descriptor);
}