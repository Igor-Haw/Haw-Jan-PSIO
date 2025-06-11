    #include "ClickerGame.h"

    ClickerGame::ClickerGame(sf::Font& font)
        : font(font), gameStarted(false), money(0), clickValue(1) {

        moneyText.setFont(font);
        moneyText.setCharacterSize(36);
        moneyText.setFillColor(sf::Color::White);
        moneyText.setPosition(50, 50);

        clickValueText.setFont(font);
        clickValueText.setCharacterSize(24);
        clickValueText.setFillColor(sf::Color::White);
        clickValueText.setPosition(50, 100);

        clickButton = Button(sf::Vector2f(300, 200), sf::Vector2f(200, 100), "Kliknij by zarobic!", font);
        upgradeButton = Button(sf::Vector2f(300, 350), sf::Vector2f(200, 50), "Ulepsz przycisk (10$)", font);
        backButton = Button(sf::Vector2f(300, 450), sf::Vector2f(200, 50), "Powrot", font);
        backgroundTexture.loadFromFile("menu_bg.png");
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            800.f / backgroundTexture.getSize().x,
            600.f / backgroundTexture.getSize().y
            );
    }

    void ClickerGame::startGame() {
        gameStarted = true;
        updateTexts();
    }

    void ClickerGame::updateTexts() {
        moneyText.setString("Saldo: " + std::to_string(money) + "$");
        clickValueText.setString("Mnoznik klikniec: x" + std::to_string(clickValue));
        upgradeButton = Button(sf::Vector2f(300, 350), sf::Vector2f(200, 50),
                               "Ulepsz przycisk (" + std::to_string(500 * clickValue) + "$)", font);
    }

    void ClickerGame::handleEvent(sf::Event& event, sf::RenderWindow& window) {
        if (!gameStarted) return;

        if (clickButton.isClicked(event, window)) {
            money += clickValue;
            updateTexts();
        }

        if (upgradeButton.isClicked(event, window) && money >= 500 * clickValue) {
            money -= 500 * clickValue;
            clickValue++;
            updateTexts();
        }

        if (backButton.isClicked(event, window)) {
            gameStarted = false;
        }
    }

    void ClickerGame::update(sf::RenderWindow& window) {
        if (!gameStarted) return;

        clickButton.setColor(clickButton.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
        upgradeButton.setColor(upgradeButton.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
        backButton.setColor(backButton.isMouseOver(window) ? sf::Color(100, 100, 100) : sf::Color(70, 70, 70));
    }

    void ClickerGame::draw(sf::RenderWindow& window) {
        if (!gameStarted) return;

        window.draw(backgroundSprite);
        window.draw(moneyText);
        window.draw(clickValueText);

        clickButton.draw(window);
        upgradeButton.draw(window);
        backButton.draw(window);
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
