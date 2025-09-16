#include "CellSim.Settings.Config.CellBehavior.MoleculeAware.hpp"
#include "CellSim.Cells.CellBehaviorPtr.hpp"
#include "CellSim.Cells.MoleculeAwareCellBehavior.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    Cells::CellBehaviorPtr Config::CellBehavior::MoleculeAware::FromJson(
        ::nlohmann::json const& config
    )
    {
        if (config.is_null()) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.MoleculeAware.FromJson.Error.JsonError"
                )
            );
        }

        double cellDivisionRadius;
        double degradationRate;
        double growthRate;
        double synthesisRate;
        
        try {
            cellDivisionRadius = config.at("cellDivisionRadius").get<double>();
            degradationRate = config.at("degradationRate").get<double>();
            growthRate = config.at("growthRate").get<double>();
            synthesisRate = config.at("synthesisRate").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.MoleculeAware.Load.Error.JsonError"
                )
            );
        }

        if (cellDivisionRadius <= 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.MoleculeAware.Load.Error.cellDivisionRadius"
                )
            );
        }
        if (degradationRate <= 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.MoleculeAware.Load.Error.degradationRate"
                )
            );
        }
        if (synthesisRate <= 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.MoleculeAware.Load.Error.synthesisRate"
                )
            );
        }
    
        return Cells::CellBehaviorPtr::FromPointerUnsafe(
            new Cells::MoleculeAwareCellBehavior(
                cellDivisionRadius,
                growthRate,
                synthesisRate,
                degradationRate
            )
        );
    }
}