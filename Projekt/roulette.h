#ifndef ROULETTE_H
#define ROULETTE_H

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Button.h"

class Roulette {
public:
    explicit Roulette(sf::Font& font);

    void startGame(int bet);
    void updateTexts();
    void spin();
    void update(sf::RenderWindow& window, int& money);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window, int& money);
    void draw(sf::RenderWindow& window);

    [[nodiscard]] bool isActive() const;

private:
    sf::Font& font;
    bool gameStarted;
    bool resultShown;
    int betAmount;
    int selectedNumber;
    int selectedColor;
    int resultNumber;
    int resultColor;
    std::string result;
    int moneyChange;
    std::map<int, int> numberColors;
    sf::Text betText;
    sf::Text numberText;
    sf::Text colorText;
    sf::Text resultText;
    Button spinButton;
    Button backButton;
};

#endif // ROULETTE_H
