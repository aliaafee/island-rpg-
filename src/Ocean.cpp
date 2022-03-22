#include "Ocean.hpp"

Ocean::Ocean(ResourceManager &rm) : rect_(Vector2f(100, 100)),
                                    arr(sf::Quads, 4),
                                    shaderLoaded_(false)
{
    rect_.setFillColor(sf::Color::Red);
    rect_.setOrigin(50, 100);

    if (!shader_.loadFromFile("graphics/shaders/ocean.vert", "graphics/shaders/ocean.frag"))
    {
        std::cout << "Could not load shader" << std::endl;
        shaderLoaded_ = false;
    }
    else
    {
        shaderLoaded_ = true;
    }

    arr[0].position = Vector2f(32, 0) * 100.f;
    arr[1].position = Vector2f(64, 16) * 100.f;
    arr[2].position = Vector2f(32, 32) * 100.f;
    arr[3].position = Vector2f(0, 16) * 100.f;

    // arr[0].texCoords = Vector2f(0.5, 0);
    // arr[1].texCoords = Vector2f(1.0, 0.25);
    // arr[2].texCoords = Vector2f(0.5, 0.5);
    // arr[3].texCoords = Vector2f(0, 0.25);

    for (int i = 0; i < arr.getVertexCount(); i++)
    {
        arr[i].texCoords = arr[i].position;
    }

    arr[0].color = sf::Color::Black;
    arr[1].color = sf::Color::Red;
    arr[2].color = sf::Color::Green;
    arr[3].color = sf::Color::Blue;

    // shader_.setUniform("textureSize", Vector2f(64, 64));
    shader_.setUniform("textureSize", Vector2f(1, 1));
    // shader_.setUniform("screenPosition", getScreenPosition());
    shader_.setUniform("worldPosition", getPosition());
    shader_.setUniform("screenSize", Vector2f(800, 300));

    rs.shader = &shader_;
}

Ocean::~Ocean()
{
}

void Ocean::update(sf::Time &elapsed, World &world)
{
    shader_.setUniform("iTime", clock_.getElapsedTime().asSeconds());
}

void Ocean::transform(Camera &camera)
{
    Entity::transform(camera);
    rect_.setPosition(getScreenPosition2());

    arr[0].position = Vector2f(32, 0) * getSize().x / 10.f;
    arr[1].position = Vector2f(64, 16) * getSize().x / 10.f;
    arr[2].position = Vector2f(32, 32) * getSize().x / 10.f;
    arr[3].position = Vector2f(0, 16) * getSize().x / 10.f;

    for (int i = 0; i < arr.getVertexCount(); i++)
    {
        arr[i].texCoords = arr[i].position;
    }

    rs.transform = sf::Transform(1, 0, getScreenPosition2().x - arr.getBounds().width / 2.0,
                                 0, 1, getScreenPosition2().y,
                                 0, 0, 1);

    shader_.setUniform("screenPosition", getScreenPosition());
    shader_.setUniform("worldPosition", camera.transform(getPosition(), 0));
    shader_.setUniform("screenSize", Vector2f(800, 300));
    shader_.setUniform("size", 7.f);
}

void Ocean::draw(sf::RenderTarget *screen)
{
    sf::Transform t = screen->getView().getTransform();

    shader_.setUniform("viewMatrix", sf::Glsl::Mat4(t.getMatrix()));
    // Entity::draw(screen);

    // screen->draw(rect_, &shader_);

    if (!shaderLoaded_)
        return;

    screen->draw(arr, rs);
}
