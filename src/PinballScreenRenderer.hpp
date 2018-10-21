#ifndef PINBALL_SCREEN_RENDERER
#define PINBALL_SCREEN_RENDERER

#include <SFML/Graphics.hpp>

class PinballScreenRenderer
{
  public:
    PinballScreenRenderer();
    void render(sf::RenderWindow &renderWindow);
    void update(sf::Time deltaTime);
  private:
    sf::Texture frameTexture;
    sf::Texture scoreBoardTexture;
    sf::Font font;
    int carterScore;
    int reaganScore;
};

#endif