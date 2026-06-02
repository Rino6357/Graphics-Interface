#include "MainScene.h"
#include "Game.h"
MainScene::MainScene(Game* game) : Scene{ game } {
    m_buttons.push_back(std::make_unique<Button>(sf::Vector2f{ 0, 0 }, 1280.f, 800.f));
    m_buttons.back()->setBackGround(true);
    m_buttons.back()->setTexture("textures/Background3.png");

    m_buttons.push_back(std::make_unique<Button>(sf::Vector2f{ 100, 100 }, 100.f, 100.f));
    m_buttons.back()->setTexture("textures/GrassBlock.png");
    m_buttons.back()->setFunction([this] {
        m_buttons[1]->setSound(Constants::dirtSounds[Random::get(0, 3)]);
        });

    m_buttons.push_back(std::make_unique<Button>(sf::Vector2f{ 300, 100 }, 100.f, 100.f));
    m_buttons.back()->setTexture("textures/StoneBlock.png");
    m_buttons.back()->setFunction([this] {
        m_buttons[2]->setSound(Constants::stoneSounds[Random::get(0, 3)]);
        });
}
void MainScene::handleKeyPress(std::optional<sf::Event> event) {
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
            m_game->pushScene(m_game->getScene(Game::SceneID::Menu));
        }
    }
}