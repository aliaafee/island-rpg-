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

bool ConfigFieldVector3f::setString(const std::string &value)
{
    auto [x, yz] = StringPartition(value, ",");
    auto [y, z] = StringPartition(yz, ",");

    value_ = Vector3f(
        std::stof(x),
        std::stof(y),
        std::stof(z));

    return true;
}

bool ConfigFieldVector2f::setString(const std::string &value)
{
    auto [x, y] = StringPartition(value, ",");

    value_ = Vector2f(
        std::stof(x),
        std::stof(y));

    return true;
}

ConfigFile::~ConfigFile()
{
    for (auto &field : data_)
    {
        if (field.second != nullptr)
        {
            delete field.second;
        }
    }
}

ConfigField *CreateConfigField(std::string type)
{
    if (type == "str")
        return new ConfigFieldString();

    if (type == "int")
        return new ConfigFieldInt();

    if (type == "bool")
        return new ConfigFieldBool();

    if (type == "float")
        return new ConfigFieldFloat();

    if (type == "vec3")
        return new ConfigFieldVector3f();

    if (type == "vec2")
        return new ConfigFieldVector2f();

    return nullptr;
}

std::string ConfigFieldToString(std::string name, ConfigField &field)
{
    std::string typeName;
    switch (field.type())
    {
    case FieldString:
        typeName = "str";
        break;
    case FieldInt:
        typeName = "int";
        break;
    case FieldBool:
        typeName = "bool";
        break;
    case FieldFloat:
        typeName = "float";
        break;
    case FieldVector3f:
        typeName = "vec3";
        break;
    case FieldVector2f:
        typeName = "vec2";
        break;
    default:
        break;
    }

    return name + " " + typeName + " " + field.getString();
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

    if (!infile.is_open())
        return false;

    std::string line, name, type, value;
    while (std::getline(infile, line))
    {
        auto [name, part2] = StringPartition(line, " ");
        auto [type, value] = StringPartition(part2, " ");

        ConfigField *newField = CreateConfigField(type);

        if (newField != nullptr)
        {
            if (getField_(name) == nullptr)
            {
                if (newField->setString(value))
                {
                    insertField_(name, newField);
                }
            }
        }
    }

    infile.close();

    if (data_.size() == 0)
        return false;

    return true;
}

bool ConfigFile::saveToFile(std::string filename)
{
    std::ofstream outfile(filename);

    if (!outfile.is_open())
        return false;

    for (auto [name, field] : data_)
    {
        if (field != nullptr)
        {
            outfile << ConfigFieldToString(name, *field) << "\n";
        }
    }

    outfile.close();

    return true;
}

int ConfigFile::getAsInt(std::string name)
{
    auto field = getField_(name);
    if (field == nullptr)
        return 0;
    return field->getInt();
}

bool ConfigFile::getAsBool(std::string name)
{
    auto field = getField_(name);
    if (field == nullptr)
        return false;
    return field->getBool();
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

bool ConfigFile::setInt(std::string name, const int &value)
{
    auto field = getField_(name);

    if (field == nullptr)
    {
        field = new ConfigFieldInt();
        insertField_(name, field);
    }

    return field->setInt(value);
}

bool ConfigFile::setBool(std::string name, const bool &value)
{
    auto field = getField_(name);

    if (field == nullptr)
    {
        field = new ConfigFieldBool();
        insertField_(name, field);
    }

    return field->setBool(value);
}

bool ConfigFile::setFloat(std::string name, const float &value)
{
    auto field = getField_(name);

    if (field == nullptr)
    {
        field = new ConfigFieldFloat();
        insertField_(name, field);
    }

    return field->setFloat(value);
}

bool ConfigFile::setString(std::string name, const std::string &value)
{
    auto field = getField_(name);

    if (field == nullptr)
    {
        field = new ConfigFieldString();
        insertField_(name, field);
    }

    return field->setString(value);
}

bool ConfigFile::setVector3f(std::string name, const Vector3f &value)
{
    auto field = getField_(name);

    if (field == nullptr)
    {
        field = new ConfigFieldVector3f();
        insertField_(name, field);
    }

    return field->setVector3f(value);
}

bool ConfigFile::setVector2f(std::string name, const Vector2f &value)
{
    auto field = getField_(name);

    if (field == nullptr)
    {
        field = new ConfigFieldVector2f();
        insertField_(name, field);
    }

    return field->setVector2f(value);
}

ConfigField *ConfigFile::getField_(std::string name)
{
    auto search = data_.find(name);

    if (search == data_.end())
        return nullptr;

    return search->second;
}

bool ConfigFile::insertField_(std::string name, ConfigField *field)
{
    data_[name] = field;

    return true;
}
