#include "Slots.h"
#include <cstdlib>

Slots::Slots(sf::Font& font)
    : font(font), gameStarted(false), spinning(false), spinFrame(0) {
    betAmount = 0;

    betText.setFont(font);
    betText.setCharacterSize(24);
    betText.setFillColor(sf::Color::White);
    betText.setPosition(50, 50);

    resultText.setFont(font);
    resultText.setCharacterSize(30);
    resultText.setFillColor(sf::Color::Yellow);
    resultText.setPosition(300, 300);

    spinButton = Button(sf::Vector2f(300, 400), sf::Vector2f(150, 50), "Spin", font);
    backButton = Button(sf::Vector2f(450, 400), sf::Vector2f(150, 50), "Back", font);

    symbols = { "7", "BAR", "Cherry", "Lemon", "Orange", "Plum" };

    for (int i = 0; i < 3; ++i) {
        results[i] = 0;
        displayResults[i] = 0;
    }
}

void Slots::startGame(int bet) {
    betAmount = bet;
    gameStarted = true;
    spinning = false;
    spinFrame = 0;
    resultShown = false;
    updateTexts();
}

void Slots::updateTexts() {
    betText.setString("Bet: " + std::to_string(betAmount));
}

void Slots::spin() {
    if (spinning) return;

    spinning = true;
    spinFrame = 0;
    resultShown = false;

    for (int i = 0; i < 3; ++i) {
        results[i] = rand() % symbols.size();
        displayResults[i] = rand() % symbols.size();
    }
}

void Slots::checkResult() {
    if (results[0] == results[1] && results[1] == results[2]) {
        result = "JACKPOT! Won " + std::to_string(betAmount * 10);
        moneyChange = betAmount * 10;
    } else if (results[0] == results[1] || results[1] == results[2] || results[0] == results[2]) {
        result = "WIN! Two same! Won " + std::to_string(betAmount * 2);
        moneyChange = betAmount * 2;
    } else {
        result = "LOSE! Lost " + std::to_string(betAmount);
        moneyChange = -betAmount;
    }

    resultText.setString(result);
    resultShown = true;
}

void Slots::update(sf::RenderWindow& window, int& money) {
    if (!gameStarted) return;

    if (spinning) {
        spinFrame++;

        if (spinFrame % 5 == 0) {
            for (int i = 0; i < 3; ++i) {
                if (spinFrame < 30 + i * 10) {
                    displayResults[i] = (displayResults[i] + 1) % symbols.size();
                }
            }
        }

        if (spinFrame >= 60) {
            spinning = false;
            checkResult();
            money += moneyChange;
        }
    }

    if (spinButton.isMouseOver(window)) {
        spinButton.setColor(sf::Color(100, 100, 100));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !spinning) {
            spin();
        }
    } else {
        spinButton.setColor(sf::Color(70, 70, 70));
    }

    if (backButton.isMouseOver(window)) {
        backButton.setColor(sf::Color(100, 100, 100));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            gameStarted = false;
        }
    } else {
        backButton.setColor(sf::Color(70, 70, 70));
    }
}

void Slots::draw(sf::RenderWindow& window) {
    if (!gameStarted) return;

    window.draw(betText);

    for (int i = 0; i < 3; ++i) {
        sf::RectangleShape slot(sf::Vector2f(100, 150));
        slot.setPosition(200 + i * 120, 200);
        slot.setFillColor(sf::Color(50, 50, 50));
        slot.setOutlineThickness(2);
        slot.setOutlineColor(sf::Color::White);
        window.draw(slot);

        sf::Text symbol(symbols[displayResults[i]], font, 24);
        symbol.setPosition(230 + i * 120, 270);
        symbol.setFillColor(sf::Color::White);
        window.draw(symbol);
    }

    if (resultShown) {
        window.draw(resultText);
    }

    spinButton.draw(window);
    backButton.draw(window);
}

bool Slots::isActive() const {
    return gameStarted;
}
