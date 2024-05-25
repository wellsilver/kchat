#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

void gui(bool *active, bool *guiactive) {
  sf::RenderWindow window(sf::VideoMode(480, 480, 32), "KChat");
  
  sf::Event p;
  while (*guiactive && *active) {
    while (window.pollEvent(p)) {
      if (p.type == p.Closed) *guiactive=0;
    }

    window.display();
  }
  window.close();
}

void grun(bool *active, bool *guiactive) {
  while (*active)
    if (*guiactive)
      gui(active, guiactive);
}