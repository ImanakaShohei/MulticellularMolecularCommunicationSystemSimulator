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

        [[nodiscard]] static Cells::CellBehaviorPtr FromJson(
            ::nlohmann::json const& config
        );
    };
}

#endif //!CELLSIs_SETTINGS_CONFIG_CELLBEHAVIOR_WAVEPROPAGATION_HPP