#include "PinballScreenRenderer.hpp"

PinballScreenRenderer::PinballScreenRenderer() : carterScore(0), reaganScore(0)
{
    frameTexture.loadFromFile("assets/frame.png");
    scoreBoardTexture.loadFromFile("assets/score_text.png");
    font.loadFromFile("assets/Lora-Regular.ttf");
}

void PinballScreenRenderer::update(sf::Time deltaTime) {
    static double elapsedSeconds = 0;
    elapsedSeconds += deltaTime.asSeconds();
    carterScore = static_cast<int>(elapsedSeconds);
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