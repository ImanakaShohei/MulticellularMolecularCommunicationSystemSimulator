#ifndef CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_USER_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_USER_HPP

#include "impl/base.hpp"
#include "impl/CellSim.Cells.CellBehaviorType.hpp"
#include "impl/CellSim.Settings.Config.CellBehavior.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellBehavior::User final {
        private:

        // TODO: ここにメンバーを追加します

        public:

        CELLSIM_STATIC_CLASS(User);

        // TODO: ここにゲッターを追加します

        [[nodiscard]] static Cells::CellBehaviorPtr FromJson(
            ::nlohmann::json const& config
        );
    };
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_USER_HPP