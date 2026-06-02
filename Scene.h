#pragma once
#include <vector>
#include <memory>
#include "Button.h"
#include "TextBox.h"

class Game;

class Scene
{
public:
	Scene(Game* game) : m_game{ game } {}
	virtual ~Scene() = default;
	virtual void update();
	virtual void draw(sf::RenderWindow* window);
	virtual void handleKeyPress(std::optional<sf::Event> event) {};
	void handleMouseClick(sf::Vector2f clickPos);
	void repositionButtons(float newWidth, float newHeight);
	void setInteractable(bool interactable);

private:
	sf::Vector2f m_windowSize{ 1280.f, 800.f };

protected:
	std::vector<std::unique_ptr<Button>> m_buttons;
	Game* m_game{ nullptr };

};