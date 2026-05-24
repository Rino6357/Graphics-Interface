#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Constants.h"
#include "Button.h"

class Game
{
public:
	Game();

	~Game() = default;

	void run();

	static sf::Vector2i getMousePosition() {
		return m_mouse;
	}
	
	static bool isMousePressed() {
		return m_mousePressed;
	}

private:

	void update();

	void processEvents();

	void handleMouseClick();

	void draw();

	void addButton(Button* button);

	void handleMouse(std::optional<sf::Event> event);

	static sf::Vector2i m_mouse;
	static bool m_mousePressed;

	sf::RenderWindow m_window;
	sf::Clock m_clock{};
	std::vector<Button*> m_buttons;
};

