#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

void grun(bool *active, bool *guiactive) {
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