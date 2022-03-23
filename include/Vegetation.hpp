#ifndef __VEGETATION_H__
#define __VEGETATION_H__

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

#endif // __VEGETATION_H__