#ifndef BASE_HPP
#define BASE_HPP

#include <stdint.h>
#include <concepts>
#include <type_traits>

#if __has_include(<Windows.h>)
    #define CELLSIM_ENV_WINDOWS 1

    #if __cplusplus == 199711L
        #define CELLSIM_COMPILER_MSVC 1
        #define CELLSIM_CPP_LANG_VERSION _MSVC_LANG
    #else
        #define CELLSIM_COMPILER_MSVC 0
        #define CELLSIM_CPP_LANG_VERSION __cplusplus
    #endif

#endif

#if __has_include(<unistd.h>) && !defined(CELLSIM_ENV_WINDOWS)
    #define CELLSIM_ENV_UNIX 1
#endif

#ifdef __APPLE__
    #define CELLSIM_ENV_APPLE 1
#endif

#ifndef CELLSIM_CPP_LANG_VERSION
    #define CELLSIM_CPP_LANG_VERSION __cplusplus
#endif

#define CELLSIM_CPP11 201103L
#define CELLSIM_CPP14 201402L
#define CELLSIM_CPP17 201703L
#define CELLSIM_CPP20 202002L
#define CELLSIM_CPP23 202302L

#if CELLSIM_CPP_LANG_VERSION >= CELLSIM_CPP11
    #define CELLSIM_HAS_CPP11 1
#else
    #define CELLSIM_HAS_CPP11 0
#endif

#if CELLSIM_CPP_LANG_VERSION >= CELLSIM_CPP14
    #define CELLSIM_HAS_CPP14 1
#else
    #define CELLSIM_HAS_CPP14 0
#endif

#if CELLSIM_CPP_LANG_VERSION >= CELLSIM_CPP17
    #define CELLSIM_HAS_CPP17 1
#else
    #define CELLSIM_HAS_CPP17 0
#endif

#if CELLSIM_CPP_LANG_VERSION >= CELLSIM_CPP20
    #define CELLSIM_HAS_CPP20 1
#else
    #define CELLSIM_HAS_CPP20 0
#endif

#if CELLSIM_CPP_LANG_VERSION >= CELLSIM_CPP23
    #define CELLSIM_HAS_CPP23 1
#else
    #define CELLSIM_HAS_CPP23 0
#endif

#ifndef CELLSIM_ENV_WINDOWS
    #define CELLSIM_ENV_WINDOWS 0
#endif

#ifndef CELLSIM_ENV_UNIX
    #define CELLSIM_ENV_UNIX 0
#endif

#ifndef CELLSIM_COMPILER_MSVC
    #define CELLSIM_COMPILER_MSVC 0
#endif

#ifndef CELLSIM_ENV_APPLE
    #define CELLSIM_ENV_APPLE 0
#endif

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
    class NaiveAlgorithm;
    class NullAlgorithm;
    class ParticleMesh;
}

namespace CellSim::CellAlgorithms::Core
{

}

/// @brief 細胞関連
namespace CellSim::Cells
{
    class Cell;
    class CellBehavior;
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
    class MoleculeDiffusionBehavior;
    class NoMoleculeDiffusion;
    //class SimpleMoleculeDiffusion;
    class SignalMoleculeDiffusion;
}

/// @brief 数値関連
namespace CellSim::Numerics
{
    template <::std::floating_point TFloat>
    struct Vector3T;
}

/// @brief 各種設定
namespace CellSim::Settings
{
    class SettingLoader;
}

/// @brief コマンドライン処理
namespace CellSim::Settings::Cli
{
    class CliMain;
    class CliOptions;
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