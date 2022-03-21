#include "ResourceManager.hpp"

ResourceManager::ResourceManager()
{
    ;
}

ResourceManager::~ResourceManager()
{
    ;
}

sf::Texture *ResourceManager::loadTexture(const std::string &filename)
{
    return textures_.load(filename);
}

bool ResourceManager::loadTextureDirectory(const std::string &directory,
                                           std::vector<sf::Texture *> *output)
{
    std::vector<std::string> filenames;

    try
    {
        for (const auto &entry : std::filesystem::directory_iterator(directory))
        {
            filenames.push_back(entry.path());
        }
    }
    catch (std::filesystem::filesystem_error const &ex)
    {
        // std::cout << "ResourceManager: Failed Directory Load" << directory << "\n";
        return false;
    }

    std::sort(filenames.begin(), filenames.end());

    sf::Texture *newTexture;
    for (const auto &filename : filenames)
    {
        newTexture = loadTexture(filename);
        if (newTexture == nullptr)
        {
            return false;
        }
        output->push_back(newTexture);
    }
    return true;
}

sf::Image *ResourceManager::loadImage(const std::string &filename)
{
    return images_.load(filename);
}