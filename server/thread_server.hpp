#ifndef LAB1_SERVER_THREAD_SERVER_HPP_
#define LAB1_SERVER_THREAD_SERVER_HPP_

#include "server.hpp"
#include <pthread.h>
#include <vector>

namespace easy_socket {
class thread_server final : public server {
  std::vector<pthread_t> m_threads;
  void connection_handler(int socket) const noexcept override;

 public:
  using server::server;
  ~thread_server() override;
};
}

#endif //LAB1_SERVER_THREAD_SERVER_HPP_
