#ifndef __CONFIGFILE_H__
#define __CONFIGFILE_H__

#include <string>
#include <map>
#include <fstream>

#include "Vector.hpp"

std::pair<std::string, std::string> StringPartition(std::string s, std::string delimiter);

enum FieldType
{
    FiledUndefined,
    FieldInt,
    FieldBool,
    FieldFloat,
    FieldString,
    FieldVector3f,
    FieldVector2f
};

class ConfigField
{
public:
    virtual FieldType type() { return FiledUndefined; }

    virtual int getInt() { return 0; }
    virtual float getFloat() { return 0.f; }
    virtual bool getBool() { return false; }
    virtual std::string getString() { return ""; }
    virtual Vector3f getVector3f() { return Vector3f(0.f, 0.f, 0.f); }
    virtual Vector2f getVector2f() { return Vector2f(0.f, 0.f); }

    virtual bool setInt(const int &value) { return false; }
    virtual bool setBool(const bool &value) { return false; }
    virtual bool setFloat(const float &value) { return false; }
    virtual bool setString(const std::string &value) { return false; }
    virtual bool setVector3f(const Vector3f &value) { return false; }
    virtual bool setVector2f(const Vector2f &value) { return false; }
};

class ConfigFieldInt : public ConfigField
{
public:
    FieldType type() { return FieldInt; }

    int getInt() { return value_; }
    std::string getString() { return std::to_string(value_); }

    bool setInt(const int &value)
    {
        value_ = value;
        return true;
    }

    bool setString(const std::string &value)
    {
        value_ = std::stoi(value);
        return true;
    }

private:
    int value_;
};

class ConfigFieldBool : public ConfigField
{
public:
    FieldType type() { return FieldBool; }

    bool getBool() { return value_; }
    std::string getString()
    {
        if (value_)
            return "true";
        return "false";
    }

    bool setBool(const bool &value)
    {
        value_ = value;
        return true;
    }

    bool setString(const std::string &value)
    {
        if (value == "true")
        {
            value_ = true;
            return true;
        }
        if (value == "false")
        {
            value_ = false;
            return true;
        }
        return false;
    }

private:
    bool value_;
};

class ConfigFieldFloat : public ConfigField
{
public:
    FieldType type() { return FieldFloat; }

    float getFloat() { return value_; }
    std::string getString() { return std::to_string(value_); }

    bool setFloat(const float &value)
    {
        value_ = value;
        return true;
    }

    bool setString(const std::string &value)
    {
        value_ = std::stof(value);
        return true;
    }

private:
    float value_;
};

class ConfigFieldString : public ConfigField
{
public:
    FieldType type() { return FieldString; }

    std::string getString() { return value_; }

    bool setString(const std::string &value)
    {
        value_ = value;
        return true;
    }

private:
    std::string value_;
};

class ConfigFieldVector3f : public ConfigField
{
public:
    FieldType type() { return FieldVector3f; }

    Vector3f getVector3f() { return value_; }
    std::string getString() { return std::to_string(value_.x) + "," + std::to_string(value_.y) + "," + std::to_string(value_.z); }

    bool setVector3f(const Vector3f &value)
    {
        value_ = value;
        return true;
    }

    bool setString(const std::string &value);

private:
    Vector3f value_;
};

class ConfigFieldVector2f : public ConfigField
{
public:
    virtual FieldType type() { return FieldVector2f; }

    Vector2f getVector2f() { return value_; }
    std::string getString() { return std::to_string(value_.x) + "," + std::to_string(value_.y); }

    bool setVector2f(const Vector2f &value)
    {
        value_ = value;
        return true;
    }

    bool setString(const std::string &value);

private:
    Vector2f value_;
};

ConfigField *CreateConfigField(std::string type);

std::string ConfigFieldToString(std::string name, ConfigField &field);

class ConfigFile
{
public:
    ~ConfigFile();
    bool loadFromFile(std::string filename);

    bool saveToFile(std::string filenamt);

    int getAsInt(std::string name);
    bool getAsBool(std::string name);
    float getAsFloat(std::string name);
    std::string getAsString(std::string name);
    Vector3f getAsVector3f(std::string name);
    Vector2f getAsVector2f(std::string name);

    bool setInt(std::string name, const int &value);
    bool setBool(std::string name, const bool &value);
    bool setFloat(std::string name, const float &value);
    bool setString(std::string name, const std::string &value);
    bool setVector3f(std::string name, const Vector3f &value);
    bool setVector2f(std::string name, const Vector2f &value);

private:
    std::map<std::string, ConfigField *> data_;

    ConfigField *getField_(std::string name);
    bool insertField_(std::string name, ConfigField *field);
};

#endif // __CONFIGFILE_H__