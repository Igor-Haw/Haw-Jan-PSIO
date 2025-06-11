#ifndef CLICKERGAME_H
#define CLICKERGAME_H

#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"

class ClickerGame {
public:
    ClickerGame(sf::Font& font);

    void startGame();
    void update(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool isActive() const;

    int getMoney() const;
    void setMoney(int amount);

private:
    void updateTexts();

    sf::Font& font;
    bool gameStarted;
    int money;
    int clickValue;

    sf::Text moneyText;
    sf::Text clickValueText;

    Button clickButton;
    Button upgradeButton;
    Button backButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

#endif // CLICKERGAME_H
