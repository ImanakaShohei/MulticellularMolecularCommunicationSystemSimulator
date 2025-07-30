#include "CellSim.Settings.Config.Cell.hpp"
#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::Cell::Load(::nlohmann::json& config)
    {
        s_cells.clear();
        s_totalCellCount = 0;

        if (config.is_null()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.JsonError"));

        try {
            s_enableGrowth = config.at("enableGrowth").get<bool>();
            s_initialPlacementRadius = config.at("initialPlacementRadius").get<double>();
            s_isSensitiveToMolecules = config.at("isSensitiveToMolecules").get<bool>();
            s_initialPlacementSeed = config.at("initialPlacementSeed").get<uint32_t>();

            Cells::CellCreateInfo info;
            ::std::string s;

            for (::nlohmann::json const& obj : config.at("cells")) {
                s = obj.at("behaviorType");
                info.CellCount = obj.at("cellCount").get<int32_t>();
                info.GrowthRate = obj.at("growthRate").get<double>();
                info.Mass = obj.at("mass").get<double>();
                info.Radius = obj.at("radius").get<double>();
                info.Type = Cells::CellType::AddName(obj.at("typeName").get<::std::string>(), Graphics::Color(obj.at("color").get<::std::string>()));

                if (info.CellCount == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.cellCount"));
                if (info.GrowthRate <= 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.growthRate"));
                if (info.Mass == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.mass"));
                if (info.Radius == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.radius"));

                if (s == "MoleculeAware") info.BehaviorType = Cells::CellBehaviorType::MoleculeAware;
                else if (s == "Normal") info.BehaviorType = Cells::CellBehaviorType::Normal;
                else if (s == "User") info.BehaviorType = Cells::CellBehaviorType::User;
                else if (s == "WavePropagation") info.BehaviorType = Cells::CellBehaviorType::WavePropagation;
                else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.behaviorType"));

                s_cells.emplace_back(info);
                s_totalCellCount += info.CellCount;
            }
        }
        catch (::std::runtime_error) {
            ::std::rethrow_exception(::std::current_exception());
        }
        catch (::std::invalid_argument) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.color"));
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.JsonError"));
        }
        
        if (s_initialPlacementRadius <= 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Cell.Load.Error.initialPlacementRadius"));
    
    }
}