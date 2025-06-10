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

        static inline Cells::CellBehaviorType s_behaviorType;

        public:

        class Normal;
        class User;

        CELLSIM_STATIC_CLASS(CellBehavior);

        /// @brief ふるまい定義
        [[nodiscard]] static Cells::CellBehaviorType BehaviorType() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    Cells::CellBehaviorType Config::CellBehavior::BehaviorType() noexcept
    {
        return s_behaviorType;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_HPP