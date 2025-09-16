#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_USER_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_USER_HPP

#include "impl/base.hpp"
#include "impl/CellSim.Settings.Config.SimulationModel.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::SimulationModel::User final {
        private:

        // TODO: ここにメンバーを追加します

        public:

        CELLSIM_STATIC_CLASS(User);

        class Params final {
            public:

            CELLSIM_STATIC_CLASS(Params);

            [[nodiscard]] static Model::CellSimulationModel::Params* FromJson(
                ::nlohmann::json const& j
            );
        };

        // TODO: ここにゲッターを追加します

        static void Load(
            ::nlohmann::json const& config
        );
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_USER_HPP