#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <filesystem>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <mutex>
#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    sf::Texture *loadTexture(const std::string &filename);
    bool loadTextureDirectory(const std::string &directory, std::vector<sf::Texture *> *output);

private:
    sf::Texture *insertTexture_(const std::string &filename, sf::Texture *addTexture);

    std::map<const std::string, sf::Texture *> textures_;
    std::mutex mutex_;
};

#endif // __RESOURCEMANAGER_H__