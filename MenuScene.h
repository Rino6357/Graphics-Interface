#pragma once
#include "Scene.h"

class MenuScene : public Scene {
public:
    MenuScene(Game* game);
    void handleKeyPress(std::optional<sf::Event> event) override;
};