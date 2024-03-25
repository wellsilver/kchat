#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

void run(bool *active) {
  sf::RenderWindow window(sf::VideoMode(640, 480, 32), "KChat");
  sf::Event a;
  while (*active) {
    sf::Event p;
    window.pollEvent(p);
    


    window.display();
  }
}