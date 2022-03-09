#include <iostream>
#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "ResourceManager.hpp"
#include "Matrix3.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Island RPG");
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    
    ResourceManager rm;
    World world(&window, &rm, 100, 100);

    sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    //view.setViewport(sf::FloatRect(0.5f, 0.5f, 0.5f, 0.5f));
    view.zoom(1.f);
    window.setView(view);

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