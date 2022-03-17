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
                                                   loaded_(false)
{
    placeholder_.setPosition(position_);
    placeholders_.push_back(&placeholder_);

    srand(getId());

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

    e = new Ground(*rm_, width_, height_, 20, 20);
    e->setPosition(position_.x, position_.y, 0);
    entities_.push_back(e);

    loaded_ = true;
}

int WorldCell::getId()
{
    return worldConfig_->getId(cell_i_, cell_j_);
}

std::vector<Entity *> &WorldCell::getEntities()
{
    if (!loaded_)
    {
        return placeholders_;
    }

    return entities_;
}