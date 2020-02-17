#include "sync_server.hpp"
#include "details.hpp"
#include <sys/socket.h>
#include <netinet/in.h> //INADDR_ANY
#include <unistd.h>
#include <iostream>

using namespace easy_socket;

void sync_server::start() const {
  listen();
  auto listener = get_listener();
  while (true) {//todo: change condition
    auto client_socket = accept(listener, nullptr, nullptr);
    connection_handler(client_socket);
  }
}