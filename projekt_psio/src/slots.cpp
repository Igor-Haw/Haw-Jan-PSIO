#include "Slots.h"
#include <cstdlib>

Slots::Slots(sf::Font& font)
    : font(font), gameStarted(false), spinning(false), spinFrame(0) {
    betAmount = 0;

    betText.setFont(font);
    betText.setCharacterSize(24);
    betText.setFillColor(sf::Color::White);
    betText.setPosition(50, 50);

    backgroundTexture.loadFromFile("menu_bg.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        800.f / backgroundTexture.getSize().x,
        600.f / backgroundTexture.getSize().y
        );

    resultText.setFont(font);
    resultText.setCharacterSize(30);
    resultText.setFillColor(sf::Color::Yellow);
    resultText.setPosition(150,125);

    spinButton = Button(sf::Vector2f(300, 400), sf::Vector2f(150, 50), "Zakrec", font);
    backButton = Button(sf::Vector2f(450, 400), sf::Vector2f(150, 50), "Powrot", font);

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
    for (int i = 0; i < 3; ++i) {
        stopped[i] = false;
        stopFrames[i] = 30 + i * 15;
    }
    updateTexts();
}

void Slots::updateTexts() {
    betText.setString("Zaklad: " + std::to_string(betAmount)+"$");
}

void Slots::spin() {
    if (spinning) return;

    spinning = true;
    spinFrame = 0;
    resultShown = false;

    for (int i = 0; i < 3; ++i) {
        results[i] = rand() % symbols.size();
        stopped[i] = false;

    }
}

void Slots::checkResult() {
    if (results[0] == results[1] && results[1] == results[2]) {
        result = "JACKPOT! Wygrana " + std::to_string(betAmount * 10)+"$";
        moneyChange = betAmount * 10;
    } else if (results[0] == results[1] || results[1] == results[2] || results[0] == results[2]) {
        result = "WYGRALES! Dwa takie same! Wygrana " + std::to_string(betAmount * 2)+"$";
        moneyChange = betAmount * 2;
    } else {
        result = "PRZEGRANA! Przegrales " + std::to_string(betAmount)+"$";
        moneyChange = -betAmount;
    }

    resultText.setString(result);
    resultShown = true;
}

void Slots::update(sf::RenderWindow& window, int& money) {
    if (!gameStarted) return;

    // Animacja spinowania
    if (spinning) {
        spinFrame++;

        if (spinFrame % 5 == 0) {
            for (int i = 0; i < 3; ++i) {
                if (!stopped[i]) {
                    displayResults[i] = (displayResults[i] + 1) % symbols.size();
                }
            }
        }

        for (int i = 0; i < 3; ++i) {
            if (!stopped[i] && spinFrame >= stopFrames[i]) {
                displayResults[i] = results[i];
                stopped[i] = true;
            }
        }

        // Gdy wszystkie zatrzymane
        if (stopped[0] && stopped[1] && stopped[2]) {
            spinning = false;
            checkResult();
            money += moneyChange;
        }
    }

    // Kolorowanie przycisków
    spinButton.setColor(spinButton.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
    backButton.setColor(backButton.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
}

void Slots::handleEvent(sf::Event& event, sf::RenderWindow& window, int& money) {
    if (!gameStarted || spinning) return;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (spinButton.isMouseOver(window)) {
            spin();
        }

        if (backButton.isMouseOver(window)) {
            gameStarted = false;
        }
    }
}

void Slots::draw(sf::RenderWindow& window) {
    if (!gameStarted) return;

    window.draw(backgroundSprite);
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
