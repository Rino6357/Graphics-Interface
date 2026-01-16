#include "Button.h"

Button::Button(sf::Vector2f position, float width, float height, sf::RenderWindow* view) {
	/*
	Insert Specification
	*/
	// rectangle initialization
	m_body.setPosition(position);
	m_body.setSize({ width, height });
	m_body.setFillColor(m_fillColor);
	m_body.setOutlineThickness(m_outlineThickness);
	m_body.setOutlineColor(m_outlineColor);
	m_view = view;

	// circle initialization
	m_circle.setFillColor(sf::Color(114, 121, 133));
	m_circle.setOutlineColor(sf::Color::White);
	m_circle.setOutlineThickness(1);
	m_circle.setOrigin(m_circle.getGeometricCenter());
	m_circle.setPosition(m_body.getPosition());
}

void Button::draw(sf::RenderWindow* view) {
	/*
	Insert Specification
	*/
	view->draw(m_body);
	if (isHovered()) {
		view->draw(m_circle);
	}

}

// allows the user to assign colors to the button
void Button::setColors(sf::Color color) {
	/*
	Insert Specification
	*/
	m_fillColor = color;

	int red{ m_fillColor.r };
	int green{ m_fillColor.g };
	int blue{ m_fillColor.b };

	m_darkFillColor = sf::Color(red * .5, green * .5, blue * .5);
	m_darkerFillColor = sf::Color(red * .25, green * .25, blue * .25);
}


void Button::initColors() {
	/*
	Insert Specification
	*/

	if (isHovered()) {
		m_body.setFillColor(m_darkFillColor);
		if (isPressed() && !m_dragging) {
			m_body.setFillColor(m_darkerFillColor);
		}
	}
	else {
		m_body.setFillColor(m_fillColor);
	}
}

void Button::handleMove() {
	/*
	Insert Specification
	*/
	sf::Vector2i mouse{ m_view->mapPixelToCoords(sf::Mouse::getPosition(*m_view)) };
	sf::Vector2f rectPos{ m_body.getPosition() };

	if (m_circle.getGlobalBounds().contains({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) }) && isPressed()) {
		m_dragging = true;
	}

	if (m_dragging) {
		m_body.setPosition({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) });
		m_circle.setPosition({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) });
	}
	
}

bool Button::isHovered() {
	/*
	Insert Specification
	*/
	sf::Vector2i mouse{ m_view->mapPixelToCoords(sf::Mouse::getPosition(*m_view)) };

	if (m_body.getGlobalBounds().contains({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) })
		|| m_circle.getGlobalBounds().contains({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) })
	) {
		return true;
	}
	return false;
}

bool Button::isPressed() {
	bool pressed{ sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) };

	if (pressed) {
		return true;
	}
}

void Button::update() {
	initColors();
	handleMove();

	if (!isPressed() && m_dragging) {
		m_dragging = false;
	}
}