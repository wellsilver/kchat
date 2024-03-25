#include <iostream>
#include <thread>

#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "graphics.hpp"
#include "network.hpp"

int main() {
  sf::UdpSocket server;
  sf::Clock time;

  bool active = true;

  std::thread thrd_grphc(run, &active);

  return 0;
}