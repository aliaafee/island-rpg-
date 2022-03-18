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
                                                   floor_(nullptr)
{
    placeholder_.setPosition(position_);
    placeholders_.push_back(&placeholder_);

    srand(getId());

    floor_ = new Ground(*rm_, width_, height_, 20, 20);
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
    }

    loaded_ = true;
}

int WorldCell::getId()
{
    return worldConfig_->getId(cell_i_, cell_j_);
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
    {
        return placeholders_;
    }

    return entities_;
}

void WorldCell::translateOrigin(const Vector3f &newOrigin)
{
    if (origin_ == newOrigin)
        return;

    floor_->translateOrigin(newOrigin);
    for (auto &entity : entities_)
    {
        entity->translateOrigin(newOrigin);
    }

    origin_ = newOrigin;
}
