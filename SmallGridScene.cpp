#include "SmallGridScene.h"
#include "Game.h"

SmallGridScene::SmallGridScene(Game* game)
    : Scene{ game } {
    sf::Vector2f windowSize = m_game->getWindowSize();
    sf::Vector2f windowCenter = windowSize / 2.f;

    m_buttons.push_back(std::make_unique<Button>(sf::Vector2f{ 0, 0 }, windowSize.x, windowSize.y));
    m_buttons.back()->setBackGround(true);
    m_buttons.back()->setColors(sf::Color(206, 237, 177));

    float baseScreenDimension{ std::min(windowSize.x, windowSize.y) };
    float bigGridSize{ baseScreenDimension * 0.80f };
    float currentScale{ bigGridSize / 83.f };

    float smallGridSize{ 23.f * currentScale };
    float gridStep{ 28.f * currentScale };
    float firstGridOffset{ 39.5f * currentScale };

    float cellSize{ 5.f * currentScale };
    float cellStep{ 8.f * currentScale };
    float firstCellOffset{ 1.f * currentScale };

    m_buttons.push_back(std::make_unique<Button>(
        sf::Vector2f{
            windowCenter.x - (bigGridSize / 2.f),
            windowCenter.y - (bigGridSize / 2.f)
        },
        bigGridSize, bigGridSize
    ));
    m_buttons.back()->setOutlineTrans();
    m_buttons.back()->setStationary(true);
    m_buttons.back()->setInteractable(false);
    m_buttons.back()->setUntouchable(true);
    m_buttons.back()->setTexture("Textures/GridBig.png");

    int count{ 0 };

    for (int i{ 0 }; i < 3; ++i) {
        for (int j{ 0 }; j < 3; ++j) {

            float subGridX = windowCenter.x - firstGridOffset + (gridStep * j);
            float subGridY = windowCenter.y - firstGridOffset + (gridStep * i);

            // create inner grid
            m_buttons.push_back(std::make_unique<Button>(
                sf::Vector2f{ subGridX, subGridY },
                smallGridSize, smallGridSize
            ));
            m_buttons.back()->setColors(sf::Color::Transparent);
            m_buttons.back()->setOutlineTrans();
            m_buttons.back()->setStationary(true);
            m_buttons.back()->setInteractable(true);
            m_buttons.back()->setBoxHover(true);
            m_buttons.back()->setTexture("Textures/EmptyBig.png");

            m_buttons.back()->setFunction([this, count] {
                m_currentGrid->setMark(count, SmallGrid::Circle);
                m_currentGrid->refresh();
                refresh();
            });

            m_marks[count] = m_buttons.back().get();
            ++count;

        }
    }
}

void SmallGridScene::handleKeyPress(std::optional<sf::Event> event) {
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
            m_game->popScene();
        }
    }
}

void SmallGridScene::refresh() {
    for (int i{ 0 }; i < 9; ++i) {
        switch (m_currentGrid->getMarkStates()[i]) {
        case SmallGrid::Circle:
            m_marks[i]->setTexture("Textures/CircleBig.png");
            break;
        case SmallGrid::Cross:
            m_marks[i]->setTexture("Textures/CrossBig.png");
            break;
        case SmallGrid::Empty:
            m_marks[i]->setTexture("Textures/EmptyBig.png");
        }
    }
}

void SmallGridScene::setActiveGrid(SmallGrid* grid) {
    m_currentGrid = grid;
    refresh();
}
