/*#ifndef CASINO_H
#define CASINO_H

#pragma once

#include <SFML/Graphics.hpp>
#include "button.h"
#include "blackjack.h"
#include "roulette.h"
#include "slots.h"

class Casino
{
public:
    Casino(sf::Font& font);

    void start(int initialMoney);
    void update(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    bool isActive() const;
    int getMoney() const;

private:
    void updateTexts();

    sf::Font& font;
    bool active;
    int money;
    int currentBet;

    sf::Text betText;
    sf::Text moneyText;
    sf::Text betInput;

    Button blackjackButton;
    Button rouletteButton;
    Button slotsButton;
    Button backButton;

    Blackjack blackjack;
    Roulette roulette;
    Slots slots;
};

#endif // CASINO_H*/
#ifndef CASINO_H
#define CASINO_H

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "button.h"
#include "blackjack.h"
#include "roulette.h"
#include "slots.h"
#include "minigame.h" // <-- klasa bazowa

class Casino {
public:
    Casino(sf::Font& font);

    void start(int initialMoney);
    void update(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    bool isActive() const;
    int getMoney() const;

private:
    void updateTexts();

    sf::Font& font;
    bool active;
    int money;
    int currentBet;

    // Teksty
    sf::Text betText;
    sf::Text moneyText;
    sf::Text betInput;

    // Przycisk powrotu
    Button backButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Gry
    Blackjack blackjack;
    Roulette roulette;
    Slots slots;

    MiniGame* currentGame;  // <-- tu trzymamy aktualną grę

    // Przycisk do każdej gry
    std::map<std::string, Button> gameButtons;
};

#endif // CASINO_H
