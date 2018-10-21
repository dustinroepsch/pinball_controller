#ifndef PINBALL_SCREEN_RENDERER
#define PINBALL_SCREEN_RENDERER

#include <SFML/Graphics.hpp>
#include "boost/asio.hpp"

class PinballScreenRenderer
{
  public:
    PinballScreenRenderer();
    void render(sf::RenderWindow &renderWindow);
    void update(sf::Time deltaTime);

  private:
    int fetch_arduino_state(int getter_code);
    void checkSensors();
    
    sf::Texture frameTexture;
    sf::Texture scoreBoardTexture;
    sf::Font font;
    int carterScore;
    int reaganScore;

    //serial comm

    boost::asio::io_context io_context;
    boost::asio::serial_port serial;
    boost::asio::serial_port_base::baud_rate BAUD;
    boost::asio::serial_port_base::flow_control FLOW;
    boost::asio::serial_port_base::parity PARITY;
    boost::asio::serial_port_base::stop_bits STOP;
};

#endif