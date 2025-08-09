#ifndef CELLSIM_SETTINGS_CONFIG_MOLECULAR_BEHAVIOR_NORMAL_HPP
#define CELLSIM_SETTINGS_CONFIG_MOLECULAR_BEHAVIOR_NORMAL_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.Molecular.Behavior.hpp"

namespace CellSim::Settings
{
    class Config::Molecular::Behavior::Normal final {
        private:

        public:

        CELLSIM_STATIC_CLASS(Normal);

        [[nodiscard]] static ::CellSim::Molecular::NormalMoleculeBehavior* FromJson(::nlohmann::json const& config);
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_MOLECULAR_BEHAVIOR_NORMAL_HPP