#include "MenuScene.h"
#include "Game.h"
MenuScene::MenuScene(Game* game) : Scene{ game } {
    m_buttons.push_back(std::make_unique<Button>(sf::Vector2f{ 0, 0 }, 1280.f, 800.f));
    m_buttons.back()->setBackGround(true);
    m_buttons.back()->setColors(sf::Color(50, 50, 50, 128));

    m_buttons.push_back(std::make_unique<Button>(sf::Vector2f{ 20.f, 20.f }, 800.f, 400.f));
    m_buttons.back()->setStationary(true);
    m_buttons.back()->setTexture("Textures/Background1.png");
}
void MenuScene::handleKeyPress(std::optional<sf::Event> event) {
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
            m_game->popScene();
        }
    }
}