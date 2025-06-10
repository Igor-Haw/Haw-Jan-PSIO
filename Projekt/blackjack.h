#ifndef BLACKJACK_H
#define BLACKJACK_H

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Button.h"

class Blackjack {
public:
    explicit Blackjack(sf::Font& font);

    void startGame(int bet);
    void update(sf::RenderWindow& window, int& money);
    void draw(sf::RenderWindow& window);
    bool isActive() const;

private:
    void hitPlayer();
    void hitDealer();
    void updateTexts();
    void checkResult();

    sf::Font& font;
    bool gameStarted;
    int betAmount;
    std::vector<int> playerCards;
    std::vector<int> dealerCards;
    int playerTotal;
    int dealerTotal;
    bool playerStand;
    bool dealerStand;
    std::string result;
    int moneyChange;

    sf::Text betText;
    sf::Text playerText;
    sf::Text dealerText;
    sf::Text resultText;

    Button hitButton;
    Button standButton;
    Button backButton;
};

#endif // BLACKJACK_H
