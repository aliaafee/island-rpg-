#include "WorldCell.hpp"

WorldCell::WorldCell(ResourceManager &rm,
                     WorldConfig &worldConfig,
                     const int &i, const int &j) : rm_(&rm),
                                                   worldConfig_(&worldConfig),
                                                   position_(worldConfig_->getCellPosition(i, j)),
                                                   cell_i_(i),
                                                   cell_j_(j),
                                                   width_(worldConfig_->getCellWidth()),
                                                   height_(worldConfig_->getCellHeight()),
                                                   placeholder_(
                                                       width_,
                                                       height_,
                                                       1, 1),
                                                   loaded_(false),
                                                   floor_(nullptr),
                                                   obstacleGrid_(
                                                       worldConfig_->subCols(),
                                                       worldConfig_->subRows())
{
    placeholder_.setPosition(position_);
    placeholders_.push_back(&placeholder_);

    loadThread_ = std::thread(&WorldCell::load, this);
    // loadThread_.join();
}

WorldCell::~WorldCell()
{
    std::cout << "Destroying World Cell " << cell_i_ << ", " << cell_j_
              << "\n";

    if (loadThread_.joinable())
        loadThread_.join();

    if (!loaded_)
        return;

    for (auto &entity : entities_)
    {
        delete entity;
    }
    entities_.clear();

    if (floor_ != nullptr)
        delete floor_;
}

int WorldCell::getId()
{
    return worldConfig_->getId(cell_i_, cell_j_);
}

void WorldCell::load()
{
    obstacleGrid_.clear(1);

    srand(getId());

    floor_ = new Ground(*rm_, position_, width_, height_, 40, 40, *worldConfig_);

    Entity *e;
    for (int i = 0; i < worldConfig_->subCols(); i++)
    {
        for (int j = 0; j < worldConfig_->subRows(); j++)
        {
            Vector3f point(
                (float)i / (float)worldConfig_->subCols() * width_ + position_.x,
                (float)j / (float)worldConfig_->subRows() * width_ + position_.y,
                0);

            float elevation = worldConfig_->getElevation(point);
            if (elevation > 0.25)
            {
                if (randi(0, 8) == 0)
                {

                    e = new Tree(*rm_);
                    entities_.push_back(e);
                    e->setPosition(
                        point.x + (randf() * 5.f - 5.f),
                        point.y + (randf() * 5.f - 5.f),
                        0);
                    _addObstacle(*e);
                }
            }

            if (elevation < 0.f)
            {
                obstacleGrid_.fill(i, j, i + 1, j + 1, ZERO);
            }
        }
    }

    /*

    Entity *e;
    int count = randi(0, 5);
    for (int c = 0; c < count; c++)
    {
        e = new Tree(*rm_);
        entities_.push_back(e);
        e->setPosition(
            position_.x + width_ * randf(),
            position_.y + height_ * randf(),
            0);
        _addObstacle(*e);
    }

    count = randi(0, 5);
    for (int c = 0; c < count; c++)
    {
        e = new Palm(*rm_);
        entities_.push_back(e);
        e->setPosition(
            position_.x + width_ * randf(),
            position_.y + height_ * randf(),
            0);
        _addObstacle(*e);
    }*/

    // sleep(1);

    loaded_ = true;

    std::cout << "World Cell " << cell_i_ << ", " << cell_j_ << " loaded"
              << "\n";
}

void WorldCell::_addObstacle(const Entity &entity)
{
    Vector3f topLeft = entity.getPosition() - position_ - (entity.getSize() / 2.f);

    int start_i = (int)floor(topLeft.x / width_ * (float)worldConfig_->subCols());
    int start_j = (int)floor(topLeft.y / height_ * (float)worldConfig_->subRows());

    int end_i = (int)ceil((topLeft.x + entity.getSize().x) / width_ * (float)worldConfig_->subCols());
    int end_j = (int)ceil((topLeft.y + entity.getSize().y) / height_ * (float)worldConfig_->subRows());

    obstacleGrid_.fill(start_i, start_j, end_i, end_j, 0);
}

const int &WorldCell::obstacleGridValue(const int &i, const int &j) const
{
    if (!loaded_)
        return ZERO;

    if (!obstacleGrid_.validIndex(i, j))
        return ZERO;

    return obstacleGrid_.value(i, j);
}

Entity *WorldCell::getFloor()
{
    if (!loaded_)
    {
        return &placeholder_;
    }

    if (floor_ == nullptr)
        return &placeholder_;

    return floor_;
}

std::vector<Entity *> &WorldCell::getEntities()
{
    if (!loaded_)
        return placeholders_;

    return entities_;
}

void WorldCell::translateOrigin(const Vector3f &newOrigin)
{
    if (!loaded_)
        return;

    if (origin_ == newOrigin)
        return;

    floor_->translateOrigin(newOrigin);
    for (auto &entity : entities_)
    {
        entity->translateOrigin(newOrigin);
    }

    origin_ = newOrigin;
}
