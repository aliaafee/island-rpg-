#include <iostream>
#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "ResourceManager.hpp"
#include "Matrix3.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Island RPG", sf::Style::Default, settings);
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    ResourceManager rm;
    World world(window, rm, 100, 100);

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
            case sf::Event::MouseButtonReleased:
                world.onMouseButtonReleased(event);
                break;
            case sf::Event::MouseWheelScrolled:
                world.onMouseWheelScrolled(event);
                break;
            default:
                break;
            }
        }

        if (windowFocused)
        {
            sf::Time elapsed = clock.restart();
            world.update(elapsed);

            world.transform();

            window.clear(sf::Color::White);
            world.draw(&window);
            window.display();
        }
    }
    return 0;
}