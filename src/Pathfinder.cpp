#include "Pathfinder.hpp"

Pathfinder::Pathfinder(const int &width, const int &height) : g_width_(width),
                                                              g_height_(height)
{
    grid_ = new int[g_width_ * g_height_];
    
    open_list = new Node[g_width_ * g_height_];
    closed_list_ = new bool[g_width_ * g_height_];
}

Pathfinder::~Pathfinder()
{
}
