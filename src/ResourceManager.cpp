#include "ResourceManager.hpp"

ResourceManager::ResourceManager()
{
    std::cout << "Creating ResourceManager"
              << "\n";
    ;
}

ResourceManager::~ResourceManager()
{
    std::cout << "Destroying ResourceManager"
              << "\n";

    for (auto &it : textures_)
    {
        delete it.second;
    }
}

sf::Texture *ResourceManager::loadTexture(const std::string &filename)
{
    auto search = textures_.find(filename);

    if (search != textures_.end())
    {
        std::cout << "ResourceManager: Already Loaded '" << filename << "'\n";
        return search->second;
    }

    sf::Texture *newTexture = new sf::Texture();

    if (!newTexture->loadFromFile(filename))
    {
        std::cout << "ResourceManager: Load Failed '" << filename << "'\n";
        delete newTexture;
        return nullptr;
    }

    std::cout << "ResourceManager: Loaded '" << filename << "'\n";

    return insertTexture_(filename, newTexture);
}

bool ResourceManager::loadTextureDirectory(const std::string &directory,
                                           std::vector<sf::Texture *> *output)
{
    sf::Texture *newTexture;
    for (const auto &entry : std::filesystem::directory_iterator(directory))
    {
        newTexture = loadTexture(entry.path());
        if (newTexture == nullptr)
        {
            return false;
        }
        output->push_back(newTexture);
    }
    return true;
}

sf::Texture *ResourceManager::insertTexture_(const std::string &filename, sf::Texture *addTexture)
{
    // Insert texture to cache in a thread safe manner
    std::lock_guard<std::mutex> lock(mutex_);

    auto search = textures_.find(filename);

    if (search != textures_.end())
    {
        std::cout << "ResourceManager: Already Loaded '" << filename << "'\n";
        return search->second;
    }

    textures_.insert(std::pair(filename, addTexture));

    return addTexture;
}