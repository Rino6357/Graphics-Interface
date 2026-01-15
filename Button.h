#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(sf::Vector2f position, float width, float height, sf::RenderWindow* view);

	void draw(sf::RenderWindow* view) const;

	void setColors(sf::Color color);

	void initColors();

	bool isHovered();

	bool isPressed();

	void update();

private:

	sf::RectangleShape m_body{};
	sf::Color m_fillColor{};
	sf::Color m_darkFillColor{};
	sf::Color m_outlineColor{ sf::Color::White };
	float m_outlineThickness{1};
	sf::RenderWindow* m_view{};

};

