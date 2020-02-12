#include "server.hpp"
#include "details.hpp"
#include <sys/socket.h>
#include <netinet/in.h> //INADDR_ANY
#include <unistd.h>
#include <iostream>

using namespace easy_socket;

void server::start() const {
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
  while (true) {//todo: change condition
    auto client_socket = accept(m_socket_descriptor, nullptr, nullptr);
    connection_handler(client_socket);
  }
}
server::~server() {
  close(m_socket_descriptor);
}