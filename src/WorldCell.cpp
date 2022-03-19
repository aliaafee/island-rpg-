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
                                                       worldConfig_->subRows()),
                                                   loadThread_(&WorldCell::load, this)
{
    placeholder_.setPosition(position_);
    placeholders_.push_back(&placeholder_);
}

WorldCell::~WorldCell()
{
    std::cout << "Destroying World Cell " << cell_i_ << ", " << cell_j_
              << "\n";

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

    floor_ = new Ground(*rm_, width_, height_, 40, 40);
    floor_->setPosition(position_.x, position_.y, 0);

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
    }

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

WorldPathfinder::WorldPathfinder(const Vector3f &position,
                                 WorldConfig &worldConfig) : Pathfinder(position,
                                                                        worldConfig.getCellWidth() * 3.f,
                                                                        worldConfig.getCellHeight() * 3.f,
                                                                        worldConfig.subCols() * 3,
                                                                        worldConfig.subRows() * 3),
                                                             cellCols_(worldConfig.subCols()),
                                                             cellRows_(worldConfig.subRows()),
                                                             currentCells_{nullptr}
{
}

void WorldPathfinder::setActiveCells(const int &start_i, const int &start_j,
                                     const std::vector<WorldCell *> &activeCells)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            currentCells_[i][j] = nullptr;
        }
    }

    int i, j;
    for (auto &cell : activeCells)
    {
        i = cell->geti() - start_i;
        j = cell->getj() - start_j;
        currentCells_[i][j] = cell;
    }
}

bool WorldPathfinder::validCell(const int &i, const int &j) const
{
    if (!validIndex(i, j))
        return false;

    if (value_(i, j) == 0)
        return false;

    return true;
}

const int &WorldPathfinder::cellValue(const int &i, const int &j) const
{
    if (!validIndex(i, j))
        return ZERO;

    return value_(i, j);
}

const int &WorldPathfinder::value_(const int &i, const int &j) const
{
    int cell_i = i / cellCols_;
    int cell_j = j / cellRows_;

    int cell_id = i + j * 3;
    WorldCell *cell = currentCells_[cell_i][cell_j];

    if (cell == nullptr)
    {
        return ZERO;
    }

    return cell->obstacleGridValue(
        i - (cell_i * cellCols_),
        j - (cell_j * cellRows_));
}