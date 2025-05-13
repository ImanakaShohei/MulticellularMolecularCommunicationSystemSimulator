/**
 * @file Simulation.hpp
 * @author Takanori Saiki
 * @brief Simulation class
 * @version 0.1
 * @date 2022-04-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../UserCell.hpp"
#include "Cell.hpp"
#include "../SimulationSettings.hpp"
#include "../UserMoleculeSpace.hpp"
#include "../utils/Util.hpp"
#include "NaiveAlgorithm.hpp"
#include "CellList.hpp"
#include "BarnesHut.hpp"
#include "ClusterModel.hpp"
#include "CellSimulationModel.hpp"
#include "../threading/ThreadPool.hpp"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <memory>
#include <numbers>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

/**
 * @class Simulation
 * @brief Simulationの状態を管理するクラス。
 *
 */
class Simulation
{
  protected:
    ThreadPool m_threadPool;

    CellAlgorithm* cellAlgorithm;                            //!< CellListのデータ構造を管理するクラス
    CellList* cellList;
    CellSimulationModel* pCellSimulationModel;

    std::vector<UserCell*> cells; //!< シミュレーションで使うCellのリスト。
    std::streambuf* consoleStream;                //!< 標準出力のストリームバッファ

    std::vector<UserMoleculeSpace*> moleculeSpaces; //!< 分子の空間を管理するクラス。分子の種類ごとに1つの空間を持つ。

  private:
    // ヒープに確保したアルゴリズムのインスタンスを削除
    template <class TCellAlgorithm> requires ::std::derived_from<TCellAlgorithm, CellAlgorithm>
    static void deleteAlgorithm(CellAlgorithm* cellAlgorithm) noexcept;

    template <class TCellAlgorithm> requires ::std::derived_from<TCellAlgorithm, CellSimulationModel>
    static void deleteModel(CellSimulationModel* pCellSimulationModel) noexcept;

    // まだできていないクラスに対しては何もしない
    template <class TNotImplemented>
    static constexpr void deleteAlgorithm(CellAlgorithm*) noexcept {}

    template <class TNotImplemented>
    static constexpr void deleteModel(CellSimulationModel*) noexcept {}

    void printHeader() const noexcept;
    void printCells(int32_t time) const;
    void printMolecules(int32_t time) const;

    //  std::vector<std::unordered_set<int32_t>> aroundCellSetList;

    int32_t stepNumDigit;
    int32_t moleculeTypeNumDigit;

  public:
    Simulation(/* args */);
    ~Simulation();

    void exportConfig() const;

    void initCells();
    void initDirectories();
    
    Vec3 calcCellForce(UserCell& c) const noexcept;
    static Vec3 calcRemoteForce(UserCell&, UserCell&) noexcept;
    static Vec3 calcVolumeExclusion(UserCell&, UserCell&) noexcept;
    Vec3 calcForce(UserCell&) const noexcept;

    int32_t nextStep() noexcept;
    int32_t run();

    // pythonにパラメタを渡す都合上必要になった。
    int32_t getFieldLen();
};


inline void Simulation::initCells()
{
  pCellSimulationModel->initCells(cells);
}