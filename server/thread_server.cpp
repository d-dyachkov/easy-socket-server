#include "thread_server.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
using namespace easy_socket;
void thread_server::connection_handler(int socket) const noexcept {
  pthread_t pid;
  pthread_create(&pid, nullptr, [](void *arg) -> void * {
    std::cout << "Handle connection (pthread)" << std::endl;
    auto socket = reinterpret_cast<int64_t>(arg);
    int i;
    while (recv(socket, &i, sizeof(i), 0)) {
      std::cout << "Received<" << socket << ">: " << i << std::endl;
    }
    close(socket);
    std::cout << "close" << std::endl;
    return nullptr;
  }, reinterpret_cast<void *>(socket));
}

thread_server::~thread_server() {
  for (const auto &pthread_id : m_threads) {
    pthread_join(pthread_id, nullptr);
  }
}
