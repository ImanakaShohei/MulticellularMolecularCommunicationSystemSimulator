#ifndef CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehaviorType.hpp"
#include "CellSim.Settings.Config.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellBehavior final {
        private:

        public:

        class MoleculeAware;
        class Normal;
        class User;
        class WavePropagation;

        CELLSIM_STATIC_CLASS(CellBehavior);

        [[nodiscard]] static Cells::CellBehaviorPtr FromJson(
            ::nlohmann::json& config,
            Cells::CellBehaviorType type
        );
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_HPP