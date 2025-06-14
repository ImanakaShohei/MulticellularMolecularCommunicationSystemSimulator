#include "CellSim.Settings.Config.CellAlgorithm.CellList.hpp"
#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::CellAlgorithm::CellList::Load(::nlohmann::json const& config)
    {
        try {
            s_gridCountX = config.at("gridCountX").get<size_t>();
            s_gridCountY = config.at("gridCountY").get<size_t>();
            s_gridCountZ = config.at("gridCountZ").get<size_t>();
            s_searchRadius = config.at("searchRadius").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.CellAlgorithm.CellList.Load.Error.JsonError"));
        }
        
        if (s_gridCountX == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellAlgorithm.CellList.Load.Error.gridCountX"));
        if (s_gridCountY == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellAlgorithm.CellList.Load.Error.gridCountY"));
        if (s_gridCountZ == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellAlgorithm.CellList.Load.Error.gridCountZ"));
        if (s_searchRadius == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellAlgorithm.CellList.Load.Error.searchRadius"));
    }
}