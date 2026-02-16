#pragma once
#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

using ButtonFunction = std::function<void()>;

class Button
{
public:
	Button(sf::Vector2f position, float width, float height, sf::RenderWindow* view);

	void draw(sf::RenderWindow* view);

	void setColors(sf::Color color);

	void handleColors();

	void handleMove();

	void setFunction(ButtonFunction action);

	bool isHovered();

	bool isPressed();

	void update();

private:

	sf::RectangleShape m_body{};
	sf::CircleShape m_circle{5};
	sf::Color m_fillColor{};
	sf::Color m_darkFillColor{};
	sf::Color m_darkerFillColor{};
	sf::Color m_outlineColor{ sf::Color::White };
	float m_outlineThickness{1};
	sf::RenderWindow* m_view{};
	ButtonFunction m_action{NULL};
	bool m_dragging{ false };
	bool m_pressed{ false };
};

