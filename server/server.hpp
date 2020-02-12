#ifndef LAB1__SERVER_HPP_
#define LAB1__SERVER_HPP_

#include "config.hpp"

namespace easy_socket {
class server {
  mutable int m_socket_descriptor = 0;
  config m_config = {};
 protected:
  virtual void connection_handler(int socket) const noexcept = 0;
 public:
  server() = default;
  explicit server(config &&config) : m_config{config} {}
  explicit server(const config &config) : m_config{config} {}
  virtual void start() const final;
  virtual ~server();
};
}

/*
 * Описать клиента: у него есть собственный сокет, у него есть команды получить сообщение и послать это сообщение
 */

#endif //LAB1__SERVER_HPP_
