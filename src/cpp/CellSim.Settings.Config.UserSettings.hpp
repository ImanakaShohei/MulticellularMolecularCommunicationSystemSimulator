#ifndef CELLSIM_SETTINGS_CONFIG_USERSETTINGS_HPP
#define CELLSIM_SETTINGS_CONFIG_USERSETTINGS_HPP

#include "impl/base.hpp"
#include "impl/CellSim.Settings.Config.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    /// @brief ユーザー独自の設定
    class Config::UserSettings final {
        private:

        // TODO: ここにメンバーを追加します

        public:

        CELLSIM_STATIC_CLASS(UserSettings);

        // TODO: ここにゲッターを追加します

        static void Load(
            ::nlohmann::json& config
        );
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_USERSETTINGS_HPP