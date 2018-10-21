#include "PinballScreenRenderer.hpp"

#include "../shared/CommunicationConstants.h"

PinballScreenRenderer::PinballScreenRenderer()
    : carterScore(0), reaganScore(0), serial(io_context, "/dev/tty96B0"), BAUD(9600), FLOW(boost::asio::serial_port_base::flow_control::none), PARITY(boost::asio::serial_port_base::parity::none), STOP(boost::asio::serial_port_base::stop_bits::one), judge1_hit(false), judge2_hit(false), judge3_hit(false), judge1_image_timeout_secs(0), judge2_image_timeout_secs(0), judge3_image_timeout_secs(0), num_times_all_judges_hit(0), mediaTimer(0), patCoTimer(0)
{

    serial.set_option(BAUD);
    serial.set_option(FLOW);
    serial.set_option(PARITY);
    serial.set_option(STOP);

    frameTexture.loadFromFile("assets/frame.png");
    scoreBoardTexture.loadFromFile("assets/score_text.png");
    font.loadFromFile("assets/Lora-Regular.ttf");
    judge1.loadFromFile("assets/judge1.png");
    judge2.loadFromFile("assets/judge2.png");
    judge3.loadFromFile("assets/judge3.png");
}

int PinballScreenRenderer::fetch_arduino_state(uint8_t getter_code)
{
    serial.write_some(boost::asio::buffer(&getter_code, 1));
    uint8_t output;
    boost::asio::read(serial, boost::asio::buffer(&output, 1));
    return output;
}

void PinballScreenRenderer::set_arduino_state(uint8_t setter_code)
{
    serial.write_some(boost::asio::buffer(&setter_code, 1));
}

void PinballScreenRenderer::check_judge(bool &judge_has_been_hit, uint8_t getter_code, uint8_t setter_code, double &image_timeout)
{
    if (image_timeout == 0 && !judge_has_been_hit)
    {
        judge_has_been_hit = fetch_arduino_state(getter_code);
        if (judge_has_been_hit)
        {
            set_arduino_state(setter_code);
            image_timeout += 5;
            reaganScore += 5;

            if (judge1_hit && judge2_hit && judge3_hit)
            {
                reaganScore += 15;
                judge1_hit = false;
                judge2_hit = false;
                judge3_hit = false;
                set_arduino_state(Communication::UNSET_LIGHTS_JUDICIAL_O);
                set_arduino_state(Communication::UNSET_LIGHTS_JUDICIAL_1);
            }
        }
    }
}

void PinballScreenRenderer::checkMedia()
{
    static int numTimesMediaHit = 0;

    int hit = fetch_arduino_state(Communication::GET_MEDIA);

    if (hit && mediaTimer == 0)
    {
        mediaTimer += 1;
        numTimesMediaHit++;
        if (numTimesMediaHit % 3 == 0)
        {
            carterScore += 15;
        }
        else
        {
            reaganScore += 10;
        }
    }
}

void PinballScreenRenderer::checkPatCo()
{

    int hit = fetch_arduino_state(Communication::GET_PAT_CO);

    if (hit && patCoTimer == 0)
    {
        patCoTimer += 5;
        if (rand() % 2 == 0)
        {
            carterScore += 20;
        }
        else
        {
            reaganScore += 20;
        }
    }
}

void PinballScreenRenderer::checkSensors()
{
    check_judge(judge1_hit, Communication::GET_JUDICIAL_O, Communication::SET_LIGHTS_JUDICIAL_O, judge1_image_timeout_secs);
    check_judge(judge2_hit, Communication::GET_JUDICIAL_1, Communication::SET_LIGHTS_JUDICIAL_1, judge2_image_timeout_secs);
    check_judge(judge3_hit, Communication::GET_JUDICIAL_2, Communication::SET_LIGHTS_JUDICIAL_O, judge3_image_timeout_secs);

    checkMedia();
    checkPatCo();
}

void tickdown_timer(sf::Time deltaTime, double &timer)
{
    if (timer <= deltaTime.asSeconds())
    {
        timer = 0;
    }
    else
    {
        timer -= deltaTime.asSeconds();
    }

    //doubles are weird
    if (timer < 0)
    {
        timer = 0;
    }
}

void PinballScreenRenderer::update(sf::Time deltaTime)
{
    checkSensors();
    tickdown_timer(deltaTime, judge1_image_timeout_secs);
    tickdown_timer(deltaTime, judge2_image_timeout_secs);
    tickdown_timer(deltaTime, judge3_image_timeout_secs);
    tickdown_timer(deltaTime, mediaTimer);
    tickdown_timer(deltaTime, patCoTimer);
}

void render_texture(sf::RenderWindow &renderWindow, sf::Texture &texture)
{
    sf::Sprite sprite;
    sprite.setTexture(texture);
    renderWindow.draw(sprite);
}

void PinballScreenRenderer::render(sf::RenderWindow &renderWindow)
{
    render_texture(renderWindow, frameTexture);
    render_texture(renderWindow, scoreBoardTexture);

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

    sf::Text score;
    score.setFont(font);
    score.setFillColor(sf::Color::Red);
    score.setCharacterSize(50);
    score.setPosition({400, 300});
    score.setString(std::to_string(reaganScore - carterScore));

    if (judge1_image_timeout_secs > 0)
    {
        render_texture(renderWindow, judge1);
    }

    if (judge2_image_timeout_secs > 0)
    {
        render_texture(renderWindow, judge2);
    }

    if (judge3_image_timeout_secs > 0)
    {
        render_texture(renderWindow, judge3);
    }

    renderWindow.draw(reaganText);
    renderWindow.draw(carterText);
    renderWindow.draw(score);
}