#ifndef BLACKJACK_H
#define BLACKJACK_H

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Button.h"
#include "minigame.h"

class Blackjack :public MiniGame {
public:
    explicit Blackjack(sf::Font& font);

    void startGame(int bet);
    void update(sf::RenderWindow& window, int& money);
    void handleEvent(sf::Event& event, sf::RenderWindow& window, int& money);
    void draw(sf::RenderWindow& window);
    bool isActive() const;

private:
    void hitPlayer();
    void hitDealer();
    void updateTexts();
    void checkResult();
                    void finalizeRound(int& money);

    sf::Font& font;
    bool gameStarted;
    int betAmount;
    std::vector<int> playerCards;
    std::vector<int> dealerCards;
    int playerTotal;
    int dealerTotal;
    bool playerStand;
    bool dealerStand;
                    bool resultChecked;
    std::string result;
    int moneyChange;

    sf::Text betText;
    sf::Text playerText;
    sf::Text dealerText;
    sf::Text resultText;

    Button hitButton;
    Button standButton;
    Button backButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

#endif // BLACKJACK_H
