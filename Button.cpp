#include "Button.h"

Button::Button(sf::Vector2f position, float width, float height, sf::RenderWindow* view) {
	m_body.setPosition(position);
	m_body.setSize({ width, height });
	m_body.setFillColor(m_fillColor);
	m_body.setOutlineThickness(m_outlineThickness);
	m_body.setOutlineColor(m_outlineColor);
	m_view = view;
}

void Button::draw(sf::RenderWindow* view) const {
	view->draw(m_body);

}

// allows the user to assign colors to the button
void Button::setColors(sf::Color color) {
	m_fillColor = color;

	int red{ m_fillColor.r };
	int green{ m_fillColor.g };
	int blue{ m_fillColor.b };

	m_darkFillColor = sf::Color(red * .5, green * .5, blue * .5);
}


// essentially the update member function for the colors
void Button::initColors() {
	if (isHovered()) {
		m_body.setFillColor(m_darkFillColor);
	}
	else {
		m_body.setFillColor(m_fillColor);
	}
}

bool Button::isHovered() {
	sf::Vector2i mouse{ sf::Mouse::getPosition(*m_view) };

	if (m_body.getGlobalBounds().contains({ static_cast<float>(mouse.x), static_cast<float>(mouse.y) })) {
		return true;
	}
	return false;
}

bool Button::isPressed() {
	bool pressed{ sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) };

	if (this->isHovered() && pressed) {
		return true;
	}
}

void Button::update() {
	initColors();
}