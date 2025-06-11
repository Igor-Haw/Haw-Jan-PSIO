#include "Blackjack.h"
#include <cstdlib>

Blackjack::Blackjack(sf::Font& font)
    : font(font), gameStarted(false), playerStand(false), dealerStand(false),
    betAmount(0), playerTotal(0), dealerTotal(0) {

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

    playerText.setFont(font);
    playerText.setCharacterSize(24);
    playerText.setFillColor(sf::Color::White);
    playerText.setPosition(50, 100);

    dealerText.setFont(font);
    dealerText.setCharacterSize(24);
    dealerText.setFillColor(sf::Color::White);
    dealerText.setPosition(50, 150);

    resultText.setFont(font);
    resultText.setCharacterSize(30);
    resultText.setFillColor(sf::Color::Yellow);
    resultText.setPosition(300, 300);

    hitButton = Button(sf::Vector2f(50, 400), sf::Vector2f(150, 50), "Dobierz", font);
    standButton = Button(sf::Vector2f(250, 400), sf::Vector2f(150, 50), "Nie dobieraj", font);
    backButton = Button(sf::Vector2f(450, 400), sf::Vector2f(150, 50), "Powrot", font);
}

void Blackjack::startGame(int bet) {
    betAmount = bet;
    playerCards.clear();
    dealerCards.clear();
    playerTotal = 0;
    dealerTotal = 0;
    gameStarted = true;
    playerStand = false;
    dealerStand = false;
            resultChecked = false;

    hitPlayer();
    hitDealer();
    hitPlayer();
    hitDealer();

    updateTexts();
}

void Blackjack::hitPlayer() {
    int card = rand() % 10 + 1;
    playerCards.push_back(card);
    playerTotal += card;
}

void Blackjack::hitDealer() {
    int card = rand() % 10 + 1;
    dealerCards.push_back(card);
    dealerTotal += card;
}

void Blackjack::updateTexts() {
    betText.setString("Zaklad: " + std::to_string(betAmount)+"$");

    std::string playerStr = "Gracz: ";
    for (int card : playerCards) playerStr += std::to_string(card) + " ";
    playerStr += "(" + std::to_string(playerTotal) + ")";
    playerText.setString(playerStr);

    std::string dealerStr = "Krupier: ";
    if (!playerStand && !dealerStand) {
        dealerStr += std::to_string(dealerCards[0]) + " ?";
    } else {
        for (int card : dealerCards) dealerStr += std::to_string(card) + " ";
        dealerStr += "(" + std::to_string(dealerTotal) + ")";
    }
    dealerText.setString(dealerStr);
}

void Blackjack::checkResult() {
    if (playerTotal > 21) {
        result = "Fura! Przegrales " + std::to_string(betAmount)+"$";
        moneyChange = -betAmount;
    } else if (dealerTotal > 21) {
        result = "Wygrales " + std::to_string(betAmount)+"$";
        moneyChange = betAmount;
    } else if (playerTotal > dealerTotal) {
        result = "Wygrales " + std::to_string(betAmount)+"$";
        moneyChange = betAmount;
    } else if (playerTotal < dealerTotal) {
        result = "Przegrales " + std::to_string(betAmount)+"$";
        moneyChange = -betAmount;
    } else {
        result = "Remis!";
        moneyChange = 0;
    }
    resultText.setString(result);
}

void Blackjack::finalizeRound(int& money) {
    if (!resultChecked) {
        checkResult();
        money += moneyChange;
        resultChecked = true;
    }
}

void Blackjack::update(sf::RenderWindow& window, int& money) {
    if (!gameStarted) return;

    if (playerStand && !dealerStand) {
        if (dealerTotal < 17) {
            hitDealer();
        } else {
            dealerStand = true;

            finalizeRound(money);
        }
        updateTexts();
    }

    hitButton.setColor(hitButton.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
    standButton.setColor(standButton.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
    backButton.setColor(backButton.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
}

void Blackjack::handleEvent(sf::Event& event, sf::RenderWindow& window, int& money) {
    if (!gameStarted) return;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (hitButton.isClicked(event, window) && !playerStand) {
            hitPlayer();
            if (playerTotal >= 21) {
                playerStand = true;

                finalizeRound(money);
            }
            updateTexts();
        }

        if (standButton.isClicked(event, window) && !playerStand) {
            playerStand = true;
            while (dealerTotal < 17) hitDealer();
            dealerStand = true;

            finalizeRound(money);
            updateTexts();
        }

        if (backButton.isClicked(event, window)) {
            gameStarted = false;
        }
    }
}

void Blackjack::draw(sf::RenderWindow& window) {
    if (!gameStarted) return;

    window.draw(backgroundSprite);
    window.draw(betText);
    window.draw(playerText);
    window.draw(dealerText);

    if (playerStand && dealerStand) window.draw(resultText);

    hitButton.draw(window);
    standButton.draw(window);
    backButton.draw(window);
}

bool Blackjack::isActive() const {
    return gameStarted;
}
