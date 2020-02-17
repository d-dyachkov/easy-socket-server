#ifndef LAB1__SERVER_HPP_
#define LAB1__SERVER_HPP_

#include "config.hpp"
#include "server.hpp"

namespace easy_socket {
class sync_server : public server {
 protected:
  virtual void connection_handler(int socket) const noexcept = 0;
 public:
  using server::server;
  void start() const final;
};
}

#endif //LAB1__SERVER_HPP_
