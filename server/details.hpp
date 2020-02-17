#ifndef LAB1_SERVER_DETAILS_HPP_
#define LAB1_SERVER_DETAILS_HPP_

#include <sys/socket.h>
#include <netinet/in.h>
namespace easy_socket::details {
template<typename T>
T get_sockaddr_by_socket(int socket) {
  T addr{};
  socklen_t len = sizeof(addr);
  getsockname(socket, (sockaddr *) &addr, &len);
  return addr;
}

inline uint16_t get_port_by_socket(int socket) {
  auto addr = get_sockaddr_by_socket<sockaddr_in>(socket);
  return ntohs(addr.sin_port);
}
}

#endif //LAB1_SERVER_DETAILS_HPP_
