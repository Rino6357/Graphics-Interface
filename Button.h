#pragma once
#include <iostream>
#include <functional>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <SFML/Audio.hpp>

using ButtonFunction = std::function<void()>;

class Button
{
public:
	Button(sf::Vector2f position, float width, float height);

	void draw(sf::RenderWindow* view);

	void setColors(sf::Color color);

	void handleColors();

	void handleMove();

	void handleMouseClick(sf::Vector2f clickPos);

	void setFunction(ButtonFunction action);

	void setSound(const std::filesystem::path& filePath);

	void setTexture(const std::filesystem::path& filePath);

	bool isHovered();

	bool isPressed();

	void update();

private:
	sf::RectangleShape m_body{};
	float m_buffer{ 10.0f };
	sf::FloatRect m_bufferedBounds{};
	sf::CircleShape m_circle{5};
	sf::Color m_fillColor{};
	sf::Color m_darkFillColor{};
	sf::Color m_darkerFillColor{};
	sf::Color m_outlineColor{ sf::Color::White };
	float m_outlineThickness{1};
	sf::RenderWindow* m_view{};
	ButtonFunction m_action{NULL};
	bool m_dragging{ false };
	bool m_pressed{ false };
	bool m_clickedInside{ false };
	bool m_hasSound{ false };
	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_sound{ m_soundBuffer };
	sf::Texture m_texture;
	sf::Sprite m_sprite{ m_texture };
	bool m_hasTexture{ false };
	sf::Image m_image;
	sf::Image m_imageBuffer;	
};

