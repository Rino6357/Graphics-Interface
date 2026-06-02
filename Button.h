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

	void setOutlineTrans() { m_body.setOutlineColor(sf::Color::Transparent); }

	void setFunction(ButtonFunction action);

	void setSound(const std::filesystem::path& filePath);

	void setTexture(const std::filesystem::path& filePath);

	void setBackGround(bool stationary) {
		m_isBackGround = stationary;
		m_isStationary = stationary;
	}

	bool isBackGround() const {
		return m_isBackGround;
	}	

	void setStationary(bool stationary) {
		m_isStationary = stationary;
	}

	bool isStationary() const {
		return m_isStationary;
	}

	void setInteractable(bool interactable) { m_interactable = interactable; }
	bool isInteractable() const { return m_interactable; }

	void setSize(sf::Vector2f size);

	void setCenter(sf::Vector2f center);

	void move(sf::Vector2f offset);

	bool isHovered();

	bool isPressed();

	void update();

private:
	sf::RectangleShape m_body{};
	float m_buffer{ 5.0f };
	bool m_isBackGround{ false };
	bool m_isStationary{ false };
	bool m_interactable{ true };
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

