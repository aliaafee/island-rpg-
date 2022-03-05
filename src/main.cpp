#include <iostream>
#include <SFML/Graphics.hpp>

#include "world.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works alright!");
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    World *world = new World(100, 100);

    sf::Clock clock;
    while (window.isOpen())
    {
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::LostFocus:
                std::cout << "Lost focus"
                          << "\n";
                break;
            case sf::Event::GainedFocus:
                std::cout << "Gained focus"
                          << "\n";
                break;
            default:
                break;
            }
        }

        world->update();
        world->transform();

        window.clear(sf::Color::Black);
        world->draw(&window);
        window.display();
    }

    delete world;
    return 0;
}