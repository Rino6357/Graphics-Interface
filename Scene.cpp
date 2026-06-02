#include "Scene.h"
#include "Game.h"

void Scene::update() {
    for (auto& c : m_buttons) {
        c.update();
    }
}

void Scene::draw(sf::RenderWindow* window) {
    for (auto& c : m_buttons) {
        c.draw(window);
    }
}

void Scene::handleMouseClick(sf::Vector2f clickPos) {
    for (auto& c : m_buttons) {
        c.handleMouseClick(clickPos);
    }
}

void Scene::repositionButtons(float newWidth, float newHeight) {
    sf::Vector2f delta = (sf::Vector2f{ newWidth, newHeight } - m_windowSize) / 2.f;
    for (auto& button : m_buttons) {
        if (button.isBackGround()) {
            button.setSize({ newWidth, newHeight });
            button.setCenter({ newWidth / 2.f, newHeight / 2.f });
        }
        else {
            button.move(delta);
        }
    }
    m_windowSize = { newWidth, newHeight };
}

void Scene::setInteractable(bool interactable) {
    for (auto& c : m_buttons) {
        c.setInteractable(interactable);
    }
}