#include "ConfigFile.hpp"

std::pair<std::string, std::string> StringPartition(std::string s, std::string delimiter)
{
    std::pair<std::string, std::string> out;
    int cut = s.find(delimiter);

    if (cut < 0)
    {
        out.first = s;
        out.second = "";
        return out;
    }

    out.first = s.substr(0, cut);
    out.second = s.substr(cut + delimiter.length(), s.length() - 1);
    return out;
}

ConfigFieldVector3f::ConfigFieldVector3f(const std::string &value)
{
    auto [x, yz] = StringPartition(value, ",");
    auto [y, z] = StringPartition(yz, ",");

    value_ = Vector3f(
        std::stof(x),
        std::stof(y),
        std::stof(z));
}

ConfigFieldVector2f::ConfigFieldVector2f(const std::string &value)
{
    auto [x, y] = StringPartition(value, ",");

    value_ = Vector2f(
        std::stof(x),
        std::stof(y));
}

ConfigFile::~ConfigFile()
{
    for (auto &it : data_)
    {
        if (it.second != nullptr)
        {
            delete it.second;
        }
    }
}

bool ConfigFile::loadFromFile(std::string filename)
{
    /* Format of config file
     *
     * <name> <type> <value>
     *
     * one field per line
     * valid types: str, int, float, vec3, vec2
     * vec3 format: x,y,z
     * vec2 format: x,y
     *
     * When parsing configuration file, all duplicate
     * fields are ignored, only the first one is loaded
     */
    std::ifstream infile(filename);
    std::string name, type, value;

    std::string line;
    while (std::getline(infile, line))
    {
        auto [name, part2] = StringPartition(line, " ");
        auto [type, value] = StringPartition(part2, " ");

        ConfigField *newField = makeField_(type, value);

        if (newField != nullptr)
        {
            if (getField_(name) == nullptr)
            {
                data_[name] = newField;
            }
        }
    }

    if (data_.size() == 0)
        return false;

    return true;
}

int ConfigFile::getAsInt(std::string name)
{
    auto field = getField_(name);
    if (field == nullptr)
        return 0;
    return field->getInt();
}

float ConfigFile::getAsFloat(std::string name)
{
    auto field = getField_(name);
    if (field == nullptr)
        return 0.f;
    return field->getFloat();
}

std::string ConfigFile::getAsString(std::string name)
{
    auto field = getField_(name);
    if (field == nullptr)
        return "";
    return field->getString();
}

Vector3f ConfigFile::getAsVector3f(std::string name)
{
    auto field = getField_(name);
    if (field == nullptr)
        return Vector3f(0, 0, 0);
    return field->getVector3f();
}

Vector2f ConfigFile::getAsVector2f(std::string name)
{
    auto field = getField_(name);
    if (field == nullptr)
        return Vector2f(0, 0);
    return field->getVector2f();
}

ConfigField *ConfigFile::makeField_(std::string type, std::string value)
{
    if (type == "str")
        return new ConfigFieldString(value);

    if (type == "int")
        return new ConfigFieldInt(value);

    if (type == "float")
        return new ConfigFieldFloat(value);

    if (type == "vec3")
        return new ConfigFieldVector3f(value);

    if (type == "vec2")
        return new ConfigFieldVector2f(value);

    return nullptr;
}

ConfigField *ConfigFile::getField_(std::string name)
{
    auto search = data_.find(name);

    if (search == data_.end())
        return nullptr;

    return search->second;
}
