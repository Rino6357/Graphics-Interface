#include "Game.h"

Game::Game() 
    : m_window(sf::VideoMode({800, 600}), "SFML Workspace") {

}

sf::Vector2i Game::m_mouse{ sf::Vector2i(0, 0) };
bool Game::m_mousePressed{ false };

void Game::run()
{

    Button button{ {100,100}, 100, 100};
    button.setColors(sf::Color::Green);

    Button button1{ {300,100}, 100, 100};
    button1.setColors(sf::Color::Blue);

    button.setFunction(
        [&] {
            button.setSound(Constants::dirtSounds[Random::get(0, 3)]);
        }
    );

	//button.setSound("sounds/MouseClick.wav");
	button.setTexture("textures/GrassBlock.png");

    addButton(&button);

    addButton(&button1);

    while (m_window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional<sf::Event> event = m_window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                m_window.close();

			handleMouse(event);
        }
        update();
        draw();
    }
}

void Game::update()
{
	m_mouse = sf::Mouse::getPosition(m_window);

    for (auto c : m_buttons) {
        c->update();
    }
}

void Game::processEvents()
{
}

void Game::handleMouseClick()
{
}

void Game::draw()
{
    m_window.clear(sf::Color(50, 40, 80));

    for (auto c : m_buttons) {
        c->draw(&m_window);
    }

    m_window.display();
}

void Game::addButton(Button* button)
{
    m_buttons.push_back(button);
}

void Game::handleMouse(std::optional<sf::Event> event)
{
    if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            m_mousePressed = true;

            sf::Vector2f clickPos{ static_cast<float>(mousePressed->position.x), 
                               static_cast<float>(mousePressed->position.y) };

        // Alert every button about the physical click location
            for (auto* button : m_buttons) {
                button->handleMouseClick(clickPos);
            }
        }
    }
    else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonReleased>()) {

        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            m_mousePressed = false;

		}
    }
}
