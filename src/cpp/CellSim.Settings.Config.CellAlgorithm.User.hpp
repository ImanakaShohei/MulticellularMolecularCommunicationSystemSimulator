#ifndef CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_USER_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_USER_HPP

#include "impl/base.hpp"
#include "impl/CellSim.Settings.Config.CellAlgorithm.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellAlgorithm::User final {
        private:

        // TODO: ここにメンバーを追加します

        public:

        // TODO: ここにゲッターを追加します

        static void Load(::nlohmann::json const& config);
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_USER_HPP