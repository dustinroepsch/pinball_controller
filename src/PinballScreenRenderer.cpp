#include "PinballScreenRenderer.hpp"


PinballScreenRenderer::PinballScreenRenderer()
    : carterScore(0), reaganScore(0), serial(io_context, "/dev/tty96B0"), BAUD(9600), FLOW(boost::asio::serial_port_base::flow_control::none), PARITY(boost::asio::serial_port_base::parity::none), STOP(boost::asio::serial_port_base::stop_bits::one)
{

    serial.set_option(BAUD);
    serial.set_option(FLOW);
    serial.set_option(PARITY);
    serial.set_option(STOP);

    frameTexture.loadFromFile("assets/frame.png");
    scoreBoardTexture.loadFromFile("assets/score_text.png");
    font.loadFromFile("assets/Lora-Regular.ttf");
}

int PinballScreenRenderer::fetch_arduino_state(uint8_t getter_code)
{
    serial.write_some(boost::asio::buffer(&getter_code, 1));
    uint8_t output;
    boost::asio::read(serial, boost::asio::buffer(&output, 1));
    return output;
}

void PinballScreenRenderer::checkSensors()
{
    carterScore = fetch_arduino_state(0);
    reaganScore = fetch_arduino_state(1);
}

void PinballScreenRenderer::update(sf::Time deltaTime)
{
    checkSensors();
}

void PinballScreenRenderer::render(sf::RenderWindow &renderWindow)
{
    sf::Sprite frameSprite;
    frameSprite.setTexture(frameTexture);

    sf::Sprite scoreSprite;
    scoreSprite.setTexture(scoreBoardTexture);

    sf::Text carterText;
    carterText.setFont(font);
    carterText.setFillColor(sf::Color::Blue);
    carterText.setCharacterSize(80);
    carterText.setPosition({300, 190});
    carterText.setString(std::to_string(carterScore));

    sf::Text reaganText;
    reaganText.setFont(font);
    reaganText.setFillColor(sf::Color::Red);
    reaganText.setCharacterSize(80);
    reaganText.setPosition({420, 190});
    reaganText.setString(std::to_string(reaganScore));

    renderWindow.draw(frameSprite);
    renderWindow.draw(scoreSprite);

    renderWindow.draw(reaganText);
    renderWindow.draw(carterText);
}