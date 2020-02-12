#include <getopt.h>
#include <string>
#include <iostream>
#include "config.hpp"

using namespace easy_socket;

config config::parse(int argc, char **argv) {
  if (argc < 2)
    return config();
  static const option options[] = {
      {"port", required_argument, nullptr, 'p'},
      {"queue", required_argument, nullptr, 'q'},
      {"help", no_argument, nullptr, 'h'},
  };
  config config{};
  int op;
  while ((op = getopt_long(argc, argv, "p:q:h", options, nullptr)) != -1) {
    switch (op) {
      case 'p': config.port = std::stoi(optarg);
        break;
      case 'q': config.connection_queue_size = std::stoi(optarg);
        break;
      case 'h':
        std::cout << "--port, -p [PORT] - server port, default random" << std::endl
                  << "--queue, -q [SIZE] - queue size, default max" << std::endl;
        break;
      default:break;
    }
  }
  return config;
}
