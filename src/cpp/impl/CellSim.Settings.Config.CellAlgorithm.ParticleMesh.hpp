#ifndef CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_PARTICLEMESH_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_PARTICLEMESH_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellAlgorithm::ParticleMesh final {
        private:

        // TODO: ここにメンバーを追加します

        public:

        CELLSIM_STATIC_CLASS(ParticleMesh);

        // TODO: ここにゲッターを追加します

        static void Load(
            ::nlohmann::json const& config
        );
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_PARTICLEMESH_HPP