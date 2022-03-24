#ifndef __VEGETATION_H__
#define __VEGETATION_H__

#include <vector>
#include <string>

#include "SpriteEntity.hpp"
#include "RandomGenerator.hpp"

class Tree : public SpriteEntity
{
public:
    Tree(ResourceManager &rm, RandomGenerator &r);
};

class Palm : public SpriteEntity
{
public:
    Palm(ResourceManager &rm, RandomGenerator &r);
};

class TropicalTree : public SpriteEntity
{
public:
    TropicalTree(ResourceManager &rm, RandomGenerator &r);
};

#endif // __VEGETATION_H__