#ifndef CELLSIM_SETTINGS_CONFIG_MOLECULAR_BEHAVIOR_HPP
#define CELLSIM_SETTINGS_CONFIG_MOLECULAR_BEHAVIOR_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.Molecular.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::Molecular::Behavior final {
        private:

        public:

        class Normal;

        CELLSIM_STATIC_CLASS(Behavior);

        [[nodiscard]] static ::CellSim::Molecular::MoleculeBehavior* FromJson(
            ::nlohmann::json& config,
            ::CellSim::Molecular::MoleculeBehaviorKind kind
        );
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_MOLECULAR_BEHAVIOR_HPP