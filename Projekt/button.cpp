#include "button.h"

Button::Button() = default;

Button::Button(sf::Vector2f position,
               sf::Vector2f size,
               const std::string& text,
               sf::Font& font)
{
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(sf::Color(70, 70, 70));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::White);

    text_.setFont(font);
    text_.setString(text);
    text_.setCharacterSize(20);
    text_.setFillColor(sf::Color::White);

    // wyśrodkowanie napisu
    auto bounds = text_.getLocalBounds();
    text_.setPosition(
        position.x + (size.x - bounds.width) / 2.f - bounds.left,
        position.y + (size.y - bounds.height) / 2.f - bounds.top
        );
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(text_);
}

bool Button::isMouseOver(sf::RenderWindow& window)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return shape.getGlobalBounds().contains(mousePos);
}

void Button::setColor(const sf::Color& color)
{
    shape.setFillColor(color);
}
