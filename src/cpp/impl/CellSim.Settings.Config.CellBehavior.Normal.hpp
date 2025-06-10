#ifndef CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_NORMAL_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_NORMAL_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehaviorType.hpp"
#include "CellSim.Settings.Config.CellBehavior.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellBehavior::Normal final {
        private:

        public:

        CELLSIM_STATIC_CLASS(Normal);

        static void Load(::nlohmann::json const& config);
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_NORMAL_HPP