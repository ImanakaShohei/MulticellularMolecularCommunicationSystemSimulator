#ifndef CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_MOLECULEAWARE_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_MOLECULEAWARE_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehaviorType.hpp"
#include "CellSim.Settings.Config.CellBehavior.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellBehavior::MoleculeAware final {
        private:

        public:

        CELLSIM_STATIC_CLASS(MoleculeAware);

        [[nodiscard]] static Cells::CellBehaviorPtr FromJson(
            ::nlohmann::json const& config
        );
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_MOLECULEAWARE_HPP