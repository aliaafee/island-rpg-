#ifndef __VEGETATION_H__
#define __VEGETATION_H__

#include "SpriteEntity.hpp"

class Tree : public SpriteEntity
{
public:
    Tree(ResourceManager &rm);
};

class Palm : public SpriteEntity
{
public:
    Palm(ResourceManager &rm);
};

#endif // __VEGETATION_H__