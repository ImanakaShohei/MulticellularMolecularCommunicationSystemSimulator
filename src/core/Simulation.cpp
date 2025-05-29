#include "Simulation.hpp"

#include "BarnesHut.hpp"
#include "ClusterFormationModel.hpp"
#include "ClusterModel.hpp"
#include "EmptyMoleculeSpace.hpp"
#include "MassGrowthModel.hpp"
#include "MassRotationModel.hpp"
#include "NaiveAlgorithm.hpp"
#include "NetworkFormationModel.hpp"
#include "NormalCell.hpp"
#include "SignalDiffusionCell.hpp"
#include "SignalDiffusionMoleculeSpace.hpp"
#include "SignalMoleculeDiffusionModel.hpp"
#include "../UserCellAlgorithm.hpp"
#include "../UserMoleculeSpace.hpp"
#include "../UserSimulationModel.hpp"
#include "../UserCell.hpp"
#include <filesystem>
#include <fstream>

// TODO: cellsをスマートポインタの配列にする。

/**
 * @brief 基本となるコンストラクタ。
 * @details
 * 各乱数生成器と遠隔力フィールドを初期化する。また、標準出力のストリームバッファを保存しておく。
 * @note
 * 例えば、(-8/2, 8/2)でランダムな値を生成すると長さ8の配列に収まるようになる。
 * {[-4, -3), [-3, -2), [-2, -1), [-1, 0), [0, 1), [1, 2), [2, 3), [3, 4)}
 */
Simulation::Simulation()
  : m_threadPool()
  , cellAlgorithm(nullptr)
  , cellList(SimulationSettings::USE_CLUSTER_MODEL ? new CellList() : nullptr)
  , pCellSimulationModel(nullptr)
  , moleculeSpaces(SimulationSettings::MOLECULE_TYPE_NUM)
  , stepNumDigit((int32_t)std::log10(SimulationSettings::SIM_STEP) + 1) // ファイル名の0埋めに使う
  , moleculeTypeNumDigit((int32_t)std::log10(SimulationSettings::MOLECULE_TYPE_NUM) + 1) /// ファイル名の0埋めに使う
{
    switch (SimulationSettings::ALGORITHM_TYPE) {
        case AlgorithmType::Naive: cellAlgorithm = new NaiveAlgorithm(); break;
        case AlgorithmType::CellList:
        {
            cellAlgorithm = SimulationSettings::USE_CLUSTER_MODEL ? cellList : new CellList();
            break;
        }
        case AlgorithmType::BarnesHut: cellAlgorithm = new BarnesHut(); break;
        case AlgorithmType::User: cellAlgorithm = new UserCellAlgorithm(); break;
    }

    switch (SimulationSettings::SIMULATION_TYPE) {
        case SimulationType::ClusterFormation: pCellSimulationModel = new ClusterFormationModel(*cellAlgorithm); break;
        case SimulationType::MassGrowth: pCellSimulationModel = new MassGrowthModel(*cellAlgorithm); break;
        case SimulationType::MassRotation: pCellSimulationModel = new MassRotationModel(*cellAlgorithm); break;
        case SimulationType::NetworkFormation: pCellSimulationModel = new NetworkFormationModel(*cellAlgorithm); break;
        case SimulationType::SignalMoleculeDiffusion: pCellSimulationModel = new SignalMoleculeDiffusionModel(*cellAlgorithm); break;
        case SimulationType::UserSimulation: pCellSimulationModel = new UserSimulationModel(*cellAlgorithm); break;
    }

    switch (SimulationSettings::SIMULATION_TYPE) {
        case SimulationType::ClusterFormation:
        case SimulationType::MassGrowth:
        case SimulationType::MassRotation:
        case SimulationType::NetworkFormation:
        {
            for (int i = 0; i < SimulationSettings::MOLECULE_TYPE_NUM; i++) {
                moleculeSpaces[i] = new EmptyMoleculeSpace();
            }
            break;
        }
        case SimulationType::SignalMoleculeDiffusion:
        {
            for (int i = 0; i < SimulationSettings::MOLECULE_TYPE_NUM; i++) {
                moleculeSpaces[i] = new SignalDiffusionMoleculeSpace(
                    SimulationSettings::DEFAULT_MOLECULE_NUMS[i],
                    MoleculeDistributionType::UNIFORM,
                    MoleculeSpaceBorderType::NEUMANN,
                    &cells,
                    i
                );
            }
            break;
        }
        case SimulationType::UserSimulation:
        {
            for (int i = 0; i < SimulationSettings::MOLECULE_TYPE_NUM; i++) {
                moleculeSpaces[i] = new UserMoleculeSpace(
                    SimulationSettings::DEFAULT_MOLECULE_NUMS[i],
                    MoleculeDistributionType::UNIFORM,
                    MoleculeSpaceBorderType::NEUMANN,
                    &cells,
                    i
                );
            }
            break;
        }
    }
    
}

/**
 * @brief いまのところ何もしない。と思っていたのか？
 *
 */
Simulation::~Simulation()
{
   switch (SimulationSettings::ALGORITHM_TYPE) {
        case AlgorithmType::Naive: deleteAlgorithm<NaiveAlgorithm>(cellAlgorithm); break;
        case AlgorithmType::CellList: /*本当に何もしない*/ break;
        case AlgorithmType::BarnesHut: deleteAlgorithm<BarnesHut>(cellAlgorithm); break;
        case AlgorithmType::User: deleteAlgorithm<UserCellAlgorithm>(cellAlgorithm); break;
    }

    if (cellList != nullptr) delete cellList;
    
    switch (SimulationSettings::SIMULATION_TYPE) {
        case SimulationType::ClusterFormation: deleteModel<ClusterFormationModel>(pCellSimulationModel); break;
        case SimulationType::MassGrowth: deleteModel<MassGrowthModel>(pCellSimulationModel); break;
        case SimulationType::MassRotation: deleteModel<MassRotationModel>(pCellSimulationModel); break;
        case SimulationType::NetworkFormation: deleteModel<NetworkFormationModel>(pCellSimulationModel); break;
        case SimulationType::SignalMoleculeDiffusion: deleteModel<SignalMoleculeDiffusionModel>(pCellSimulationModel); break;
        case SimulationType::UserSimulation: deleteModel<UserSimulationModel>(pCellSimulationModel); break;
    }

    switch (SimulationSettings::SIMULATION_TYPE) {
        case SimulationType::ClusterFormation:
        case SimulationType::MassGrowth:
        case SimulationType::MassRotation:
        case SimulationType::NetworkFormation:
        {
            for (Cell* pCell : cells) {
                delete static_cast<NormalCell*>(pCell);
            }

            for (MoleculeSpace* pSpace : moleculeSpaces) {
                delete static_cast<EmptyMoleculeSpace*>(pSpace);
            }
            break;
        }
        case SimulationType::SignalMoleculeDiffusion:
        {
            for (Cell* pCell : cells) {
                delete static_cast<SignalDiffusionCell*>(pCell);
            }

            for (MoleculeSpace* pSpace : moleculeSpaces) {
                delete static_cast<SignalDiffusionMoleculeSpace*>(pSpace);
            }
            break;
        }
        case SimulationType::UserSimulation:
        {
            for (Cell* pCell : cells) {
                delete static_cast<UserCell*>(pCell);
            }

            for (MoleculeSpace* pSpace : moleculeSpaces) {
                delete static_cast<UserMoleculeSpace*>(pSpace);
            }
            break;
        }
    }
    
    
}

/**
 * @brief 設定ファイルに出力画像のサイズなどを書き込む。
 *
 */
void Simulation::exportConfig() const
{
    std::ofstream outputfile("config.txt");
    outputfile << SimulationSettings::FIELD_X_LEN << std::endl;
    outputfile << SimulationSettings::FIELD_Y_LEN << std::endl;
    outputfile << SimulationSettings::SIM_STEP << std::endl;

    const double TIME_PER_FILE = SimulationSettings::DELTA_TIME * (double)SimulationSettings::OUTPUT_INTERVAL_STEP;

    outputfile << TIME_PER_FILE << std::endl;

    outputfile.close();
}

void Simulation::initDirectories()
{
    if (!std::filesystem::exists("result")) std::filesystem::create_directory("result");

    if (!std::filesystem::exists("molecule_result")) std::filesystem::create_directory("molecule_result");

    std::filesystem::path dirPath;

    for (int i = 0; i < SimulationSettings::MOLECULE_TYPE_NUM; i++) {
        dirPath = "molecule_result/" + std::string(moleculeTypeNumDigit, '0');
        
        if (!std::filesystem::exists(dirPath)) std::filesystem::create_directory(dirPath);
    }
}

template <class TCellAlgorithm> requires ::std::derived_from<TCellAlgorithm, CellAlgorithm>
void Simulation::deleteAlgorithm(CellAlgorithm* cellAlgorithm) noexcept
{
    delete static_cast<TCellAlgorithm*>(cellAlgorithm);
}

template <class TCellAlgorithm> requires ::std::derived_from<TCellAlgorithm, CellSimulationModel>
void Simulation::deleteModel(CellSimulationModel* pCellSimulationModel) noexcept
{
    delete static_cast<TCellAlgorithm*>(pCellSimulationModel);
}

/**
 * @brief ファイルにヘッダ情報を出力する。
 *
 */
void Simulation::printHeader(::std::ostream& out) const noexcept
{
    // std::cout << "ID\ttypeID\tX\tY\tZ\tVx\tVy\tVz\tR\tN_contact\tContact_IDs" << std::endl;
    out << "ID\tX\tY" << std::endl;
}

/**
 * @brief ファイルに現在のすべてのCell情報を出力する。
 *
 * @param time
 */
void Simulation::printCells(int32_t time) const
{
    std::ostringstream sout;
    sout << std::setfill('0') << std::setw(stepNumDigit) << time;

    std::string outputPath = "./result/cells_" + sout.str();
    std::ofstream ofs(outputPath);
    printHeader(ofs);
    for (auto pCell : cells) {
        if (pCell->getCellType() == CellType::NONE) continue;

        pCell->printCell(ofs);
    }
}

void Simulation::printMolecules(int32_t time) const
{
    std::ostringstream sout;
    sout << std::setfill('0') << std::setw(stepNumDigit) << time;
    std::string outputPath = "./molecule_result/" + std::string(moleculeTypeNumDigit, '0') + "/molecule_" + sout.str();

    for (int32_t i = 0; i < SimulationSettings::MOLECULE_TYPE_NUM; i++) {
        std::ostringstream typeSout;
        typeSout << std::setfill('0') << std::setw(moleculeTypeNumDigit) << i;
        outputPath.replace(18, moleculeTypeNumDigit, typeSout.str());
        std::ofstream ofs(outputPath);

        // ファイルに書き込まれる
        moleculeSpaces[i]->print(ofs);
    }
}

/**
 * @brief 細胞間作用の計算。細胞の種類に応じて計算を行う。
 *
 * @param c
 * @return Vec3
 */
Vec3 Simulation::calcCellForce(Cell& c) const noexcept
{
    return pCellSimulationModel->calcCellForce(c, cells, moleculeSpaces);
}

/**
 * @brief 指定したCellにかかるすべての力を計算する。O(n^2)
 *
 * @param c
 * @return Vec3
 */
Vec3 Simulation::calcForce(Cell& c) const noexcept
{
    // Vec3 force = Vec3::zero();

    // force += cellAlgorithm->calcCellForce(c, cells, moleculeSpaces);
    // force += calcRemoteForce(c);
    // force += calcVolumeExclusion(c);

    return calcCellForce(c);
}

/**
 * @brief 各ステップでの前処理
 *
 * @details 
 */
void Simulation::beforeNextStep()
{
    // すべての細胞の力を初期化する(速度を0に設定)
    for (auto pCell : cells) {
        pCell->initForce();
    }

    if (!SimulationSettings::CELL_GROWTH) return;

    // ここから先は細胞の成長と分裂の処理

    for (auto pCell : cells) {
        Cell& c = *pCell;

        switch (c.getCellType()) {
            case CellType::DEAD:
            case CellType::NONE:
                break;

            default:
                c.metabolize();
                break;
        }
    }

    // 要素数の変更があるので連想for文は使わない
    for (uint32_t i = 0; i < cells.size(); i++) {
        Cell& cell = *cells[i];

        switch (cell.getCellType()) {
            case CellType::DEAD:
            case CellType::NONE:
                break;

            default:
            {
                if (!cell.checkWillDivide()) break;

                Cell* c;
                
                switch (SimulationSettings::SIMULATION_TYPE) {
                    case SimulationType::ClusterFormation:
                    case SimulationType::MassGrowth:
                    case SimulationType::MassRotation:
                    case SimulationType::NetworkFormation:
                    {
                        auto& ref = static_cast<NormalCell&>(cell);
                        c = new NormalCell(ref.divide());
                        break;
                    }
                    case SimulationType::SignalMoleculeDiffusion:
                    {
                        auto& ref = static_cast<SignalDiffusionCell&>(cell);
                        c = new SignalDiffusionCell(ref.divide());
                        break;
                    }
                    case SimulationType::UserSimulation:
                    {
                        auto& ref = static_cast<UserCell&>(cell);
                        c = new UserCell(ref.divide());
                        break;
                    }
                }
                
                // 分裂した場合は配列に新しいCellを上書き(あるいは追加)する。
                if (c->arrayIndex >= (int32_t)cells.size()) {
                    cells.push_back(c);
                }
                else {
                    cells[c->arrayIndex] = c;
                }
                
                break;
            }
        }
    }
}

/**
 * @brief すべてのCellに力を加えた後、それぞれのCellの位置を更新する。
 *
 * @return int32_t
 * @details Cellの数が多いので、スレッドを用いて並列処理を行う。
 */
int32_t Simulation::nextStep() noexcept
{
    beforeNextStep();
    pCellSimulationModel->beforeNextStep(cells, moleculeSpaces);

    if (SimulationSettings::USE_CLUSTER_MODEL) {
        if (SimulationSettings::ALGORITHM_TYPE != AlgorithmType::CellList) cellList->setCells(cells);
        
        ClusterModel::combine(cells, moleculeSpaces, *cellList);
        cellList->setCells(cells);
    }

    // XXX: スレッド数を増やしてもメモリアクセスがボトルネックになってしまう。が気にしない
    m_threadPool.parallelFor(
        0, 
        cells.size(),
        [this](size_t i) {
            Cell& cell = *cells[i];
            switch (cell.getCellType()) {
                case CellType::DEAD:
                case CellType::NONE:
                    break;

                default:
                    cell.addForce(calcCellForce(cell));
                    break;
            }
        }
    );

    for (int32_t i = 0; i < SimulationSettings::MOLECULE_TYPE_NUM; i++) {
        moleculeSpaces[i]->calcConcentrationDiff();
    }

    for (auto cell : cells) {
        cell->nextStep();
    }

    for (int32_t i = 0; i < SimulationSettings::MOLECULE_TYPE_NUM; i++) {
        moleculeSpaces[i]->nextStep();
    }

    pCellSimulationModel->onNextStep(cells, moleculeSpaces);

    return 0;
}

/**
 * @brief シミュレーションを実行する。
 *
 * @return int32_t
 * @details Cellの位置更新と情報出力を繰り返すだけ。
 */
int32_t Simulation::run()
{
    std::cout << "ThreadPool max threads: " << m_threadPool.threadCount() << std::endl;

    printCells(0);
    printMolecules(0);
    int64_t sumTime = 0;

    std::cout << "initialized." << std::endl;

    for (int32_t step = 1; step < SimulationSettings::SIM_STEP; step++) {
        auto start = std::chrono::system_clock::now();

        nextStep();

        const bool willOut = (step % SimulationSettings::OUTPUT_INTERVAL_STEP) == 0;
        if (willOut) {
            printCells(step / SimulationSettings::OUTPUT_INTERVAL_STEP);
            printMolecules(step / SimulationSettings::OUTPUT_INTERVAL_STEP);
        }
        const bool wasOut = willOut;

        auto end  = std::chrono::system_clock::now();
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "step: " << step << "  " << msec << "msec" << (wasOut ? " output saved" : "") << std::endl;
        sumTime += msec;
    }

    const double averageTime = (double)sumTime / (double)SimulationSettings::SIM_STEP;
    ::std::cout << "Initial cell count      : " << SimulationSettings::CELL_NUM << ::std::endl;
    ::std::cout << "Average processing time : " << averageTime << ::std::endl;
    ::std::cout << "Simulation model        : ";

    switch (SimulationSettings::SIMULATION_TYPE) {
        case SimulationType::ClusterFormation:        ::std::cout << "ClusterFormation"; break;
        case SimulationType::MassGrowth:              ::std::cout << "MassGrowth"; break;
        case SimulationType::MassRotation:            ::std::cout << "MassRotation"; break;
        case SimulationType::NetworkFormation:        ::std::cout << "NetworkFormation"; break;
        case SimulationType::SignalMoleculeDiffusion: ::std::cout << "SignalMoleculeDiffusion"; break;
        case SimulationType::UserSimulation:          ::std::cout << "UserSimulation"; break;
    }

    ::std::cout << ::std::endl;

    ::std::cout << "Algorithm               : ";

    switch (SimulationSettings::ALGORITHM_TYPE) {
        case AlgorithmType::Naive:     std::cout << "Naive";         break;
        case AlgorithmType::CellList:  std::cout << "CellList";      break;
        case AlgorithmType::BarnesHut: std::cout << "BarnesHut";     break;
        case AlgorithmType::User:      std::cout << "UserAlgorithm"; break;
    }

    if (SimulationSettings::USE_CLUSTER_MODEL) std::cout << "+Cluster";
    ::std::cout << ::std::endl;

    return 0;
}

/**
 * @brief
 * なくてもいい。Pythonに情報を渡す都合上必要かもしれなかった。(使っていない)
 *
 * @return int32_t
 */
int32_t Simulation::getFieldLen()
{
    return SimulationSettings::FIELD_X_LEN;
}