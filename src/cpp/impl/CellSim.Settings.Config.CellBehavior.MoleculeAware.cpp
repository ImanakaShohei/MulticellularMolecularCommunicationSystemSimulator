#include "CellSim.Settings.Config.CellBehavior.MoleculeAware.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::CellBehavior::MoleculeAware::Load(::nlohmann::json const& config)
    {
        try {
            s_cellDivisionRadius = config["cellDivisionRadius"].get<double>();
            s_degradationRate = config["degradationRate"].get<double>();
            s_synthesisRate = config["synthesisRate"].get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.MoleculeAware.Load.Error.JsonError"));
        }

        if (s_cellDivisionRadius <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.MoleculeAware.Load.Error.cellDivisionRadius"));
        if (s_degradationRate <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.MoleculeAware.Load.Error.degradationRate"));
        if (s_synthesisRate <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.MoleculeAware.Load.Error.synthesisRate"));
    }
}