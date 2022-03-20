#include <iostream>
#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "ResourceManager.hpp"
#include "Matrix3.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Island RPG", sf::Style::Default, settings);
    // window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::ContextSettings settings2 = window.getSettings();
    std::cout << "depth bits:" << settings2.depthBits << std::endl;
    std::cout << "stencil bits:" << settings2.stencilBits << std::endl;
    std::cout << "antialiasing level:" << settings2.antialiasingLevel << std::endl;
    std::cout << "version:" << settings2.majorVersion << "." << settings2.minorVersion << std::endl;

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
                windowFocused = false;
                break;
            case sf::Event::GainedFocus:
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