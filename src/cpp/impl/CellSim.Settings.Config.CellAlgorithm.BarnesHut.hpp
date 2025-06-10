#ifndef CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_BARNESHUT_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_BARNESHUT_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellAlgorithm::BarnesHut final {
        private:

        // TODO: ここにメンバーを追加します

        public:

        // TODO: ここにゲッターを追加します

        static void Load(::nlohmann::json const& config);
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_BARNESHUT_HPP