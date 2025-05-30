#ifndef BASE_HPP
#define BASE_HPP

#include <stdint.h>
#include <concepts>
#include <type_traits>

// クラスをインスタンス化できないようにする
#define CELLSIM_STATIC_CLASS(className)                 \
    className() = delete;                               \
    className(className const&) = delete;               \
    className(className&&) = delete;                    \
    className& operator=(className const&) = delete;    \
    className& operator=(className&&) = delete;         \
    ~className() = delete

/// @brief シミュレーターの既定の名前空間
namespace CellSim
{
    class Simulation;
}

/// @brief 高速化アルゴリズム
namespace CellSim::CellAlgorithms
{
    class BarnesHut;
    class CellAlgorithm;
    class CellList;
    class ClusterModel;
    class ParticleMesh;
}

namespace CellSim::CellAlgorithms::Core
{

}

/// @brief 細胞関連
namespace CellSim::Cells
{
    class Cell;
    struct CellInfo;
    enum class CellType;
}

/// @brief 画像処理
namespace CellSim::Imaging
{

}

/// @brief シミュレーションモデル
namespace CellSim::Model
{
    class CellGrowthModel;
    class ClusterFormationModel;
    class ClusterRotationModel;
    class ClusterSproutingModel;
    class NetworkFormationModel;
    class NullModel;
    class SimulationModel;
    class WavePropagationModel;
}

/// @brief 分子拡散など
namespace CellSim::Model::Molecule
{
    class MoleculeDiffusion;
    class NoMoleculeDiffusion;
    //class SimpleMoleculeDiffusion;
    class SignalMoleculeDiffusion;
}

/// @brief 各種設定
namespace CellSim::Options
{
    class SettingLoader;
}

/// @brief コマンドライン処理
namespace CellSim::Options::Cli
{

}

/// @brief 数値関連
namespace CellSim::Numerics
{
    template <::std::floating_point TFloat>
    struct Vector3T;
}

/// @brief 並列処理とコルーチン
namespace CellSim::Threading
{
    class AsyncAction;

    template <class T>
    class Generator;

    class StlThreadPool;
    class ThreadPool;
    
}

// エイリアス定義
namespace CellSim::Numerics
{
    using Vector3F = Vector3T<float>;
    using Vector3 = Vector3T<double>;
    using Vector3L = Vector3T<long double>;
}

#endif //!BASE_HPP