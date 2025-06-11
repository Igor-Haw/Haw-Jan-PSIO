#include "ClickerGame.h"

ClickerGame::ClickerGame(sf::Font& font) : font(font), gameStarted(false), money(0), clickValue(1) {
    moneyText.setFont(font);
    moneyText.setCharacterSize(36);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(50, 50);

    clickValueText.setFont(font);
    clickValueText.setCharacterSize(24);
    clickValueText.setFillColor(sf::Color::White);
    clickValueText.setPosition(50, 100);

    clickButton = Button(sf::Vector2f(300, 200), sf::Vector2f(200, 100), "CLICK!", font);
    upgradeButton = Button(sf::Vector2f(300, 350), sf::Vector2f(200, 50), "Upgrade (10)", font);
    backButton = Button(sf::Vector2f(300, 450), sf::Vector2f(200, 50), "Back", font);
}

void ClickerGame::startGame() {
    gameStarted = true;
    updateTexts();
}

void ClickerGame::updateTexts() {
    moneyText.setString("Money: " + std::to_string(money));
    clickValueText.setString("Click value: " + std::to_string(clickValue));
    upgradeButton = Button(sf::Vector2f(300, 350), sf::Vector2f(200, 50),
                           "Upgrade (" + std::to_string(10 * (clickValue)) + ")", font);
}

void ClickerGame::update(sf::RenderWindow& window) {
    if (gameStarted) {
        if (clickButton.isMouseOver(window)) {
            clickButton.setColor(sf::Color(100, 100, 100));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                money += clickValue;
                updateTexts();
            }
        } else {
            clickButton.setColor(sf::Color(70, 70, 70));
        }

        if (upgradeButton.isMouseOver(window)) {
            upgradeButton.setColor(sf::Color(100, 100, 100));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && money >= 10 * clickValue) {
                money -= 10 * clickValue;
                clickValue++;
                updateTexts();
            }
        } else {
            upgradeButton.setColor(sf::Color(70, 70, 70));
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
}

void ClickerGame::draw(sf::RenderWindow& window) {
    if (gameStarted) {
        window.draw(moneyText);
        window.draw(clickValueText);
        clickButton.draw(window);
        upgradeButton.draw(window);
        backButton.draw(window);
    }
}

bool ClickerGame::isActive() const {
    return gameStarted;
}

int ClickerGame::getMoney() const {
    return money;
}

void ClickerGame::setMoney(int amount) {
    money = amount;
    updateTexts();
}
