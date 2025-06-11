#include "Casino.h"

Casino::Casino(sf::Font& font)
    : font(font), active(false), currentGame(nullptr),
    blackjack(font), roulette(font), slots(font) {

    gameButtons["Oczko"] = Button({200, 150}, {200, 50}, "Oczko", font);
    gameButtons["Ruletka"] = Button({200, 250}, {200, 50}, "Ruletka", font);
    gameButtons["Sloty"] = Button({200, 350}, {200, 50}, "Sloty", font);

    backButton = Button({200, 450}, {200, 50}, "Powrot", font);

    // Teksty
    betText.setFont(font);
    betText.setCharacterSize(24);
    betText.setFillColor(sf::Color::White);
    betText.setPosition(450, 50);

    moneyText.setFont(font);
    moneyText.setCharacterSize(24);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(450, 100);

    backgroundTexture.loadFromFile("menu_bg.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        800.f / backgroundTexture.getSize().x,
        600.f / backgroundTexture.getSize().y
        );

    betInput.setFont(font);
    betInput.setCharacterSize(24);
    betInput.setFillColor(sf::Color::White);
    betInput.setPosition(450, 150);
    betInput.setString("100");

    currentBet = 100;
    money = 1000;
}

void Casino::start(int initialMoney) {
    active = true;
    money = initialMoney;
    updateTexts();
}

void Casino::updateTexts() {
    moneyText.setString("Saldo: " + std::to_string(money)+"$");
    betText.setString("Zaklad: " + std::to_string(currentBet)+"$");
}

void Casino::update(sf::RenderWindow& window) {
    if (!active) return;

    if (currentGame && currentGame->isActive()) {
        currentGame->update(window, money);
        updateTexts();
    } else {
        // Highlight buttons
        for (auto& [name, button] : gameButtons) {
            button.setColor(button.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
        }
        backButton.setColor(backButton.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
    }
}

void Casino::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (!active) return;

    if (currentGame && currentGame->isActive()) {
        currentGame->handleEvent(event, window, money);
        updateTexts();
        return;
    }

    // Obsługa betInput
    static bool isTyping = false;

    if (event.type == sf::Event::MouseButtonPressed) {
        if (betInput.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            isTyping = true;
            betInput.setString("");
        } else {
            isTyping = false;
        }
    }

    if (isTyping && event.type == sf::Event::TextEntered) {
        std::string current = betInput.getString().toAnsiString();
        if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            current += static_cast<char>(event.text.unicode);
        } else if (event.text.unicode == 8 && !current.empty()) {
            current.pop_back();
        } else if (event.text.unicode == 13 && !current.empty()) {
            currentBet = std::stoi(current);
            isTyping = false;
        }
        betInput.setString(current);
        updateTexts();
    }

    // Start wybranej gry
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (!betInput.getString().isEmpty()) {
            currentBet = std::stoi(betInput.getString().toAnsiString());
            updateTexts();
        }

        if (currentBet > 0 && currentBet <= money) {
            if (gameButtons["Oczko"].isClicked(event, window)) {
                currentGame = &blackjack;
                currentGame->startGame(currentBet);
            } else if (gameButtons["Ruletka"].isClicked(event, window)) {
                currentGame = &roulette;
                currentGame->startGame(currentBet);
            } else if (gameButtons["Sloty"].isClicked(event, window)) {
                currentGame = &slots;
                currentGame->startGame(currentBet);
            }
        }

        if (backButton.isClicked(event, window)) {
            active = false;
        }
    }
}

void Casino::draw(sf::RenderWindow& window) {
    if (!active) return;

    if (currentGame && currentGame->isActive()) {
        currentGame->draw(window);
    } else {
        window.draw(backgroundSprite);
        window.draw(betText);
        window.draw(moneyText);
        window.draw(betInput);

        for (auto& [_, button] : gameButtons) {
            button.draw(window);
        }
        backButton.draw(window);
    }
}

bool Casino::isActive() const {
    return active;
}

int Casino::getMoney() const {
    return money;
}
