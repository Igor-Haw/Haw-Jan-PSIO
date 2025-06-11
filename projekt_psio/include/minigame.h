#ifndef MINIGAME_H
#define MINIGAME_H

#pragma once
#include <SFML/Graphics.hpp>

class MiniGame {
public:
    virtual ~MiniGame() = default;
    virtual void startGame(int bet) = 0;
    virtual void update(sf::RenderWindow& window, int& money) = 0;
    virtual void handleEvent(sf::Event& event, sf::RenderWindow& window, int& money) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual bool isActive() const = 0;
};

#endif // MINIGAME_H
