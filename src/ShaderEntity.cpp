#include "ShaderEntity.hpp"

ShaderEntity::ShaderEntity(ResourceManager &rm) : rect_(Vector2f(100, 100)),
                                                  arr(sf::Quads, 4)
{
    rect_.setFillColor(sf::Color::Red);
    rect_.setOrigin(50, 100);

    if (!shader_.loadFromFile("graphics/shaders/test.vert", "graphics/shaders/test.frag"))
    {
        std::cout << "Could not load shader" << std::endl;
    }

    arr[0].position = Vector2f(0, 0);
    arr[1].position = Vector2f(0, 64);
    arr[2].position = Vector2f(64, 64);
    arr[3].position = Vector2f(64, 0);

    arr[0].texCoords = Vector2f(0, 0);
    arr[1].texCoords = Vector2f(0, 1);
    arr[2].texCoords = Vector2f(1, 1);
    arr[3].texCoords = Vector2f(1, 0);

    arr[0].color = sf::Color::Black;
    arr[1].color = sf::Color::Red;
    arr[2].color = sf::Color::Green;
    arr[3].color = sf::Color::Blue;

    rs.shader = &shader_;
}

ShaderEntity::~ShaderEntity()
{
}

void ShaderEntity::transform(Camera &camera)
{
    Entity::transform(camera);
    rect_.setPosition(getScreenPosition2());

    rs.transform = sf::Transform(1, 0, getScreenPosition2().x - 32,
                                 0, 1, getScreenPosition2().y - 64,
                                 0, 0, 1);
}

void ShaderEntity::draw(sf::RenderTarget *screen)
{
    Entity::draw(screen);

    // screen->draw(rect_, &shader_);
    screen->draw(arr, rs);
}
