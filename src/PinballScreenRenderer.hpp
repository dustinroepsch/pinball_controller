#ifndef PINBALL_SCREEN_RENDERER
#define PINBALL_SCREEN_RENDERER

#include <SFML/Graphics.hpp>
#include "boost/asio.hpp"
#include <cstdint>

class PinballScreenRenderer
{
  public:
    PinballScreenRenderer();
    void render(sf::RenderWindow &renderWindow);
    void update(sf::Time deltaTime);

  private:
    int fetch_arduino_state(uint8_t getter_code);
    void set_arduino_state(uint8_t setter_code);
    void check_judge(bool &judge_has_been_hit, uint8_t getter_code, uint8_t setter_code, double & image_timeout);

    void checkSensors();
    
    sf::Texture frameTexture;
    sf::Texture scoreBoardTexture;
    sf::Texture judge1;
    sf::Texture judge2;
    sf::Texture judge3;

    sf::Font font;
    int carterScore;
    int reaganScore;

    bool judge1_hit;
    bool judge2_hit;
    bool judge3_hit;

    double judge1_image_timeout_secs;
    double judge2_image_timeout_secs;
    double judge3_image_timeout_secs;

    int num_times_all_judges_hit;


    //serial comm

    boost::asio::io_context io_context;
    boost::asio::serial_port serial;
    boost::asio::serial_port_base::baud_rate BAUD;
    boost::asio::serial_port_base::flow_control FLOW;
    boost::asio::serial_port_base::parity PARITY;
    boost::asio::serial_port_base::stop_bits STOP;
};

#endif