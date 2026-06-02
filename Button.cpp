#include "Button.h"
#include "Game.h"

Button::Button(sf::Vector2f position, float width, float height) {
	/*
	Insert Specification
	*/
	// rectangle initialization
	m_body.setPosition(position);
	m_body.setSize({ width, height });
	m_body.setOutlineThickness(m_outlineThickness);
	m_body.setOutlineColor(m_outlineColor);

	// circle initialization
	m_circle.setFillColor(sf::Color(114, 121, 133));
	m_circle.setOutlineColor(sf::Color::White);
	m_circle.setOutlineThickness(1);
	m_circle.setOrigin(m_circle.getGeometricCenter());
	m_circle.setPosition(m_body.getPosition());

	sf::FloatRect bounds{ m_body.getGlobalBounds() };

	m_bufferedBounds = sf::FloatRect{
		{bounds.position.x + m_buffer,
		 bounds.position.y + m_buffer},
		{bounds.size.x - (m_buffer * 2),
		 bounds.size.y - (m_buffer * 2)}
	};

}

void Button::draw(sf::RenderWindow* view) {
	/*
	Insert Specification
	*/
	view->draw(m_body);

	if (m_hasTexture) {
		view->draw(m_sprite);
	}
	if (isHovered() && !isBackGround() && !isStationary() && isInteractable()) {
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

	m_darkFillColor = sf::Color(red * .8, green * .8, blue * .8);
	m_darkerFillColor = sf::Color(red * .5, green * .5, blue * .5);
}


void Button::handleColors() {
	/*
	Insert Specification
	*/

	if (m_hasTexture) {
		m_fillColor = sf::Color::Transparent;
		m_darkFillColor = sf::Color::Transparent;
		m_darkerFillColor = sf::Color::Transparent;
	}

	m_body.setFillColor(m_fillColor);

	if (!isBackGround()) {
		if (isHovered()) {
			m_body.setFillColor(m_darkFillColor);
			if (m_hasTexture) {
				m_sprite.setColor(sf::Color(204, 204, 204));  // 80% brightness, no pixel loop needed
			}
			if (isPressed() && !m_dragging) {
				m_body.setFillColor(m_darkerFillColor);
				m_sprite.setColor(sf::Color(128, 128, 128));  // 50% brightness, no pixel loop needed	
			}
		}
		else {
			m_body.setFillColor(m_fillColor);
			if (m_hasTexture) {
				m_sprite.setColor(sf::Color::White);  // Reset to original color
			}
		}
	}
}

void Button::handleMouseClick(sf::Vector2f clickPos) {

	if (m_circle.getGlobalBounds().contains(clickPos)) {
		m_dragging = true;
	}

	if (m_bufferedBounds.contains(clickPos)) {
		m_clickedInside = true;
	}
}

void Button::handleMove() {
	/*
	Insert Specification
	*/
	if (!isBackGround() && !isStationary()) {
		if (!Game::isMousePressed()) {
			m_dragging = false;
		}

		if (m_dragging) {
			sf::Vector2f mouse{ Game::getMousePosition() };
			m_body.setPosition(mouse);
			m_circle.setPosition(mouse);
			m_bufferedBounds.position = { mouse.x + m_buffer, mouse.y + m_buffer };
			if (m_hasTexture) {
				m_sprite.setPosition(mouse);
			}
		}
	}
}

void Button::setSize(sf::Vector2f size) {
	m_body.setSize(size);
	if (m_hasTexture) {
		sf::Vector2u textureSize = m_texture.getSize();
		m_sprite.setScale({
			size.x / textureSize.x,
			size.y / textureSize.y
			});
	}
}

void Button::setCenter(sf::Vector2f center) {
	sf::Vector2f pos = center - (m_body.getSize() / 2.f);
	m_body.setPosition(pos);
	if (m_hasTexture) {
		m_sprite.setPosition(pos);
	}
}

void Button::move(sf::Vector2f offset) {
	m_body.move(offset);
	m_circle.move(offset);
	m_bufferedBounds.position += offset;
	if (m_hasTexture) {
		m_sprite.move(offset);
	}
}

bool Button::isHovered() {
	/*
	Insert Specification
	*/

	sf::Vector2f mouse{ Game::getMousePosition() };

	if (m_body.getGlobalBounds().contains(mouse)
		|| m_circle.getGlobalBounds().contains(mouse)) {
		return true;
	}
	return false;
}

bool Button::isPressed() { // IF THE MOUSE IS PRESSED, NOT SPECIFICALLY THE BUTTON
	bool pressed{ sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) };

	return pressed;
}

void Button::update() {
	handleColors();
	handleMove();

	if (!isPressed() && m_dragging) {
		m_dragging = false;
	}

	if (isHovered() && isPressed() && !m_pressed && m_clickedInside) {
		if (m_action != nullptr) {
			m_action();
		}
		if (m_hasSound) {
			m_sound.play();
		}
		m_pressed = true;
	}

	if (!isPressed()) {
		m_pressed = false;
		m_clickedInside = false;  
	}
}

void Button::setFunction(ButtonFunction action) {
	m_action = action;
}

void Button::setSound(const std::filesystem::path& filePath) {
	if (m_soundBuffer.loadFromFile(filePath)) {
		m_sound.setBuffer(m_soundBuffer);
		m_hasSound = true;
	}
}

void Button::setTexture(const std::filesystem::path& filePath) {
		if (m_texture.loadFromFile(filePath)) {
		m_sprite.setTexture(m_texture, true);
		m_hasTexture = true;

		sf::Vector2f buttonSize = m_body.getSize();
		sf::Vector2u textureSize = m_texture.getSize();
		m_sprite.setScale({
			buttonSize.x / textureSize.x,
			buttonSize.y / textureSize.y
			});
		m_sprite.setPosition(m_body.getPosition());
	}
}

