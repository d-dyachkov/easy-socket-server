#ifndef LAB1_SERVER_THREAD_SERVER_HPP_
#define LAB1_SERVER_THREAD_SERVER_HPP_

#include "sync_server.hpp"
#include <pthread.h>
#include <vector>

namespace easy_socket {
class thread_server final : public sync_server {
  mutable std::vector<pthread_t> m_threads;
  mutable pthread_mutex_t m_mutex{};
  void connection_handler(int socket) const noexcept override;

 public:
  using sync_server::sync_server;
  ~thread_server() override;
};
}

#endif //LAB1_SERVER_THREAD_SERVER_HPP_
