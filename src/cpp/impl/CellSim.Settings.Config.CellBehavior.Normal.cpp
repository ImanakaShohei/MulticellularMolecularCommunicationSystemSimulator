#include "CellSim.Settings.Config.CellBehavior.Normal.hpp"
#include "CellSim.Cells.CellBehaviorPtr.hpp"
#include "CellSim.Cells.NormalCellBehavior.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    Cells::CellBehaviorPtr Config::CellBehavior::Normal::FromJson(
        ::nlohmann::json const& config
    )
    {
        if (config.is_null()) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.Normal.FromJson.Error.JsonError"
                )
            );
        }

        double cellDivisionRadius;
        double growthRate;
        
        try {
            cellDivisionRadius = config.at("cellDivisionRadius").get<double>();
            growthRate = config.at("growthRate").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.Normal.Load.Error.JsonError"
                )
            );
        }

        if (cellDivisionRadius <= 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.Normal.Load.Error.cellDivisionRadius"
                )
            );
        }

        return Cells::CellBehaviorPtr::FromPointerUnsafe(
            new Cells::NormalCellBehavior(
                cellDivisionRadius,
                growthRate
            )
        );
    }
}