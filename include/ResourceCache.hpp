#ifndef __RESOURCECACHE_H__
#define __RESOURCECACHE_H__

#include <string>
#include <mutex>

template <class ResourceType>
class ResourceCache
{
public:
    ResourceCache();
    ~ResourceCache();

    ResourceType *load(const std::string &filename);

private:
    ResourceType *insert_(const std::string &filename, ResourceType *addTexture);

    std::map<const std::string, ResourceType *> resources_;
    std::mutex mutex_;
};

template <class ResourceType>
ResourceCache<ResourceType>::ResourceCache()
{
}

template <class ResourceType>
ResourceCache<ResourceType>::~ResourceCache()
{
    for (auto &it : resources_)
    {
        if (it.second != nullptr)
        {
            delete it.second;
        }
    }
}

template <class ResourceType>
ResourceType *ResourceCache<ResourceType>::load(const std::string &filename)
{
    auto search = resources_.find(filename);

    if (search != resources_.end())
    {
        return search->second;
    }

    ResourceType *newResource = new ResourceType();

    if (!newResource->loadFromFile(filename))
    {
        delete newResource;
        // Mark as invalid texture source
        return insert_(filename, nullptr);
    }

    return insert_(filename, newResource);
}

template <class ResourceType>
ResourceType *ResourceCache<ResourceType>::insert_(const std::string &filename, ResourceType *addResource)
{
    // Insert texture to cache in a thread safe manner
    std::lock_guard<std::mutex> lock(mutex_);

    auto search = resources_.find(filename);

    if (search != resources_.end())
    {
        return search->second;
    }

    resources_[filename] = addResource;

    return addResource;
}

#endif // __RESOURCECACHE_H__