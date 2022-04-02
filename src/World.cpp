#include "World.hpp"

World::World(sf::RenderWindow &window,
             ResourceManager &rm,
             int64_t width, int64_t height) : window_(&window),
                                              rm_(&rm),
                                              camera_(
                                                  new TrackingCamera(Vector3f(0, 0, 0),
                                                                     Vector3f(
                                                                         window.getSize().x / 2,
                                                                         window.getSize().y / 2,
                                                                         0),
                                                                     Vector2f(64, 32),
                                                                     10,
                                                                     window.getSize().x,
                                                                     window.getSize().y)),
                                              worldConfig_(
                                                  4000000.f, 4000000.f,
                                                  10000, 10000,
                                                  40, 40,
                                                  *camera_),
                                              player_(new Player(rm)),
                                              cursor_(rm),
                                              ocean_(rm),
                                              pathfinder_(
                                                  Vector3f(0, 0, 0),
                                                  worldConfig_),
                                              pathfinderGrid_(pathfinder_),
                                              activeCellId_(-1)
{
    ocean_.setSize(
        worldConfig_.getCellWidth() * 3.f,
        worldConfig_.getCellHeight() * 3.f,
        0);

    addEntity(player_);
    // player_->setPosition(198062, 198901, 0);
    player_->setPosition(2854, 2864, 0);

    cursor_.setSize(Vector3f(5, 5, 5));

    TrackingCamera *camera = reinterpret_cast<TrackingCamera *>(camera_);
    camera->setTrackTarget(*player_, 1, 5, 60);
    camera->setZoom(0.75);
    camera->setPosition(player_->getPosition());

    Entity *fire = addEntity(new FirePit(*rm_));
    fire->setPosition(player_->getPosition() + Vector3f(30, 30, 0));
}

World::~World()
{
    for (auto &entity : entities_)
    {
        delete entity;
    }

    for (auto &item : cellCache_)
    {
        delete item.second;
    }

    entities_.clear();
}

void World::input_(sf::Time &elapsed)
{
    // Cursor
    Vector2f mousePosition = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
    cursor_.setPosition(
        camera_->projectGround(mousePosition));

    // Camera Pan
    // float speed = elapsed.asSeconds() * 4.0 * 60;
    // Vector2f panDir(0, 0);
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    // {
    //     panDir.x = speed;
    // }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    // {
    //     panDir.x = -speed;
    // }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    // {
    //     panDir.y = -speed;
    // }
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    // {
    //     panDir.y = speed;
    // }
    // if (std::abs(panDir.x) > 0 || std::abs(panDir.y) > 0)
    // {
    //     camera_->pan(panDir);
    // }
}

void World::updateCells_()
{
    int cellId = worldConfig_.getId(player_->getPosition());
    if (cellId == activeCellId_)
    {
        return;
    }

    activeCellId_ = cellId;

    std::cout << "Updating cells\n";
    activeCells_.clear();

    int min_i = worldConfig_.rows();
    int min_j = worldConfig_.cols();
    int max_i = 0;
    int max_j = 0;
    for (auto [i, j] : worldConfig_.getAdjacentIds(player_->getPosition(), 9))
    {
        WorldCell *currentCell;

        auto search = cellCache_.find(worldConfig_.getId(i, j));
        if (search == cellCache_.end())
        {
            currentCell = new WorldCell(
                *rm_,
                worldConfig_,
                i, j);
            cellCache_[worldConfig_.getId(i, j)] = currentCell;
        }
        else
        {
            currentCell = search->second;
        }

        activeCells_.push_back(currentCell);

        if (i < min_i)
            min_i = i;
        if (j < min_j)
            min_j = j;
        if (i > max_i)
            max_i = i;
        if (j > max_j)
            max_j = j;
    }

    pathfinder_.setPosition(
        worldConfig_.getCellPosition(min_i, min_j));

    pathfinder_.setActiveCells(min_i, min_j, activeCells_);

    ocean_.setPosition(pathfinder_.getPosition());

    for (auto &cell : activeCells_)
    {
        cell->translateOrigin(pathfinder_.getPosition());
    }

    for (auto &entity : entities_)
    {
        entity->translateOrigin(pathfinder_.getPosition());
    }

    cursor_.translateOrigin(pathfinder_.getPosition());
}

void World::updateVisibileList_()
{
    visibleEntities_.clear();
    floorEntities_.clear();

    visibleEntities_ = entities_;
    for (auto &cell : activeCells_)
    {
        for (auto entity : cell->getEntities())
        {
            visibleEntities_.push_back(entity);
        }
        floorEntities_.push_back(cell->getFloor());
    }
}

void World::update(sf::Time &elapsed)
{
    ocean_.update(elapsed, *this);

    updateCells_();
    updateVisibileList_();

    camera_->updateWindow(*window_);

    input_(elapsed);

    for (auto &entity : floorEntities_)
    {
        entity->update(elapsed, *this);
    }

    for (auto &entity : visibleEntities_)
    {
        entity->update(elapsed, *this);
    }

    camera_->update(elapsed);
}

void World::transform()
{
    ocean_.transform(*camera_);

    for (auto &entity : floorEntities_)
    {
        entity->transform(*camera_);
    }

    pathfinderGrid_.transform(*camera_);

    for (auto &entity : visibleEntities_)
    {
        entity->transform(*camera_);
    }

    cursor_.transform(*camera_);
}

void World::draw(sf::RenderTarget *screen)
{
    ocean_.draw(screen);

    std::sort(floorEntities_.begin(), floorEntities_.end(), entityDepthComp);

    for (auto &entity : floorEntities_)
    {
        entity->draw(screen);
    }

    pathfinderGrid_.draw(screen);

    std::sort(visibleEntities_.begin(), visibleEntities_.end(), entityDepthComp);

    for (auto &entity : visibleEntities_)
    {
        entity->draw(screen);
    }

    cursor_.draw(screen);
}

Entity *World::addEntity(Entity *entity)
{
    entities_.push_back(entity);
    return entity;
}

void World::onMouseButtonReleased(const sf::Event &event)
{
    // std::cout << "Mouse Release ";
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        // std::cout << "Left"
        //           << "\n";
        for (auto &entity : visibleEntities_)
        {
            if (entity != player_)
            {
                if (entity->collision(cursor_))
                {
                    std::cout << "clicked entity\n";
                    std::cout << entity->getPosition() << "\n";
                    player_->attackOther(*entity);
                    return;
                }
            }
        }
        player_->walkTo(cursor_.getPosition());
        std::cout << "e" << worldConfig_.getElevation(cursor_.getPosition()) << "\n";
    }
    else if (event.mouseButton.button == sf::Mouse::Right)
    {
        // std::cout << "Right"
        //           << "\n";
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

bool World::findPath(const Entity &entity, const Vector3f &end,
                     const bool &diagonal,
                     std::deque<Vector3f> &resultPath)
{
    // if (!canMoveTo(entity, entity.getLocalPosition()))
    // {
    //     std::cout << "Entity is at an invalid position...";
    //     Vector3f validPos;
    //     if (pathfinder_.findFreePosition(entity.getPosition(), validPos))
    //     {
    //         std::cout << "Consider move to " << validPos;
    //     }
    //     std::cout << "\n";
    //     return false;
    // }
    return pathfinder_.findPath(entity.getPosition(), end, diagonal, resultPath);
}

bool World::canMoveTo(const Entity &entity, const Vector3f &localPoint) const
{
    if (!pathfinder_.isAreaFree(localPoint, entity.getSize() * 0.8f))
        return false;

    for (auto &e : entities_)
    {
        if (e != &entity)
        {
            if (e->collision(localPoint, entity.getSize()))
            {
                return false;
            }
        }
    }
    return true;
}

bool World::findNearbyFreePosition(const Vector3f &position, Vector3f &out_position)
{
    return pathfinder_.findFreePosition(position, out_position);
}
