#include "StartMenu.h"
#include "Game.h"
StartMenu::StartMenu(Game* game) : Scene{ game } {
    m_buttons.push_back(std::make_unique<Button>(sf::Vector2f{ 0, 0 }, 1280.f, 800.f));
    m_buttons.back()->setBackGround(true);
    m_buttons.back()->setColors(sf::Color(206, 237, 177));

    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f{ m_game->getWindowSize().x / 2 - 350.f, -100 },
        700.f, 700.f
    ));
    m_buttons.back()->setOutlineTrans();
    m_buttons.back()->setStationary(true);
    m_buttons.back()->setInteractable(false);
    m_buttons.back()->setUntouchable(true);
    m_buttons.back()->setTexture("Textures/TitleTTTE.png");

    m_buttons.push_back(std::make_unique<TextBox>(
        sf::Vector2f{ m_game->getWindowSize().x / 2 - 140.f, 500 }, //Button Location
        280.f, 120.f, //Button size
        "Play",       //Text
        "Fonts/VCR_OSD_MONO_1.001.ttf") //Font
    );
    m_buttons.back()->setTexture("textures/RegularButton.png");
    m_buttons.back()->setOutlineTrans();
    m_buttons.back()->setFunction([this] {
        m_game->pushScene(m_game->getScene(Game::SceneID::Menu));
        });
    m_buttons.back()->setStationary(true);

    m_buttons.push_back(std::make_unique<TextBox>(
        sf::Vector2f{ m_game->getWindowSize().x / 2 - 140.f, 650 },
        280.f, 120.f,
        "Settings",
        "Fonts/VCR_OSD_MONO_1.001.ttf")
    );
    m_buttons.back()->setTexture("textures/RegularButton.png");
    m_buttons.back()->setOutlineTrans();
    m_buttons.back()->setStationary(true);
}