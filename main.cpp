#include <iostream>
#include <SFML/Graphics.hpp>
// #include <Text.hpp>
#include <cstdint>
#include "boost/asio.hpp"

// #include "src/ScreenConstants.h"

int main()
{
    boost::asio::io_context io_context;
    boost::asio::serial_port serial(io_context, "/dev/tty96B0");

    boost::asio::serial_port_base::baud_rate BAUD(9600);
    boost::asio::serial_port_base::flow_control FLOW(boost::asio::serial_port_base::flow_control::none);
    boost::asio::serial_port_base::parity PARITY(boost::asio::serial_port_base::parity::none);
    // serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );
    boost::asio::serial_port_base::stop_bits STOP(boost::asio::serial_port_base::stop_bits::one);

    serial.set_option(BAUD);
    serial.set_option(FLOW);
    serial.set_option(PARITY);
    serial.set_option(STOP);

    // sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Pinball Game", sf::Style::Fullscreen);
    // sf::Font font;

    // font.loadFromFile("fonts/Roboto-Regular.ttf");
    double i = 0;
    char b = 1;
    // sf::Clock deltaClock;
    while (1)
    {
        std::cout << "Writing " << ((int) b )<< std::endl;
        serial.write_some(boost::asio::buffer(&b, 1));
        boost::asio::read(serial, boost::asio::buffer(&b, 1));
        std::cout << b << std::endl;
    }

    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //         {
    //             window.close();
    //         }
    //     }
    //     window.clear(sf::Color::Black);

    //     sf::CircleShape octagon(sf::VideoMode::getDesktopMode().width / 6.0, 8);

    //     octagon.rotate(i);
    //     octagon.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2.0f, sf::VideoMode::getDesktopMode().height / 2.0f));
    //     uint8_t b << serial;
    //     std::string output = "Serial"s + b;
    //     sf::Text t(output, font);
    //     t.setFillColor(sf::Color::White);
    //     t.setPosition({20.0, 20.0});
    //     window.draw(t);
    //     octagon.setFillColor(sf::Color::Magenta);
    //     window.draw(octagon);
    //     window.display();

    //     i += deltaClock.restart().asSeconds() * 6;
    // }

    return 0;
}