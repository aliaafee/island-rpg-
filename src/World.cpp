#include "World.hpp"

World::World(sf::RenderWindow &window,
             ResourceManager &rm,
             int64_t width, int64_t height) : window_(&window),
                                              rm_(&rm),
                                              player_(new Player(rm)),
                                              cursor_(new ShaderEntity(rm)),
                                              pathfinder_(
                                                  Vector3f(0, 0, 0),
                                                  600, 600,
                                                  60, 60)
{
    std::cout << "Creating World"
              << "\n";

    pathfinder_.clearGrid();

    addEntity(player_);
    player_->move(20, 20, 0);

    addEntity(cursor_);
    //cursor_->setSize(Vector3f(5, 5, 5));

    Entity *grid = new PathfinderGrid(pathfinder_);
    addEntity(grid);

    Entity *sh = new ShaderEntity(*rm_);
    addEntity(sh);
    sh->move(40, 40,0);
    pathfinder_.addObstacle(*sh);
    

    TrackingCamera *camera = new TrackingCamera(Vector3f(0, 0, 0),
                                                Vector3f(800 / 2, 600 / 2, 0),
                                                Vector2f(64, 32),
                                                10,
                                                window.getSize().x, window.getSize().y);

    camera->setTrackTarget(*player_, 1, 5, 60);

    camera_ = camera;

    // addEntity(new Player(rm_));

    // addEntity(new Player(rm_));

    // entities_[0]->setPosition(Vector3f(0, 20, 0));
    // // entities_[1]->setPosition(Vector3f(0, 30, 10));

    // Entity *a;
    // for (float i; i < 10; i++)
    // {
    //     a = new Player(rm_);
    //     a->setPosition(Vector3f(20 + i * 6, 0, 0));
    //     addEntity(a);
    // }
}

World::~World()
{
    std::cout << "Destroying World"
              << "\n";

    for (auto &entity : entities_)
    {
        delete entity;
    }
    entities_.clear();
}

void World::input_(sf::Time &elapsed)
{
    // Cursor
    Vector2f mousePosition = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
    cursor_->setPosition(
        camera_->projectGround(mousePosition));

    // Camera Pan
    float speed = elapsed.asSeconds() * 4.0 * 60;
    Vector2f panDir(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        panDir.x = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        panDir.x = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        panDir.y = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        panDir.y = speed;
    }
    if (abs(panDir.x) > 0 || abs(panDir.y) > 0)
    {
        camera_->pan(panDir);
    }
}

void World::update(sf::Time &elapsed)
{
    camera_->updateWindow(*window_);

    input_(elapsed);

    for (auto &entity : entities_)
    {
        entity->update(elapsed, *this);
    }

    camera_->update(elapsed);
}

void World::transform()
{
    for (auto &entity : entities_)
    {
        entity->transform(*camera_);
    }
}

void World::draw(sf::RenderTarget *screen)
{
    std::sort(entities_.begin(), entities_.end(), entityDepthComp);

    for (auto &entity : entities_)
    {
        entity->draw(screen);
    }
}

void World::addEntity(Entity *entity)
{
    entities_.push_back(entity);
}

void World::onMouseButtonReleased(const sf::Event &event)
{
    std::cout << "Mouse Release ";
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        std::cout << "Left"
                  << "\n";
        player_->walkTo(cursor_->getPosition());
    }
    else if (event.mouseButton.button == sf::Mouse::Right)
    {
        std::cout << "Right"
                  << "\n";
        pathfinder_.addObstacle(*cursor_);
    }
}

void World::onMouseWheelScrolled(const sf::Event &event)
{
    if (event.mouseWheelScroll.delta < 0)
    {
        camera_->zoom(1.1);
    }
    else
    {
        camera_->zoom(0.9);
    }
}

const std::vector<Entity *> &World::getEntitys() const
{
    return entities_;
}