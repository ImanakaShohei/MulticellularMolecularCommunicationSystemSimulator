#ifndef CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_BARNESHUT_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_BARNESHUT_HPP

#include "CellSim.Settings.Config.CellAlgorithm.hpp"
#include "base.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings {
    class Config::CellAlgorithm::BarnesHut final
    {
        private:
        // TODO: ここにメンバーを追加します
        static inline double s_theta;

        public:
        CELLSIM_STATIC_CLASS(BarnesHut);

        // TODO: ここにゲッターを追加します
        [[nodiscard]] static double Theta() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings {
    inline double Config::CellAlgorithm::BarnesHut::Theta() noexcept
    {
        return s_theta;
    }
}

#endif //! CELLSIM_SETTINGS_CONFIG_CELLALGORITHM_BARNESHUT_HPP