#include "Leg.h"
#include "Constants.h"

Leg::Leg(sf::Vector2f joint1, sf::Vector2f joint2, sf::Vector2f joint3, sf::Vector2f end)
	: m_joint1{ joint1 }, m_joint2{ joint2 }, m_joint3{ joint3 }, m_end{ end }
{
	this->color();
}

void Leg::rotateCoxa(double angle, float dt, float speed) {
	sf::Vector2f original { m_coxa.getVertexArray()[1].position.x, m_coxa.getVertexArray()[1].position.y };
	m_coxa.rotateLine(angle, dt, speed);

	sf::Vector2f newOrigin{ m_coxa.getVertexArray()[1].position.x, m_coxa.getVertexArray()[1].position.y };
	sf::Vector2f delta{ newOrigin - original };

	m_femur.moveLine(delta);
	m_tibia.moveLine(delta);
}

void Leg::rotateFemur(double angle, float dt, float speed) {
	sf::Vector2f original{ m_femur.getVertexArray()[1].position.x, m_femur.getVertexArray()[1].position.y };
	m_femur.rotateLine(angle, dt, speed);

	sf::Vector2f newOrigin{ m_femur.getVertexArray()[1].position.x, m_femur.getVertexArray()[1].position.y };
	sf::Vector2f delta{ newOrigin - original };

	m_tibia.moveLine(delta);
}

void Leg::rotateTibia(double angle, float dt, float speed) {
	m_tibia.rotateLine(angle, dt, speed);
}

void Leg::draw(sf::RenderWindow& window) {
	m_coxa.color(m_color1);
	m_femur.color(m_color2);
	m_tibia.color(m_color3);

	m_coxa.draw(window);
	m_femur.draw(window);
	m_tibia.draw(window);
}

void Leg::color(sf::Color color1, sf::Color color2, sf::Color color3) {
	m_color1 = color1;
	m_color2 = color2;
	m_color3 = color3;
}

bool Leg::IK2D(float x, float y, float dt)
{
    return true;
}
