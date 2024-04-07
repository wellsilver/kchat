#include <iostream>
#include <thread>
#include <chrono>

#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "graphics.hpp"
#include "network.hpp"

// tell the other instance to reactivate its gui
void notifyext() {
  sf::TcpSocket t;
  t.connect(sf::IpAddress::LocalHost, 64888);
  t.send(sf::Packet() << "gui");
  t.disconnect();
}

int main() {
  sf::UdpSocket server;
  sf::TcpListener local_server;
  if (local_server.listen(64888, sf::IpAddress::LocalHost) == sf::Socket::Status::Error) {notifyext();return -1;}
  
  sf::Clock time;

  bool gui_active = true;
  bool active = true;

  std::thread thrd_grphc(grun, &active, &gui_active);
  std::thread thrd_ntwrk(nrun, &active);
  // poll... forever....
  while (active) std::this_thread::sleep_for(std::chrono::seconds(1));

  thrd_grphc.join();
  thrd_ntwrk.join();

  return 0;
}