#ifndef CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_MOLECULEAWARE_HPP
#define CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_MOLECULEAWARE_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehaviorType.hpp"
#include "CellSim.Settings.Config.CellBehavior.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellBehavior::MoleculeAware final {
        private:

        static inline double s_cellDivisionRadius;
        static inline double s_degradationRate;
        static inline double s_synthesisRate;

        public:

        CELLSIM_STATIC_CLASS(MoleculeAware);

        /// @brief 細胞の半径がこの値を超えると分裂する
        [[nodiscard]] static double CellDivisionRadius() noexcept;

        /// @brief 分解係数 k2
        [[nodiscard]] static double DegradationRate() noexcept;

        /// @brief 生成係数 k1
        [[nodiscard]] static double SynthesisRate() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline double Config::CellBehavior::MoleculeAware::CellDivisionRadius() noexcept
    {
        return s_cellDivisionRadius;
    }

    inline double Config::CellBehavior::MoleculeAware::DegradationRate() noexcept
    {
        return s_degradationRate;
    }

    inline double Config::CellBehavior::MoleculeAware::SynthesisRate() noexcept
    {
        return s_synthesisRate;
    }
}

#endif //!CELLSIM_SETTINGS_CONFIG_CELLBEHAVIOR_MOLECULEAWARE_HPP