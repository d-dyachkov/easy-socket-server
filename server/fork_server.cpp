#include "fork_server.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

using namespace easy_socket;
const auto incorrect_child_create = -1;

fork_server::fork_server(const config &config) : sync_server(config) {
#ifdef DEBUG
  signal(SIGCHLD, [](int) {
    int retcode;
    pid_t pid = wait3(&retcode, WNOHANG, nullptr);
    std::cout << "Process " << pid << " Return code: " << retcode << std::endl;
  });
#else
  signal(SIGCHLD, SIG_IGN);
#endif
}

void fork_server::connection_handler(int socket) const noexcept {
  switch (fork()) {
    case 0: close_listener();
      break;
    case incorrect_child_create: std::cerr << "Error fork!" << std::endl;
      [[fallthrough]];
    default: close(socket);
      return;
  }
  std::cout << "Handle connection (fork)" << std::endl;
  for (int i; recv(socket, &i, sizeof(i), 0);) {
    std::cout << "Received<" << socket << ">: " << i << std::endl;
  }
  close(socket);
  std::cout << "close" << std::endl;
  exit(0);
}
