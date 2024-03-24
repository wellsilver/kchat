#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class graphic {
public:
  sf::Window window;

  graphic() {
    window = sf::RenderWindow(sf::VideoMode(640, 480, 32), "KChat");

  };
};