#ifndef LAB1_SERVER_CONFIG_HPP_
#define LAB1_SERVER_CONFIG_HPP_

#include <cstdint>
namespace easy_socket {
struct config {
  int connection_queue_size = 0;
  int proto = 0;
  uint16_t port = 0;

  static config parse(int argc, char **argv);
};
}
#endif //LAB1_SERVER_CONFIG_HPP_
