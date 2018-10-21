#include <iostream>
#include <SFML/Graphics.hpp>
// #include <Text.hpp>
#include <cstdint>
#include "src/PinballScreenRenderer.hpp"
#include "boost/asio.hpp"

// #include "src/ScreenConstants.h"

int main()
{
    // boost::asio::io_context io_context;
    // boost::asio::serial_port serial(io_context, "/dev/tty96B0");
    // boost::asio::serial_port_base::baud_rate BAUD(9600);
    // boost::asio::serial_port_base::flow_control FLOW(boost::asio::serial_port_base::flow_control::none);
    // boost::asio::serial_port_base::parity PARITY(boost::asio::serial_port_base::parity::none);
    // boost::asio::serial_port_base::stop_bits STOP(boost::asio::serial_port_base::stop_bits::one);

    // serial.set_option(BAUD);
    // serial.set_option(FLOW);
    // serial.set_option(PARITY);
    // serial.set_option(STOP);

    // sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Pinball Game", sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(800, 480), "Pinball Game");

    sf::Font font;

    font.loadFromFile("fonts/Roboto-Regular.ttf");

    sf::Clock deltaClock;
    // while (1)
    // {
    //     std::cout << "Writing " << ((int) b )<< std::endl;
    //     serial.write_some(boost::asio::buffer(&b, 1));
    //     boost::asio::read(serial, boost::asio::buffer(&b, 1));
    //     std::cout << b << std::endl;
    // }

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