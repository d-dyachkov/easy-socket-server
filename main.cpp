#include <iostream>
#include "server/thread_server.hpp"
#include "server/fork_server.hpp"
#include "server/async_server.hpp"

using namespace easy_socket;

int main(int argc, char **argv) try {
  auto config = config::parse(argc, argv);
  const server &server = thread_server(config);
  server.start();
  return 0;
} catch (std::exception&ex) {
  std::cerr << "Catching exception: " << ex.what() << std::endl;
  return 1;
}
