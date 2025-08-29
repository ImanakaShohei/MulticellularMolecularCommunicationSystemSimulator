#ifndef CELLSIs_SETTINGS_CONFIG_CELLBEHAVIOR_WAVEPROPAGATION_HPP
#define CELLSIs_SETTINGS_CONFIG_CELLBEHAVIOR_WAVEPROPAGATION_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.CellBehavior.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    class Config::CellBehavior::WavePropagation final {
        private:

        static inline double s_cellDivisionRadius;
        static inline double s_degradationRate;
        static inline double s_growthRate;
        static inline double s_synthesisRate;

        static inline double s_c;
        static inline double s_k_1;
        static inline double s_k_2;
        static inline double s_l_1;
        static inline double s_l_2;
        static inline double s_q;
        static inline double s_sigma;
        static inline double s_k_i;
        static inline double s_k_e;
        static inline double s_k_t;
        static inline double s_alpha;
        static inline double s_h;
        static inline double s_theta;
        static inline double s_lambda;
        static inline double s_epsilon;

        public:

        CELLSIM_STATIC_CLASS(WavePropagation);

        /// @brief 細胞の半径がこの値を超えると分裂する
        [[nodiscard]] static double CellDivisionRadius() noexcept;

        /// @brief 分解係数 k2
        [[nodiscard]] static double DegradationRate() noexcept;

        /// @brief 細胞の成長速度
        [[nodiscard]] static double GrowthRate() noexcept;

        /// @brief 生成係数 k1
        [[nodiscard]] static double SynthesisRate() noexcept;

        [[nodiscard]] static double C() noexcept;
        [[nodiscard]] static double K1() noexcept;
        [[nodiscard]] static double K2() noexcept;
        [[nodiscard]] static double L1() noexcept;
        [[nodiscard]] static double L2() noexcept;
        [[nodiscard]] static double Q() noexcept;
        [[nodiscard]] static double Sigma() noexcept;
        [[nodiscard]] static double Ki() noexcept;
        [[nodiscard]] static double Ke() noexcept;
        [[nodiscard]] static double Kt() noexcept;
        [[nodiscard]] static double Alpha() noexcept;
        [[nodiscard]] static double H() noexcept;
        [[nodiscard]] static double Theta() noexcept;
        [[nodiscard]] static double Lambda() noexcept;
        [[nodiscard]] static double Epsilon() noexcept;

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline double Config::CellBehavior::WavePropagation::CellDivisionRadius() noexcept
    {
        return s_cellDivisionRadius;
    }

    inline double Config::CellBehavior::WavePropagation::DegradationRate() noexcept
    {
        return s_degradationRate;
    }

    inline double Config::CellBehavior::WavePropagation::GrowthRate() noexcept
    {
        return s_growthRate;
    }

    inline double Config::CellBehavior::WavePropagation::SynthesisRate() noexcept
    {
        return s_synthesisRate;
    }

    inline double Config::CellBehavior::WavePropagation::C() noexcept
    {
        return s_c;
    }

    inline double Config::CellBehavior::WavePropagation::K1() noexcept
    {
        return s_k_1;
    }

    inline double Config::CellBehavior::WavePropagation::K2() noexcept
    {
        return s_k_2;
    }

    inline double Config::CellBehavior::WavePropagation::L1() noexcept
    {
        return s_l_1;
    }

    inline double Config::CellBehavior::WavePropagation::L2() noexcept
    {
        return s_l_2;
    }

    inline double Config::CellBehavior::WavePropagation::Q() noexcept
    {
        return s_q;
    }

    inline double Config::CellBehavior::WavePropagation::Sigma() noexcept
    {
        return s_sigma;
    }

    inline double Config::CellBehavior::WavePropagation::Ki() noexcept
    {
        return s_k_i;
    }

    inline double Config::CellBehavior::WavePropagation::Ke() noexcept
    {
        return s_k_e;
    }

    inline double Config::CellBehavior::WavePropagation::Kt() noexcept
    {
        return s_k_t;
    }

    inline double Config::CellBehavior::WavePropagation::Alpha() noexcept
    {
        return s_alpha;
    }

    inline double Config::CellBehavior::WavePropagation::H() noexcept
    {
        return s_h;
    }

    inline double Config::CellBehavior::WavePropagation::Theta() noexcept
    {
        return s_theta;
    }

    inline double Config::CellBehavior::WavePropagation::Lambda() noexcept
    {
        return s_lambda;
    }

    inline double Config::CellBehavior::WavePropagation::Epsilon() noexcept
    {
        return s_epsilon;
    }
}

#endif //!CELLSIs_SETTINGS_CONFIG_CELLBEHAVIOR_WAVEPROPAGATION_HPP