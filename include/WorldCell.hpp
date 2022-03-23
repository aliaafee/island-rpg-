#ifndef __WORLDCELL_H__
#define __WORLDCELL_H__

#include <vector>
#include <random>
#include <thread>

#include "Vector.hpp"
#include "Entity.hpp"
#include "ResourceManager.hpp"
#include "Guides.hpp"
#include "Algorithm.hpp"
#include "Vegetation.hpp"
#include "Ground.hpp"
#include "ValueGrid.hpp"
#include "WorldConfig.hpp"
#include "RandomGenerator.hpp"

// #ifdef _WIN32
// #include <Windows.h>
// #else
// #include <unistd.h>
// #endif

class WorldCell
{
public:
    WorldCell(ResourceManager &rm,
              WorldConfig &worldConfig,
              const int &i, const int &j);

    ~WorldCell();

    int getId();

    const int &geti() const { return cell_i_; }
    const int &getj() const { return cell_j_; }

    void load();

    std::vector<Entity *> &getEntities();
    Entity *getFloor();

    void translateOrigin(const Vector3f &newOrigin);

    const int &obstacleGridValue(const int &i, const int &j) const;

private:
    Vector3f origin_;
    ResourceManager *rm_;
    WorldConfig *worldConfig_;
    int cell_i_, cell_j_;
    float width_, height_;
    Vector3f position_;

    Entity *floor_;
    std::vector<Entity *> entities_;
    std::vector<Entity *> placeholders_;
    Grid placeholder_;

    ValueGrid<int> obstacleGrid_;
    void _addObstacle(const Entity &entity);

    std::thread loadThread_;

    bool loaded_;
};

#endif // __WORLDCELL_H__