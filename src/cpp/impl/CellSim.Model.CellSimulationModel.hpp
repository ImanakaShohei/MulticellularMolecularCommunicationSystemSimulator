#ifndef CELLSIM_MODEL_SIMULATIONMODEL_HPP
#define CELLSIM_MODEL_SIMULATIONMODEL_HPP

#include "base.hpp"

#include <vector>

namespace CellSim::Model
{
    /// @brief 力学モデル
    class CellSimulationModel {
        public:

        virtual ~CellSimulationModel() = default;

        /// @brief CellSimulationTypeからインスタンスを作成
        /// @param type 種類
        /// @return インスタンス
        [[nodiscard]] static CellSimulationModel* FromType(CellSimulationType type);

        /// @brief 前処理
        /// @param cells 細胞リスト
        /// @param molecules 分子空間リスト
        virtual void BeforeAdvanceStep(
            const Simulation* sender,
            SimulationModelStepArgs args
        ) = 0;

        /// @brief ターゲットの細胞かける力を計算
        /// @param target ターゲットの細胞
        /// @param cells 細胞リスト
        /// @param moleculeSpaces 分子空間リスト
        /// @param cellAlgorithm 高速化アルゴリズム
        /// @return 計算結果
        [[nodiscard]] virtual Numerics::Vector3 ComputeForceOnCell(
            const Simulation* sender,
            SimulationModelForceComputationArgs args
        ) const = 0;

        /// @brief リストに細胞を格納
        /// @param cells リスト
        virtual void InitializeCells(
            const Simulation* sender,
            ::std::vector<Cells::Cell>& cells
        );

        /// @brief 後処理
        /// @param cells 細胞リスト
        /// @param molecules 分子空間リスト
        virtual void OnAdvanceStep(
            const Simulation* sender,
            SimulationModelStepArgs args
        ) = 0;

        /// @brief モデルでCellAlgorithmを使うかどうか
        [[nodiscard]] virtual bool UseCellAlgorithm() const noexcept = 0;
    };
}

#endif //!CELLSIM_MODEL_SIMULATIONMODEL_HPP