#pragma once
#include "Button.h"

class TextBox : public Button
{
public:
	TextBox(sf::Vector2f position, float width, float height, std::string_view text)
		: Button{ position, width, height }, m_text{ text } { 

	}

private:
	std::string m_text;
};

