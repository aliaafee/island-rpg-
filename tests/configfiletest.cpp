#include "ConfigFile.hpp"

int main()
{
    std::cout << "# Testing ConfigFile" << std::endl;

    ConfigFile config;
    config.loadFromFile("test-data/config-test.cfg");

    if (config.getAsString("name") != "Some Random Name")
    {
        std::cout << "Failed\n";
        return 1;
    }

    if (config.getAsInt("count") != 24)
    {
        std::cout << "Failed\n";
        return 1;
    }

    if (config.getAsFloat("size") != 1.355f)
    {
        std::cout << "Failed\n";
        return 1;
    }

    if (config.getAsVector3f("position") != Vector3f(2.f, 1.f, 3.f))
    {
        std::cout << "Failed\n";
        return 1;
    }

    if (config.getAsVector2f("box") != Vector2f(1.f, 3.f))
    {
        std::cout << "Failed\n";
        return 1;
    }

    if (config.getAsString("bos") != "")
    {
        std::cout << "Failed\n";
        return 1;
    }

    if (config.getAsString("NonExistantField") != "")
    {
        std::cout << "Failed\n";
        return 1;
    }

    ConfigFile otherConfig;

    if (otherConfig.loadFromFile("nonexistantfile.cfg"))
    {
        std::cout << "Failed\n";
        return 1;
    }

    config.setInt("count", 971);
    config.setBool("newitem", true);
    config.saveToFile("test-data/config-test-save.cfg.save");

    ConfigFile reloadedConfig;
    if (!reloadedConfig.loadFromFile("test-data/config-test-save.cfg.save"))
    {
        std::cout << "Failed\n";
        return 1;
    }

    if (reloadedConfig.getAsInt("count") != 971)
    {
        std::cout << reloadedConfig.getAsInt("count") << "\n";
        std::cout << "Failed\n";
        return 1;
    }

    if (reloadedConfig.getAsBool("newitem") != true)
    {
        std::cout << reloadedConfig.getAsString("newitem") << "\n";
        std::cout << "Failed\n";
        return 1;
    }

    if (reloadedConfig.saveToFile("test-data/nonexistantfolder/nonexistantfile.save"))
    {
        std::cout << "Save to inaccesible location\n";
        return 1;
    }

    std::cout << "  Success\n";

    return 0;
}