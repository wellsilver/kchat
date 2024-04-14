#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <thread>

// thread to toggle guiactive when requested
void ensurerun(bool *active, sf::TcpListener *local_server, bool *guiactive) {
  sf::TcpSocket n;
  std::string recv;
  sf::Packet packet;
  while (*active) {
    local_server->accept(n);
    n.receive(packet);
    packet >> recv;
    if (recv == "gui") *guiactive = true;
  }
}

void grun(bool *active, sf::TcpListener *local_server, bool *guiactive) {
  std::thread(ensurerun, active, local_server, guiactive);
  while (*active) {
    if (*guiactive) {
      sf::RenderWindow window(sf::VideoMode(640, 480, 32), "KChat");
      sf::Event p;
      while (*guiactive) {
        window.pollEvent(p);
        if (p.type == p.Closed) *guiactive=0;


        window.display();
      }
      window.close();
    }
  }
}