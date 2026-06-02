#include "PlayScene.h"
#include "Game.h"

PlayScene::PlayScene(Game* game) : Scene{ game } {
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

    for (int i{ 0 }; i < 3; ++i) {
        for (int j{ 0 }; j < 3; ++j) {

            float subGridX = windowCenter.x - firstGridOffset + (gridStep * i);
            float subGridY = windowCenter.y - firstGridOffset + (gridStep * j);

            // create inner grid
            m_buttons.push_back(std::make_unique<Button>(
                sf::Vector2f{ subGridX, subGridY },
                smallGridSize, smallGridSize
            ));
            m_buttons.back()->setOutlineTrans();
            m_buttons.back()->setStationary(true);
            m_buttons.back()->setInteractable(true);
            m_buttons.back()->setTexture("Textures/GridSmall.png");

            // create x/o objects
            for (int cellI{ 0 }; cellI < 3; ++cellI) {
                for (int cellJ{ 0 }; cellJ < 3; ++cellJ) {

                    m_buttons.push_back(std::make_unique<Button>(
                        sf::Vector2f{
                            subGridX + firstCellOffset + (cellStep * cellI),
                            subGridY + firstCellOffset + (cellStep * cellJ)
                        },
                        cellSize, cellSize
                    ));
                    m_buttons.back()->setOutlineTrans();
                    m_buttons.back()->setStationary(true);
                    m_buttons.back()->setInteractable(true);
                    m_buttons.back()->setUntouchable(false);
                    m_buttons.back()->setTexture("Textures/Circle.png");
                }
            }

        }
    }
}

void PlayScene::handleKeyPress(std::optional<sf::Event> event) {
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
            m_game->popScene();
        }
    }
}
