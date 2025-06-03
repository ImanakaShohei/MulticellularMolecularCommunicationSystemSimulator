#ifndef CELLSIM_SIMULATION_HPP
#define CELLSIM_SIMULATION_HPP

#include "base.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Model.Molecule.MoleculeDiffusion.hpp"
#include <vector>

namespace CellSim
{
    /// @brief シミュレーション実行クラス
    class Simulation final {
        private:

        /// @brief 細胞リスト
        ::std::vector<Cells::Cell> m_cells;

        /// @brief 分子空間リスト
        ::std::vector<Model::Molecule::MoleculeDiffusion> m_molecules;

        /// @brief 使用する高速化アルゴリズムへのポインター
        /// @note シミュレーションモデルのUserCellAlgorithm()がfalseの場合はnullptr
        CellAlgorithms::CellAlgorithm* m_pCellAlgorithm;

        /// @brief クラスタモデルで使うCellListインスタンスへのポインター
        CellAlgorithms::CellList* m_pCellList;

        /// @brief シミュレーションモデルインスタンスへのポインター
        Model::CellSimulationModel* m_pCellSimulationModel;

        /// @brief 1step進める
        void m_advanceStep();

        /// @brief m_advanceStep()の前処理
        void m_beforeAdvanceStep();

        /// @brief 高速化アルゴリズムインスタンスの初期化
        void m_initializeCellAlgorithm();

        public:

        /// @brief 初期化
        Simulation();
        Simulation(Simulation const&) = delete;

        ~Simulation();

        Simulation& operator=(Simulation const&) = delete;

        /// @brief シミュレーションを実行
        void Run();
    };
}

#endif //!CELLSIM_SIMULATION_HPP