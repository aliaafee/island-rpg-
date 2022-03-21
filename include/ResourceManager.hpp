#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <filesystem>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <ResourceCache.hpp>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    sf::Texture *loadTexture(const std::string &filename);
    bool loadTextureDirectory(const std::string &directory, std::vector<sf::Texture *> *output);

    sf::Image *loadImage(const std::string &filename);

private:
    ResourceCache<sf::Texture> textures_;
    ResourceCache<sf::Image> images_;
};

#endif // __RESOURCEMANAGER_H__