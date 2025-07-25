#ifndef CELLSIM_CELLS_CELLCREATEINHO_HPP
#define CELLSIM_CELLS_CELLCREATEINHO_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehaviorType.hpp"
#include "CellSim.Cells.CellType.hpp"
#include "CellSim.Graphics.Color.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Cells
{
    struct CellCreateInfo {
        /// @brief 細胞の成長速度
        double GrowthRate;

        /// @brief 細胞の初期質量
        double Mass;

        /// @brief 細胞の初期半径
        double Radius;

        /// @brief 細胞の初期数
        int32_t CellCount;

        /// @brief ふるまい定義
        CellBehaviorType BehaviorType;

        /// @brief 細胞の種類
        CellType Type;

        /// @brief 画像出力時の色
        Graphics::Color Color;
    };
}

#endif //!CELLSIM_CELLS_CELLCREATEINHO_HPP