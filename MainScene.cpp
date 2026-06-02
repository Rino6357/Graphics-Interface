#include "MainScene.h"
#include "Game.h"

// MainScene.cpp
MainScene::MainScene(Game* game) : Scene{ game } {
    m_buttons.reserve(15);

    // background
    m_buttons.emplace_back(sf::Vector2f{ 0, 0 }, 1280.f, 800.f);
    m_buttons.back().setBackGround(true);
    m_buttons.back().setTexture("textures/Background3.png");

    // grass block
    m_buttons.emplace_back(sf::Vector2f{ 100, 100 }, 100.f, 100.f);
    m_buttons.back().setTexture("textures/GrassBlock.png");
    m_buttons.back().setFunction([this] {
        m_buttons[1].setSound(Constants::dirtSounds[Random::get(0, 3)]);
        });

    // stone block
    m_buttons.emplace_back(sf::Vector2f{ 300, 100 }, 100.f, 100.f);
    m_buttons.back().setTexture("textures/StoneBlock.png");
    m_buttons.back().setFunction([this] {
        m_buttons[2].setSound(Constants::stoneSounds[Random::get(0, 3)]);
        });
}

void MainScene::handleKeyPress(std::optional<sf::Event> event) {
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
            m_game->pushScene(m_game->getScene(Game::SceneID::Menu));
        }
    }
}