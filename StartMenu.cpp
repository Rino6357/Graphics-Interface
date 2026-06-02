#include "StartMenu.h"
#include "Game.h"

StartMenu::StartMenu(Game* game) : Scene{ game } {
    m_buttons.reserve(2);

    m_buttons.emplace_back(sf::Vector2f{ 0, 0 }, 1280.f, 800.f);
    m_buttons.back().setBackGround(true);
    m_buttons.back().setColors(sf::Color(206, 237, 177));

    m_buttons.emplace_back(sf::Vector2f{ m_game->getWindowSize().x / 2 - 140.f, 500}, 280.f, 120.f);
    m_buttons.back().setTexture("textures/RegularButton.png");
    m_buttons.back().setOutlineTrans();
    m_buttons.back().setFunction([this] {
        m_game->pushScene(m_game->getScene(Game::SceneID::Menu));
    });
    m_buttons.back().setStationary(true);
}
