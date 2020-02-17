#ifndef LAB1_SERVER_FORK_SERVER_HPP_
#define LAB1_SERVER_FORK_SERVER_HPP_
#include "sync_server.hpp"

namespace easy_socket {
class fork_server : public sync_server {
  void connection_handler(int socket) const noexcept override;
 public:
  fork_server() : fork_server(config{}) {};
  explicit fork_server(config &&config) : fork_server(config) {};
  explicit fork_server(const config &config);
};
}

#endif //LAB1_SERVER_FORK_SERVER_HPP_
