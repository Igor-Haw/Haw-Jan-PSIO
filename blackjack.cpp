#include "Blackjack.h"
#include <cstdlib>

Blackjack::Blackjack(sf::Font& font)
    : font(font), gameStarted(false), playerStand(false), dealerStand(false),
    betAmount(0), playerTotal(0), dealerTotal(0) {

    betText.setFont(font);
    betText.setCharacterSize(24);
    betText.setFillColor(sf::Color::White);
    betText.setPosition(50, 50);

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

    hitButton = Button(sf::Vector2f(50, 400), sf::Vector2f(150, 50), "Hit", font);
    standButton = Button(sf::Vector2f(250, 400), sf::Vector2f(150, 50), "Stand", font);
    backButton = Button(sf::Vector2f(450, 400), sf::Vector2f(150, 50), "Back", font);
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
    betText.setString("Bet: " + std::to_string(betAmount));

    std::string playerStr = "Player: ";
    for (int card : playerCards) playerStr += std::to_string(card) + " ";
    playerStr += "(" + std::to_string(playerTotal) + ")";
    playerText.setString(playerStr);

    std::string dealerStr = "Dealer: ";
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
        result = "You bust! Lost " + std::to_string(betAmount);
        moneyChange = -betAmount;
    } else if (dealerTotal > 21) {
        result = "Dealer bust! Won " + std::to_string(betAmount);
        moneyChange = betAmount;
    } else if (playerTotal > dealerTotal) {
        result = "You win! Won " + std::to_string(betAmount);
        moneyChange = betAmount;
    } else if (playerTotal < dealerTotal) {
        result = "You lose! Lost " + std::to_string(betAmount);
        moneyChange = -betAmount;
    } else {
        result = "Push! Bet returned";
        moneyChange = 0;
    }
    resultText.setString(result);
}

void Blackjack::update(sf::RenderWindow& window, int& money) {
    if (!gameStarted) return;

    if (playerStand && !dealerStand) {
        if (dealerTotal < 17) {
            hitDealer();
        } else {
            dealerStand = true;
            checkResult();
            money += moneyChange;
        }
        updateTexts();
    }

    if (hitButton.isMouseOver(window)) {
        hitButton.setColor(sf::Color(100, 100, 100));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !playerStand) {
            hitPlayer();
            if (playerTotal >= 21) {
                playerStand = true;
                checkResult();
                money += moneyChange;
            }
            updateTexts();
        }
    } else {
        hitButton.setColor(sf::Color(70, 70, 70));
    }

    if (standButton.isMouseOver(window)) {
        standButton.setColor(sf::Color(100, 100, 100));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !playerStand) {
            playerStand = true;
            while (dealerTotal < 17) hitDealer();
            dealerStand = true;
            checkResult();
            money += moneyChange;
            updateTexts();
        }
    } else {
        standButton.setColor(sf::Color(70, 70, 70));
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

void Blackjack::draw(sf::RenderWindow& window) {
    if (!gameStarted) return;

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
