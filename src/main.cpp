#include <iostream>
#include <thread>
#include <chrono>

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

  // poll... forever....
  while (active) {std::this_thread::sleep_for(std::chrono::seconds(1));}

  return 0;
}