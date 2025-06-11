#ifndef CLICKERGAME_H
#define CLICKERGAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Button.h"

class ClickerGame {
public:
    explicit ClickerGame(sf::Font& font);
    void startGame();
    void update(sf::RenderWindow& window);
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
};

#endif
