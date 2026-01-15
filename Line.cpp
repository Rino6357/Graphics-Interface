#include "Line.h"

Line::Line(sf::Vector2f origin, sf::Vector2f joint) 
    : m_origin{ origin }, m_joint{ joint } 
{
	m_vertexArray.append(sf::Vertex{ m_origin });
	m_vertexArray.append(sf::Vertex{ m_joint });
}

void Line::rotateLine(double angle, float dt, float speed) {
    m_vertexArray[1].position.x = m_vertexArray[0].position.x + this->length() * std::cosf(m_theta);
    m_vertexArray[1].position.y = m_vertexArray[0].position.y + -this->length() * std::sinf(m_theta);

    if (m_theta <= angle) {
        m_theta += speed * dt;
    }
}

void Line::draw(sf::RenderWindow& window) const {
	window.draw(m_vertexArray);
}

float Line::length() const {
    float horizontalDist{ std::abs(m_origin.x - m_joint.x) };
    float verticalDist{ std::abs(m_origin.y - m_joint.y) };

    float length{ std::sqrt(horizontalDist * horizontalDist + verticalDist * verticalDist) };
    return length;
}

void Line::color(sf::Color color) {
    m_vertexArray[0].color = color;
    m_vertexArray[1].color = color;
}

void Line::moveLine(sf::Vector2f delta) {
    sf::Vector2f origin{ m_vertexArray[0].position.x, m_vertexArray[0].position.y };
    sf::Vector2f joint{ m_vertexArray[1].position.x, m_vertexArray[1].position.y };

    sf::Vector2f newOrigin{ origin + delta };
    sf::Vector2f newJoint{ joint + delta };

    m_vertexArray[0].position.x = newOrigin.x;
    m_vertexArray[0].position.y = newOrigin.y;
    m_vertexArray[1].position.x = newJoint.x;
    m_vertexArray[1].position.y = newJoint.y;

}

sf::VertexArray Line::getVertexArray() const {
    return m_vertexArray;
}