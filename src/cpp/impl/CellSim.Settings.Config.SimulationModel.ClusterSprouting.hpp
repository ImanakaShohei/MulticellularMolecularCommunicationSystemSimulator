#ifndef CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERSPROUTING_HPP
#define CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERSPROUTING_HPP

#include "base.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"

#include <nlohmann/json_fwd.hpp>

namespace CellSim::Settings
{
    /// @brief クラスタスプラウトモデルの設定
    class Config::SimulationModel::ClusterSprouting final {
        private:

        static inline size_t s_adhesionThreshold; //接着している細胞の数がこの値以下の時に反発力が働く
        static inline double s_coefficientCd; //反発力にかける係数
        static inline double s_contactDistance; //細胞同士がこの値より近づくと反発力が発生
        static inline double s_followerAttractionFactor; //接着している細胞の数がadhesion_thresholdより多い時に受ける引力にかける係数
        static inline double s_globalAttractionFactor; //すべての細胞間にかかる力の係数
        static inline double s_initialRadius; //初期半径
        static inline double s_lambda; //力の届く範囲を決める値
        static inline double s_leaderRepulsionFactor; //接着している細胞の数がadhesion_thresholdの時に受ける反発力にかける係数
        static inline double s_leaderRepulsionMaxDistance; //リーダーに届く反発力の最大距離
        static inline double s_leaderRepulsionMinDistance; //リーダーに届く反発力の最小距離
        
        public:

        CELLSIM_STATIC_CLASS(ClusterSprouting);

        /// @brief 接着している細胞の数がこの値以下の時に反発力が働く
        [[nodiscard]] static size_t AdhesionThreshold() noexcept;

        /// @brief 反発力にかける係数
        [[nodiscard]] static double CoefficientCd() noexcept;

        /// @brief 細胞同士がこの値より近づくと反発力が発生
        [[nodiscard]] static double ContactDistance() noexcept;

        /// @brief 接着している細胞の数がadhesion_thresholdより多い時に受ける引力にかける係数
        [[nodiscard]] static double FollowerAttractionFactor() noexcept;

        /// @brief すべての細胞間にかかる力の係数
        [[nodiscard]] static double GlobalAttractionFactor() noexcept;

        /// @brief 初期半径
        [[nodiscard]] static double InitialRadius() noexcept;

        /// @brief 力の届く範囲を決める値
        [[nodiscard]] static double Lambda() noexcept;

        /// @brief 接着している細胞の数がadhesion_thresholdの時に受ける反発力にかける係数
        [[nodiscard]] static double LeaderRepulsionFactor() noexcept;

        /// @brief リーダーに届く反発力の最大距離
        [[nodiscard]] static double LeaderRepulsionMaxDistance() noexcept;

        /// @brief リーダーに届く反発力の最小距離
        [[nodiscard]] static double LeaderRepulsionMinDistance() noexcept;
        

        static void Load(::nlohmann::json const& config);
    };
}

namespace CellSim::Settings
{
    inline size_t Config::SimulationModel::ClusterSprouting::AdhesionThreshold() noexcept
    {
        return s_adhesionThreshold;
    }

    inline double Config::SimulationModel::ClusterSprouting::CoefficientCd() noexcept
    {
        return s_coefficientCd;
    }

    inline double Config::SimulationModel::ClusterSprouting::ContactDistance() noexcept
    {
        return s_contactDistance;
    }

    inline double Config::SimulationModel::ClusterSprouting::FollowerAttractionFactor() noexcept
    {
        return s_followerAttractionFactor;
    }

    inline double Config::SimulationModel::ClusterSprouting::GlobalAttractionFactor() noexcept
    {
        return s_globalAttractionFactor;
    }

    inline double Config::SimulationModel::ClusterSprouting::InitialRadius() noexcept
    {
        return s_initialRadius;
    }

    inline double Config::SimulationModel::ClusterSprouting::Lambda() noexcept
    {
        return s_lambda;
    }

    inline double Config::SimulationModel::ClusterSprouting::LeaderRepulsionFactor() noexcept
    {
        return s_leaderRepulsionFactor;
    }

    inline double Config::SimulationModel::ClusterSprouting::LeaderRepulsionMaxDistance() noexcept
    {
        return s_leaderRepulsionMaxDistance;
    }

    inline double Config::SimulationModel::ClusterSprouting::LeaderRepulsionMinDistance() noexcept
    {
        return s_leaderRepulsionMinDistance;
    }

}

#endif //!CELLSIM_SETTINGS_CONFIG_SIMULATIONMODEL_CLUSTERSPROUTING_HPP