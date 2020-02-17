#ifndef LAB1_SERVER_ASYNC_SERVER_HPP_
#define LAB1_SERVER_ASYNC_SERVER_HPP_

#include "config.hpp"
#include "server.hpp"

namespace easy_socket {
class async_server : public server {
 public:
  using server::server;
  void start() const final;
};
}

#endif //LAB1_SERVER_ASYNC_SERVER_HPP_
