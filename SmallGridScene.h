#pragma once
#include "Scene.h"
#include "SmallGrid.h"

class SmallGridScene : public Scene {
public:
	SmallGridScene(Game* game);
	void handleKeyPress(std::optional<sf::Event> event) override;
	void setActiveGrid(SmallGrid* grid);
	void refresh();

private:
	std::array<Button*, 9> m_marks{};
	SmallGrid* m_currentGrid{};
};

