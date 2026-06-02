#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Constants.h"
#include "Button.h"
#include "Scene.h"
#include "MainScene.h"
#include "MenuScene.h"
#include "StartMenu.h"
#include "PlayScene.h"

class Game
{
public:
	Game();

	~Game() = default;

	void run();

	static sf::Vector2f getMousePosition() {
		return m_mouse;
	}
	
	static bool isMousePressed() {
		return m_mousePressed;
	}

	enum SceneID {
		Main,
		Menu,
		Start,
		Play
	};

	Scene* getScene(SceneID id);
	void switchScene(Scene* scene); // replaces top of stack
	void popScene();
	void pushScene(Scene* scene);
	sf::Vector2f getWindowSize() { return static_cast<sf::Vector2f>(m_window.getSize()); }



private:

	void update();
	void processEvents();
	void draw();
	void handleMouse(std::optional<sf::Event> event);
	void handleResize(std::optional<sf::Event> event);
	void handleKeys(std::optional<sf::Event> event);
	void toggleFullscreen();

	static sf::Vector2f m_mouse;
	static bool m_mousePressed;

	sf::RenderWindow m_window;
	sf::Vector2f m_windowSize{ static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y) };
	sf::View m_view;
	sf::Clock m_clock{};
	bool m_isFullscreen{ false };

	std::vector<Scene*> m_scenes;
	MainScene m_mainScene;
	MenuScene m_menuScene;
	StartMenu m_startMenu;
	PlayScene m_playScene;
};

