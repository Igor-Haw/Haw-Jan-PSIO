#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cstdlib>
#include <ctime>

#include "button.h"
#include "clickergame.h"
#include "casino.h"


int main() {
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "PGC");
    window.setFramerateLimit(60);

    // Ładowanie czcionki
    sf::Font font;
    font.loadFromFile("times.ttf");

    // Inicjalizacja komponentów gry
    ClickerGame clickerGame(font);
    Casino casino(font);

    // Przyciski menu głównego
    Button minigameButton(sf::Vector2f(300, 200), sf::Vector2f(200, 50), "Zarabianie", font);
    Button casinoButton(sf::Vector2f(300, 300), sf::Vector2f(200, 50), "Kasyno", font);
    Button exitButton(sf::Vector2f(300, 400), sf::Vector2f(200, 50), "Wyjdz z gry", font);

    // Tekst tytułu
    sf::Text titleText("POZNAN GRANDE CA$INO", font, 50);
    titleText.setFillColor(sf::Color::Yellow);
    sf::FloatRect textBounds = titleText.getLocalBounds();
    titleText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    titleText.setPosition(800 / 2.0f, 100); // wyśrodkowany poziomo, 100px od góry

    bool casinoWasActive = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (clickerGame.isActive()) {
                clickerGame.handleEvent(event, window);
            }

            if (casino.isActive()) {
                casino.handleEvent(event, window);
            }

            if (!clickerGame.isActive() && !casino.isActive()) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    if (minigameButton.isMouseOver(window)) {
                        clickerGame.startGame();
                    }
                    if (casinoButton.isMouseOver(window)) {
                        casino.start(clickerGame.getMoney());
                    }
                    if (exitButton.isMouseOver(window)) {
                        window.close();
                    }
                }
            }

        }

        window.clear();

        if (!clickerGame.isActive() && !casino.isActive()) {
            // Rysowanie menu głównego
            window.draw(titleText);
            minigameButton.draw(window);
            casinoButton.draw(window);
            exitButton.draw(window);

            if (minigameButton.isMouseOver(window)) {
                minigameButton.setColor(sf::Color(100, 100, 100));

            } else {
                minigameButton.setColor(sf::Color(70, 70, 70));
            }

            if (casinoButton.isMouseOver(window)) {
                casinoButton.setColor(sf::Color(100, 100, 100));

            } else {
                casinoButton.setColor(sf::Color(70, 70, 70));
            }

            if (exitButton.isMouseOver(window)) {
                exitButton.setColor(sf::Color(100, 100, 100));

            } else {
                exitButton.setColor(sf::Color(70, 70, 70));
            }
        }
        else if (clickerGame.isActive()) {
            clickerGame.update(window);
            clickerGame.draw(window);
        }
        else if (casino.isActive()) {
            casino.update(window);
            casino.draw(window);
        }

        // wykrywamy wyjście z kasyna
        if (casinoWasActive && !casino.isActive()) {
            clickerGame.setMoney(casino.getMoney());
        }
        casinoWasActive = casino.isActive();  // aktualizujemy stan

        window.display();
    }

    return 0;
}
