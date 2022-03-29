#ifndef __CONFIGFILE_H__
#define __CONFIGFILE_H__

#include <string>
#include <map>
#include <fstream>

#include "Vector.hpp"

std::pair<std::string, std::string> StringPartition(std::string s, std::string delimiter);

class ConfigField
{
public:
    enum FieldType
    {
        FiledUndefined,
        FieldInt,
        FieldFloat,
        FieldString,
        FieldVector3f,
        FieldVector2f
    };
    virtual int getInt() { return 0; }
    virtual float getFloat() { return 0.f; }
    virtual std::string getString() { return ""; }
    virtual Vector3f getVector3f() { return Vector3f(0.f, 0.f, 0.f); }
    virtual Vector2f getVector2f() { return Vector2f(0.f, 0.f); }
    virtual FieldType type() { return FiledUndefined; }
};

class ConfigFieldInt : public ConfigField
{
public:
    ConfigFieldInt(const int &value) : value_(value){};
    ConfigFieldInt(const std::string &value) : value_(std::stoi(value)){};
    int getInt() { return value_; }
    std::string getString() { return std::to_string(value_); }
    virtual FieldType type() { return FieldInt; }

private:
    int value_;
};

class ConfigFieldFloat : public ConfigField
{
public:
    ConfigFieldFloat(const float &value) : value_(value){};
    ConfigFieldFloat(const std::string &value) : value_(std::stof(value)){};
    float getFloat() { return value_; }
    std::string getString() { return std::to_string(value_); }
    virtual FieldType type() { return FieldFloat; }

private:
    float value_;
};

class ConfigFieldString : public ConfigField
{
public:
    ConfigFieldString(const std::string &value) : value_(value){};
    std::string getString() { return value_; }
    virtual FieldType type() { return FieldString; }

private:
    std::string value_;
};

class ConfigFieldVector3f : public ConfigField
{
public:
    ConfigFieldVector3f(const Vector3f &value) : value_(value){};
    ConfigFieldVector3f(const std::string &value);
    Vector3f getVector3f() { return value_; }
    std::string getString() { return std::to_string(value_.x) + "," + std::to_string(value_.y) + "," + std::to_string(value_.z); }
    virtual FieldType type() { return FieldVector3f; }

private:
    Vector3f value_;
};

class ConfigFieldVector2f : public ConfigField
{
public:
    ConfigFieldVector2f(const Vector2f &value) : value_(value){};
    ConfigFieldVector2f(const std::string &value);
    Vector2f getVector2f() { return value_; }
    std::string getString() { return std::to_string(value_.x) + "," + std::to_string(value_.y); }
    virtual FieldType type() { return FieldVector2f; }

private:
    Vector2f value_;
};

class ConfigFile
{
public:
    bool loadFromFile(std::string filename);

    int getAsInt(std::string name);
    float getAsFloat(std::string name);
    std::string getAsString(std::string name);
    Vector3f getAsVector3f(std::string name);
    Vector2f getAsVector2f(std::string name);

private:
    std::map<std::string, ConfigField *> data_;

    ConfigField *makeField_(std::string type, std::string value);
    ConfigField *getField_(std::string name);
};

#endif // __CONFIGFILE_H__