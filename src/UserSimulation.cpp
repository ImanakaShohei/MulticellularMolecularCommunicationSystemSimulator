/**
 * @file UserSimulation.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-06-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "UserSimulation.hpp"

/**
 * @brief コンストラクタ。何も呼び出さない。
 *
 */
UserSimulation::UserSimulation(/* args */)
{
}

/**
 * @brief デストラクタ。何もしない。
 *
 */
UserSimulation::~UserSimulation()
{
}

/**
 * @brief シミュレーションで扱う細胞の初期化。ここで細胞を生成する。生成した細胞はcellsに格納する。
 * @note 各細胞の初期状態はユーザが定義する。
 *
 */
void UserSimulation::initCells() noexcept
{
    Simulation::initCells();
}

/**
 * @brief 各ステップの前処理。
 *
 */
void UserSimulation::stepPreprocess() noexcept
{
    int32_t preCellCount = (int32_t)cells.size();

    // すべての細胞の力を初期化する(速度を0に設定)
    for (int32_t i = 0; i < preCellCount; i++) {
        cells[i]->initForce();
    }

    for (int32_t i = 0; i < preCellCount; i++) {
        if (cells[i]->getCellType() == CellType::DEAD || cells[i]->getCellType() == CellType::NONE) {
            continue;
        }
        cells[i]->metabolize();
    }

    for (int32_t i = 0; i < preCellCount; i++) {
        if (cells[i]->getCellType() == CellType::DEAD || cells[i]->getCellType() == CellType::NONE) {
            continue;
        }

        if (cells[i]->checkWillDivide()) {
            auto c = std::make_shared<UserCell>(cells[i]->divide());

            // 分裂した場合は配列に新しいCellを上書き(あるいは追加)する。
            if (c->arrayIndex >= (int32_t)cells.size()) {
                cells.push_back(c);
            } else {
                cells[c->arrayIndex] = c;
            }
        }
    }
}

/**
 * @brief 各ステップの後処理。
 *
 */
void UserSimulation::stepEndProcess() noexcept
{
}