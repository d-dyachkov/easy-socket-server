#include "thread_server.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
using namespace easy_socket;

struct server_context {
  pthread_mutex_t *mutex;
  int socket;
};

void thread_server::connection_handler(int socket) const noexcept {
  static bool mutex_init = [this]{
    pthread_mutex_init(&m_mutex, nullptr);
    return true;
  }();//todo: это хуево тк выполняется для всех инстансов 1 раз
  pthread_t tid;
  auto context = new server_context{&m_mutex, socket};
  pthread_create(&tid, nullptr, [](void *context_ptr) -> void * {
    if (context_ptr == nullptr)
      return nullptr;
    auto context = reinterpret_cast<server_context *>(context_ptr);
    std::cout << "Handle connection (pthread): " << context->socket << std::endl;
    for (int i; recv(context->socket, &i, sizeof(i), 0);) {
      pthread_mutex_lock(context->mutex);
      std::cout << "Received: " << i << " [" << context->socket << "]" << std::endl;
      pthread_mutex_unlock(context->mutex);
    }
    close(context->socket);
    std::cout << "close" << std::endl;
    delete context;
    return nullptr;
  }, context);
  m_threads.emplace_back(tid);
}

thread_server::~thread_server() {
  for (const auto &pthread_id : m_threads) {
    pthread_join(pthread_id, nullptr);
  }
  pthread_mutex_destroy(&m_mutex);
}
