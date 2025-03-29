#include "net.hpp"

#include <sys/socket.h>

extern bool end; // If the program is running or not, main.cpp
extern unsigned int tasks; // How many tasks are running

net::net() {
  fd = socket(0, 0, 0);
}

void net::tracker() {
  
}