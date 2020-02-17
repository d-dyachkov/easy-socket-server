#ifndef LAB1_SERVER_SERVER_HPP_
#define LAB1_SERVER_SERVER_HPP_

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include "config.hpp"
#include "details.hpp"

namespace easy_socket {
class server {
  mutable int m_socket_descriptor = 0;
  config m_config = {};
 protected:
  void listen() const {
    struct sockaddr_in bind_addr{
        .sin_family = AF_INET,
        .sin_port = htons(m_config.port),
        .sin_addr = {.s_addr = INADDR_ANY}
    };
    m_socket_descriptor = socket(AF_INET, SOCK_STREAM, m_config.proto);
    if (bind(m_socket_descriptor, (sockaddr *) &bind_addr, sizeof(bind_addr)) < 0) {
      throw std::runtime_error("Incorrect bind address");
    }
    ::listen(m_socket_descriptor, m_config.connection_queue_size);
    std::cout << "Server start on " << details::get_port_by_socket(m_socket_descriptor) << " port" << std::endl;
  }
  void close_listener() const noexcept {
    close(m_socket_descriptor);
  }
  auto get_listener() const noexcept {
    return m_socket_descriptor;
  }
 public:
  server() = default;
  explicit server(config &&config) : m_config{config} {}
  explicit server(const config &config) : m_config{config} {}
  virtual void start() const = 0;
  virtual ~server() {
    close_listener();
  }
};
}

#endif //LAB1_SERVER_SERVER_HPP_
