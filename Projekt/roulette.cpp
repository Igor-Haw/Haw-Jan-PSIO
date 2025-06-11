#include "Roulette.h"
#include <cstdlib>

Roulette::Roulette(sf::Font& font)
    : font(font),
    gameStarted(false),
    resultShown(false),
    betAmount(0),
    selectedNumber(-1),
    selectedColor(-1),
    resultNumber(-1),
    resultColor(-1),
    moneyChange(0) {

    // Konfiguracja tekstu
    betText.setFont(font);
    betText.setCharacterSize(24);
    betText.setFillColor(sf::Color::White);
    betText.setPosition(50.f, 50.f);

    resultText.setFont(font);
    resultText.setCharacterSize(30);
    resultText.setFillColor(sf::Color::Yellow);
    resultText.setPosition(150.f, 500.f);

    numberText.setFont(font);
    numberText.setCharacterSize(24);
    numberText.setFillColor(sf::Color::White);
    numberText.setPosition(50.f, 100.f);

    colorText.setFont(font);
    colorText.setCharacterSize(24);
    colorText.setFillColor(sf::Color::White);
    colorText.setPosition(50.f, 150.f);

    spinButton = Button(sf::Vector2f(300.f, 400.f), sf::Vector2f(150.f, 50.f), "Zakrec", font);
    backButton = Button(sf::Vector2f(450.f, 400.f), sf::Vector2f(150.f, 50.f), "Powrot", font);

    for (int i = 0; i <= 36; ++i) {
        if (i == 0) {
            numberColors[i] = 2;
        } else if ((i >= 1 && i <= 10) || (i >= 19 && i <= 28)) {
            numberColors[i] = (i % 2 == 1) ? 0 : 1;
        } else {
            numberColors[i] = (i % 2 == 1) ? 1 : 0;
        }
    }
}

void Roulette::startGame(int bet) {
    betAmount = bet;
    gameStarted = true;
    resultShown = false;
    selectedNumber = -1;
    selectedColor = -1;
    resultNumber = -1;
    updateTexts();
}

void Roulette::updateTexts() {
    betText.setString("Zaklad: " + std::to_string(betAmount)+"$");

    std::string numberStr = "Numer: ";
    numberStr += (selectedNumber == -1) ? "Nie wybrano" : std::to_string(selectedNumber);
    numberText.setString(numberStr);

    std::string colorStr = "Kolor: ";
    if (selectedColor == -1) {
        colorStr += "Nie wybrano";
    } else if (selectedColor == 0) {
        colorStr += "Czerwony";
    } else if (selectedColor == 1) {
        colorStr += "Czarny";
    } else {
        colorStr += "Zielony";
    }
    colorText.setString(colorStr);
}

void Roulette::spin() {
    if (selectedNumber == -1 && selectedColor == -1) return;

    resultNumber = rand() % 37;
    resultColor  = numberColors[resultNumber];

    if (selectedNumber != -1 && selectedNumber == resultNumber) {
        moneyChange = betAmount * 35;
        result = "WYGRALES!  Numer " + std::to_string(resultNumber) + "!  Wygrana " + std::to_string(moneyChange)+"$";
    } else if (selectedColor != -1 && selectedColor == resultColor) {
        moneyChange = betAmount;
        result = "WYGRALES!  Dobry kolor!  Wygrana " + std::to_string(moneyChange)+"$";
    } else {
        moneyChange = -betAmount;
        result = "PZEGRALES!  Wylosowano: " + std::to_string(resultNumber) + "  Przegrana " + std::to_string(betAmount);
    }

    resultText.setString(result);
    resultShown = true;
}

void Roulette::update(sf::RenderWindow& window, int& /*money*/) {
    if (!gameStarted) return;

    spinButton.setColor(spinButton.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
    backButton.setColor(backButton.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
}

void Roulette::handleEvent(const sf::Event& event, sf::RenderWindow& window, int& money) {
    if (!gameStarted || event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left)
        return;

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    for (int i = 0; i <= 36; ++i) {
        int row = i / 12;
        int col = i % 12;
        sf::FloatRect rectBounds(50.f + col * 45.f, 200.f + row * 45.f, 40.f, 40.f);
        if (rectBounds.contains(mousePos)) {
            selectedNumber = i;
            selectedColor = -1;
            updateTexts();
            return;
        }
    }

    sf::FloatRect redRect(50.f, 380.f, 100.f, 40.f);
    if (redRect.contains(mousePos)) {
        selectedColor = 0;
        selectedNumber = -1;
        updateTexts();
        return;
    }

    sf::FloatRect blackRect(160.f, 380.f, 100.f, 40.f);
    if (blackRect.contains(mousePos)) {
        selectedColor = 1;
        selectedNumber = -1;
        updateTexts();
        return;
    }

    if (spinButton.isMouseOver(window) && !resultShown && (selectedNumber != -1 || selectedColor != -1)) {
        spin();
        money += moneyChange;
        return;
    }

    if (backButton.isMouseOver(window)) {
        gameStarted = false;
    }
}

void Roulette::draw(sf::RenderWindow& window) {
    if (!gameStarted) return;

    window.draw(betText);
    window.draw(numberText);
    window.draw(colorText);

    for (int i = 0; i <= 36; ++i) {
        int row = i / 12;
        int col = i % 12;
        sf::RectangleShape numberRect(sf::Vector2f(40.f, 40.f));
        numberRect.setPosition(50.f + col * 45.f, 200.f + row * 45.f);

        if (numberColors[i] == 0)      numberRect.setFillColor(sf::Color::Red);
        else if (numberColors[i] == 1) numberRect.setFillColor(sf::Color::Black);
        else                           numberRect.setFillColor(sf::Color::Green);

        if (selectedNumber == i) {
            numberRect.setOutlineThickness(2.f);
            numberRect.setOutlineColor(sf::Color::Yellow);
        }

        window.draw(numberRect);

        sf::Text numberLabel(std::to_string(i), font, 16);
        numberLabel.setPosition(50.f + col * 45.f + 10.f, 200.f + row * 45.f + 10.f);
        numberLabel.setFillColor(sf::Color::White);
        window.draw(numberLabel);
    }

    sf::RectangleShape redRect(sf::Vector2f(100.f, 40.f));
    redRect.setPosition(50.f, 380.f);
    redRect.setFillColor(sf::Color::Red);
    if (selectedColor == 0) {
        redRect.setOutlineThickness(2.f);
        redRect.setOutlineColor(sf::Color::Yellow);
    }
    window.draw(redRect);

    sf::RectangleShape blackRect(sf::Vector2f(100.f, 40.f));
    blackRect.setPosition(160.f, 380.f);
    blackRect.setFillColor(sf::Color::Black);
    if (selectedColor == 1) {
        blackRect.setOutlineThickness(2.f);
        blackRect.setOutlineColor(sf::Color::Yellow);
    }
    window.draw(blackRect);

    sf::Text redText("CZERWONY", font, 16); redText.setPosition(55.f, 390.f); window.draw(redText);
    sf::Text blackText("CZARNY", font, 16); blackText.setPosition(175.f, 390.f); window.draw(blackText);

    if (resultShown) window.draw(resultText);

    spinButton.draw(window);
    backButton.draw(window);
}

bool Roulette::isActive() const {
    return gameStarted;
}
