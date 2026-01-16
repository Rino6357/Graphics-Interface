#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(sf::Vector2f position, float width, float height, sf::RenderWindow* view);

	void draw(sf::RenderWindow* view);

	void setColors(sf::Color color);

	void initColors();

	void handleMove();

	bool isHovered();

	bool isPressed();

	void update();

private:

	sf::RectangleShape m_body{};
	sf::CircleShape m_circle{5};
	sf::Color m_fillColor{};
	sf::Color m_darkFillColor{};
	sf::Color m_outlineColor{ sf::Color::White };
	float m_outlineThickness{1};
	sf::RenderWindow* m_view{};
	bool m_dragging{ false };

};

