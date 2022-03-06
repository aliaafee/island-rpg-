#include <iostream>
#include <SFML/Graphics.hpp>

#include "World.h"

#include "Matrix3.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works alright!");
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(120);

    World *world = new World(100, 100);

    bool windowFocused = false;

    sf::Clock clock;
    while (window.isOpen())
    {
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
                windowFocused = false;
                break;
            case sf::Event::GainedFocus:
                std::cout << "Gained focus"
                          << "\n";
                windowFocused = true;
                break;
            default:
                break;
            }
        }

        if (windowFocused)
        {
            sf::Time elapsed = clock.restart();
            world->update(elapsed);

            world->transform();

            window.clear(sf::Color::White);
            world->draw(&window);
            window.display();
        }
    }

    delete world;
    return 0;
}