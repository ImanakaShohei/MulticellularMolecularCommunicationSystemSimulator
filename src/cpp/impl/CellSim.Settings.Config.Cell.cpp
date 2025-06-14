#include "CellSim.Settings.Config.Cell.hpp"
#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::Cell::Load(::nlohmann::json const& config)
    {
        ::std::string s;
        try {
            s_cellCount = config["cellCount"].get<size_t>();
            s_enableGrowth = config["enableGrowth"].get<bool>();
            s_growthRate = config["growthRate"].get<double>();
            s_initialPlacementRadius = config["initialPlacementRadius"].get<double>();
            s_isSensitiveToMolecules = config["isSensitiveToMolecules"].get<bool>();
            s_initialPlacementSeed = config["initialPlacementSeed"].get<uint32_t>();
            s_mass = config["mass"].get<double>();
            s_radius = config["radius"].get<double>();
            s = config["type"].get<::std::string>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.JsonError"));
        }

        if (s_cellCount == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.cellCount"));
        if (s_growthRate <= 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.growthRate"));
        if (s_initialPlacementRadius <= 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.initialPlacementRadius"));
        if (s_mass == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.mass"));
        if (s_radius == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.radius"));
        if (s_cellCount == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.radius"));

        if (s == "Normal") s_type = Cells::CellType::Normal;
        else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.type"));
    }
}