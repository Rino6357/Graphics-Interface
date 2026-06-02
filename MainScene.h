#pragma once
#include "Scene.h"
#include "Constants.h"
#include "Random.h"

class MainScene : public Scene {
public:
    MainScene(Game* game);
    void handleKeyPress(std::optional<sf::Event> event) override;
};