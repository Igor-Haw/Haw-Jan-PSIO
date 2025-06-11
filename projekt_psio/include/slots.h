plicit#ifndef SLOTS_H
#define SLOTS_H

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Button.h"
#include "minigame.h"

class Slots :public MiniGame{
public:
    explicit Slots(sf::Font& font);

    void startGame(int bet);
    void update(sf::RenderWindow& window, int& money);
    void handleEvent(sf::Event& event, sf::RenderWindow& window, int& money);
    void draw(sf::RenderWindow& window);
    bool isActive() const;

private:
    void updateTexts();
    void spin();
    void checkResult();

    sf::Font& font;
    bool gameStarted;
    bool spinning;
    bool resultShown;
    int spinFrame;
    int betAmount;
    int results[3];
    int displayResults[3];
    int stopFrames[3];
    bool stopped[3];
    int moneyChange;
    std::vector<std::string> symbols;
    std::string result;

    sf::Text betText;
    sf::Text resultText;

    Button spinButton;
    Button backButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

#endif // SLOTS_H
