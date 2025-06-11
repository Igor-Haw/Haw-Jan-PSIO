#ifndef BUTTON_H
#define BUTTON_H

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
    Button();

    Button(sf::Vector2f position,
           sf::Vector2f size,
           const std::string& text,
           sf::Font& font);

    void draw(sf::RenderWindow& window);

    bool isMouseOver(sf::RenderWindow& window);

    void setColor(const sf::Color& color);

    bool isClicked(sf::Event& event, sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
    sf::Text           text_;
};
#endif // BUTTON_H
