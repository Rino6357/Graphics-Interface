#include "Game.h"

// Game.cpp
Game::Game()
    : m_window(sf::VideoMode({ 1280, 800 }), "SFML Workspace", sf::Style::Default),
    m_mainScene(this),
    m_menuScene(this),
    m_startMenu(this),
    m_playScene(this) {
    m_view = sf::View(sf::FloatRect({ 0,0 }, { 1280, 800 }));
    m_window.setView(m_view);
    m_window.setKeyRepeatEnabled(false);
    //toggleFullscreen();
}

sf::Vector2f Game::m_mouse{ sf::Vector2f(0, 0) };
bool Game::m_mousePressed{ false };

void Game::run()
{
    pushScene(&m_startMenu);
    while (m_window.isOpen())
    {
        while (const std::optional<sf::Event> event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                m_window.close();
            handleMouse(event);
            handleResize(event);
            handleKeys(event);
        }
        update();
        draw();
    }
}

// Game.cpp
Scene* Game::getScene(SceneID id) {
    switch (id) {
    case SceneID::Main: return &m_mainScene;
    case SceneID::Menu: return &m_menuScene;
    case SceneID::Start: return &m_startMenu;
    case SceneID::Play: return &m_playScene;
    default: return nullptr;
    }
}

void Game::update()
{
	m_mouse = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

    m_scenes.back()->update();
}

void Game::processEvents()
{
}

void Game::draw()
{
    m_window.clear(sf::Color(50, 40, 80));

    for (auto scene : m_scenes) {
        scene->draw(&m_window);
    }

    m_window.display();
}

void Game::handleMouse(std::optional<sf::Event> event)
{
    if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            m_mousePressed = true;

            sf::Vector2f clickPos = m_window.mapPixelToCoords(mousePressed->position);

        // Alert every button about the physical click location
            m_scenes.back()->handleMouseClick(clickPos);
        }
    }
    else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonReleased>()) {

        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            m_mousePressed = false;

		}
    }
}

void Game::handleResize(std::optional<sf::Event> event)
{
    if (const auto* resized = event->getIf<sf::Event::Resized>()) {
        m_view.setSize({ static_cast<float>(resized->size.x), static_cast<float>(resized->size.y) });
        m_view.setCenter({ resized->size.x / 2.f, resized->size.y / 2.f });
        m_window.setView(m_view);

        for (auto* scene : m_scenes) {
            scene->repositionButtons(resized->size.x, resized->size.y);
        }

        m_windowSize = { static_cast<float>(resized->size.x), static_cast<float>(resized->size.y) };

    }
}

void Game::handleKeys(std::optional<sf::Event> event) {
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::F11) {
            toggleFullscreen();
        }
    }
    m_scenes.back()->handleKeyPress(event);
}

void Game::toggleFullscreen() {
    m_isFullscreen = !m_isFullscreen;
    if (m_isFullscreen) {
        m_window.create(sf::VideoMode::getDesktopMode(), "SFML Workspace", sf::State::Fullscreen);

        m_view.setSize({ static_cast<float>(sf::VideoMode::getDesktopMode().size.x),
                         static_cast<float>(sf::VideoMode::getDesktopMode().size.y) });

        m_view.setCenter({ sf::VideoMode::getDesktopMode().size.x / 2.f,
                           sf::VideoMode::getDesktopMode().size.y / 2.f });

        unsigned int newWidth{ sf::VideoMode::getDesktopMode().size.x };
        unsigned int newHeight{ sf::VideoMode::getDesktopMode().size.y };

        for (auto* scene : m_scenes) {
            scene->repositionButtons(newWidth, newHeight);
        }

        m_windowSize = { static_cast<float>(newWidth), static_cast<float>(newHeight) };

    }
    else {
        m_window.create(sf::VideoMode({ 1280, 800 }), "SFML Workspace", sf::Style::Default);
        m_view.setSize({ 1280.f, 800.f });
        m_view.setCenter({ 640.f, 400.f });

        for (auto* scene : m_scenes) {
            scene->repositionButtons(1280, 800);
        }

        m_windowSize = { 1280.f,800.f };
    }
    m_window.setView(m_view);
}

void Game::pushScene(Scene* scene) {
    if (!m_scenes.empty()) {
        m_scenes.back()->setInteractable(false);
    }

    m_scenes.push_back(scene);
    scene->repositionButtons(m_windowSize.x, m_windowSize.y);
}

void Game::switchScene(Scene* scene) {
    m_scenes.pop_back();
    m_scenes.push_back(scene);
    scene->repositionButtons(m_windowSize.x, m_windowSize.y);
}

void Game::popScene() {
    m_scenes.pop_back();
    if (!m_scenes.empty()) {
        m_scenes.back()->setInteractable(true); 
    }
}