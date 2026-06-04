#pragma once
#include "Scene.h"
#include "BigGrid.h"
#include "SmallGrid.h"
#include "SmallGridScene.h"

class PlayScene : public Scene {
public:
    PlayScene(Game* game);
    void handleKeyPress(std::optional<sf::Event> event) override;

	enum Grid {
		TopLeft,
		TopMiddle,
		TopRight,
		CenterLeft,
		CenterMiddle,
		CenterRight,
		BottomLeft,
		BottomMiddle,
		BottomRight
	};

private:
    BigGrid m_bigGrid;
};

