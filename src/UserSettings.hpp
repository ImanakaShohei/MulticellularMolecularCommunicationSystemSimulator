#pragma once

#include <stdint.h>
#include <yaml-cpp/yaml.h>

class UserSettings {
    public:

    static void init(YAML::Node node);
};