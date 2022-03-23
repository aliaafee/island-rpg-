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
    ResourceManager(const std::string &resourceDirectory);
    ~ResourceManager();

    sf::Texture *loadTexture(const std::string &filename);
    bool loadTextureDirectory(const std::string &directory, std::vector<sf::Texture *> *output);

    sf::Image *loadImage(const std::string &filename);

    bool loadShader(sf::Shader &shader, std::string vertShaderFilename, std::string fragShaderFilename);

private:
    std::string resourceDir_;
    ResourceCache<sf::Texture> textures_;
    ResourceCache<sf::Image> images_;
};

#endif // __RESOURCEMANAGER_H__