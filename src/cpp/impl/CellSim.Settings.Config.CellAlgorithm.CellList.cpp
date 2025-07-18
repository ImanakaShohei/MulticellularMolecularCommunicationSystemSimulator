#include "CellSim.Settings.Config.CellAlgorithm.CellList.hpp"
#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::CellAlgorithm::CellList::Load(::nlohmann::json const& config)
    {
        if (config.is_null()) return;
        
        try {
            s_gridCount = config.at("gridCount").get<size_t>();
            s_searchRadius = config.at("searchRadius").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.CellAlgorithm.CellList.Load.Error.JsonError"));
        }
        
        if (s_gridCount == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellAlgorithm.CellList.Load.Error.gridCount"));
        if (s_searchRadius == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellAlgorithm.CellList.Load.Error.searchRadius"));

    }
}