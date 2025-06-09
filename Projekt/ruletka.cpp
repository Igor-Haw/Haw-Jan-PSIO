#include "Ruletka.h"
#include <cstdlib>

Ruletka::Ruletka(sf::Font& font)
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
    resultText.setPosition(300.f, 300.f);

    numberText.setFont(font);
    numberText.setCharacterSize(24);
    numberText.setFillColor(sf::Color::White);
    numberText.setPosition(50.f, 100.f);

    colorText.setFont(font);
    colorText.setCharacterSize(24);
    colorText.setFillColor(sf::Color::White);
    colorText.setPosition(50.f, 150.f);


    spinButton = Button(sf::Vector2f(300.f, 400.f), sf::Vector2f(150.f, 50.f), "Spin", font);
    backButton = Button(sf::Vector2f(450.f, 400.f), sf::Vector2f(150.f, 50.f), "Back", font);


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

void Ruletka::startGame(int bet) {
    betAmount = bet;
    gameStarted = true;
    resultShown = false;
    selectedNumber = -1;
    selectedColor = -1;
    resultNumber = -1;
    updateTexts();
}

void Ruletka::updateTexts() {
    betText.setString("Bet: " + std::to_string(betAmount));

    std::string numberStr = "Number: ";
    numberStr += (selectedNumber == -1) ? "Not selected" : std::to_string(selectedNumber);
    numberText.setString(numberStr);

    std::string colorStr = "Color: ";
    if (selectedColor == -1) {
        colorStr += "Not selected";
    } else if (selectedColor == 0) {
        colorStr += "Red";
    } else if (selectedColor == 1) {
        colorStr += "Black";
    } else {
        colorStr += "Green";
    }
    colorText.setString(colorStr);
}

void Ruletka::spin() {
    if (selectedNumber == -1 && selectedColor == -1) return;

    resultNumber = rand() % 37;          // 0–36
    resultColor  = numberColors[resultNumber];

    // Sprawdzenie wyniku zakładu
    if (selectedNumber != -1 && selectedNumber == resultNumber) {
        // Trafienie liczby – 35:1
        moneyChange = betAmount * 35;
        result = "WIN! Number " + std::to_string(resultNumber) + "! Won " + std::to_string(moneyChange);
    } else if (selectedColor != -1 && selectedColor == resultColor) {
        // Trafienie koloru – 1:1
        moneyChange = betAmount;
        result = "WIN! Color match! Won " + std::to_string(moneyChange);
    } else {
        // Przegrana
        moneyChange = -betAmount;
        result = "LOSE! Result: " + std::to_string(resultNumber) + ". Lost " + std::to_string(betAmount);
    }

    resultText.setString(result);
    resultShown = true;
}

void Ruletka::update(sf::RenderWindow& window, int& money) {
    if (!gameStarted) return;

    for (int i = 0; i <= 36; ++i) {
        int row = i / 12;
        int col = i % 12;
        sf::RectangleShape numberRect(sf::Vector2f(40.f, 40.f));
        numberRect.setPosition(50.f + col * 45.f, 200.f + row * 45.f);

        if (numberRect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            numberRect.setOutlineThickness(2.f);
            numberRect.setOutlineColor(sf::Color::Yellow);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                selectedNumber = i;
                selectedColor = -1;
                updateTexts();
            }
        }
    }

    sf::RectangleShape redRect  (sf::Vector2f(100.f, 40.f)); redRect  .setPosition(50.f , 350.f);
    sf::RectangleShape blackRect(sf::Vector2f(100.f, 40.f)); blackRect.setPosition(160.f, 350.f);

    if (redRect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
        redRect.setOutlineThickness(2.f);
        redRect.setOutlineColor(sf::Color::Yellow);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            selectedColor = 0;
            selectedNumber = -1;
            updateTexts();
        }
    }

    if (blackRect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
        blackRect.setOutlineThickness(2.f);
        blackRect.setOutlineColor(sf::Color::Yellow);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            selectedColor = 1;
            selectedNumber = -1;
            updateTexts();
        }
    }

    if (spinButton.isMouseOver(window)) {
        spinButton.setColor(sf::Color(100, 100, 100));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !resultShown && (selectedNumber != -1 || selectedColor != -1)) {
            spin();
            money += moneyChange;
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

void Ruletka::draw(sf::RenderWindow& window) {
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
    redRect.setPosition(50.f, 350.f);
    redRect.setFillColor(sf::Color::Red);
    if (selectedColor == 0) {
        redRect.setOutlineThickness(2.f);
        redRect.setOutlineColor(sf::Color::Yellow);
    }
    window.draw(redRect);

    sf::RectangleShape blackRect(sf::Vector2f(100.f, 40.f));
    blackRect.setPosition(160.f, 350.f);
    blackRect.setFillColor(sf::Color::Black);
    if (selectedColor == 1) {
        blackRect.setOutlineThickness(2.f);
        blackRect.setOutlineColor(sf::Color::Yellow);
    }
    window.draw(blackRect);

    sf::Text redText("RED", font, 16);   redText.setPosition(75.f , 360.f); window.draw(redText);
    sf::Text blackText("BLACK", font, 16); blackText.setPosition(175.f, 360.f); window.draw(blackText);

    if (resultShown) window.draw(resultText);

    spinButton.draw(window);
    backButton.draw(window);
}

bool Ruletka::isActive() const {
    return gameStarted;
}
