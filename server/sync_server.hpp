#ifndef LAB1__SERVER_HPP_
#define LAB1__SERVER_HPP_

#include "config.hpp"

namespace easy_socket {
class sync_server {
  mutable int m_socket_descriptor = 0;
  config m_config = {};
 protected:
  void close_listener() const noexcept;
  virtual void connection_handler(int socket) const noexcept = 0;
 public:
  sync_server() = default;
  explicit sync_server(config &&config) : m_config{config} {}
  explicit sync_server(const config &config) : m_config{config} {}
  virtual void start() const final;
  virtual ~sync_server();
};
}

/*
 * Описать клиента: у него есть собственный сокет, у него есть команды получить сообщение и послать это сообщение
 */

#endif //LAB1__SERVER_HPP_
