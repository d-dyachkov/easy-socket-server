#ifndef LAB1_SERVER_ASYNC_SERVER_HPP_
#define LAB1_SERVER_ASYNC_SERVER_HPP_

#include "config.hpp"

namespace easy_socket {
class async_server {
  mutable int m_socket_descriptor = 0;
  config m_config = {};
 protected:
  void close_listener() const noexcept;
 public:
  async_server() = default;
  explicit async_server(config &&config) : m_config{config} {}
  explicit async_server(const config &config) : m_config{config} {}
  virtual void start() const final;
  virtual ~async_server();
};
}

#endif //LAB1_SERVER_ASYNC_SERVER_HPP_
