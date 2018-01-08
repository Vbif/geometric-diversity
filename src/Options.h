#pragma once

#include <cstdint>

class Options {
public:
    Options();
    void LoadFrom(const char* filename);

private:
    void SetProperty(const std::string& name, const std::string& value);

public:
    uint32_t EnemiesCount;
    uint32_t Speed;
    uint32_t Time;
};
