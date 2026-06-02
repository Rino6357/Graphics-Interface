#pragma once
#include "Scene.h"

class PlayScene : public Scene {
public:
    PlayScene(Game* game);
    void handleKeyPress(std::optional<sf::Event> event) override;
};

