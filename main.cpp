#include <iostream>
#include <SFML/Graphics.hpp>
// #include <Text.hpp>
#include <cstdint>
#include "src/PinballScreenRenderer.hpp"
#include "boost/asio.hpp"

// #include "src/ScreenConstants.h"

int main()
{


    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Pinball Game", sf::Style::Fullscreen);
    // sf::RenderWindow window(sf::VideoMode(800, 480), "Pinball Game");


    sf::Clock deltaClock;

    PinballScreenRenderer pinball;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        pinball.update(deltaClock.restart());
        pinball.render(window);
        window.display();
    }

    return 0;
}