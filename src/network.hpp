#include <vector>
#include <SFML/Network.hpp>

void nrun(bool *active, sf::UdpSocket *server) {
  server->setBlocking(false);
  server->bind(64885);

  unsigned short port;
  sf::IpAddress ip;
  
  sf::Packet m;
  while (*active) {
    if (server->receive(m, ip, port) == sf::Socket::Status::Done) {

    }
  }
}