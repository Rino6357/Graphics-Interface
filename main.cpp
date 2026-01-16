#include <SFML/Graphics.hpp>
#include <iostream>
#include "Leg.h"
#include "Constants.h"
#include "Button.h"

// skibidi

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Workspace");

    sf::Clock clock;

    Button button{ {100,100}, 100, 100, &window};
    button.setColors(sf::Color::Blue);

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        button.update();
        window.clear(sf::Color(50, 40, 80));
        button.draw(&window);
        window.display();
    }
}
