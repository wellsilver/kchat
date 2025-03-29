#include "net.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <thread>

extern bool end; // If the program is running or not, main.cpp
extern unsigned int tasks; // How many tasks are running

const int one=1;

net::net() {
  fd = socket(AF_INET6, SOCK_DGRAM, 0);
  int err = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
  struct sockaddr_in servaddr; 
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  servaddr.sin_port = htons(6070);
  servaddr.sin_family = AF_INET6;
  bind(fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
}

void net::starttracker() {
  std::thread(&net::tracker, this).detach();
}

void net::tracker() {

}