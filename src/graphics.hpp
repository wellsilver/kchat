#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

void grun(bool *active) {
  sf::RenderWindow window(sf::VideoMode(640, 480, 32), "KChat");
  sf::Event p;
  while (*active) {
    window.pollEvent(p);
    if (p.type == p.Closed) *active=0;


    window.display();
  }
}