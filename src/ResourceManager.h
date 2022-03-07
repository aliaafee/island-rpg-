#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <filesystem>
#include <map>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    sf::Texture *loadTexture(const std::string &filename);

private:
    std::map<const std::string, sf::Texture *> textures_;
};

#endif // __RESOURCEMANAGER_H__