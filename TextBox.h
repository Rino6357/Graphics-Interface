#pragma once
#include "Button.h"

class TextBox : public Button
{
public:
	TextBox(sf::Vector2f position, float width, float height,
		std::string_view text, const std::filesystem::path& filePath);

    void draw(sf::RenderWindow* view) override;
	void move(sf::Vector2f offset) override;

	std::optional<sf::Text>& getText() { return m_text; }

private:
	std::string m_textString;
	sf::Font m_font;
	std::optional<sf::Text> m_text;
	int m_size{ 50 };
	sf::Color m_fillColor{ sf::Color::Black };
};

