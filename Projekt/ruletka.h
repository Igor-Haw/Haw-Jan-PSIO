#ifndef RULETKA_H
#define RULETKA_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "button.h"

class Ruletka {
public:
    explicit Ruletka(sf::Font& font);

    void startGame(int bet);
    void updateTexts();
    void spin();
    void update(sf::RenderWindow& window, int& money);
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

#endif // RULETKA_H
