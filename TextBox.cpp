#include "TextBox.h"

TextBox::TextBox(sf::Vector2f position, float width, float height, std::string_view text, const std::filesystem::path& filePath)
	: Button{ position, width, height }, m_textString{ text } {
	if (m_font.openFromFile(filePath)) {
		m_text.emplace(m_font, m_textString);
		m_text->setCharacterSize(m_size);

		sf::FloatRect textBounds = m_text->getLocalBounds();
		m_text->setOrigin({ textBounds.position.x + textBounds.size.x / 2.f,
							textBounds.position.y + textBounds.size.y / 2.f });
		m_text->setPosition({ m_body.getPosition().x + m_body.getSize().x / 2.f,
							  m_body.getPosition().y + m_body.getSize().y / 2.f });
	}
}

void TextBox::draw(sf::RenderWindow* view) {
	Button::draw(view);
	view->draw(*m_text);
}

void TextBox::move(sf::Vector2f offset) {
	Button::move(offset);
	if (m_text.has_value()) {
		m_text->move(offset);
	}
}
