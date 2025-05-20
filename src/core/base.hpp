#pragma once

#include <stdint.h>
#include <concepts>
#include <type_traits>

#if __has_include(<Windows.h>)
    #define SIM_ENV_WINDOWS 1

    #if __cplusplus == 199711L
        #define SIM_COMPILER_MSVC 1
        #define SIM_CPP_LANG_VERSION _MSVC_LANG
    #else
        #define SIM_COMPILER_MSVC 0
        #define SIM_CPP_LANG_VERSION __cplusplus
    #endif

#endif

#if __has_include(<unistd.h>) && !defined(SIM_ENV_WINDOWS)
    #define SIM_ENV_UNIX 1
#endif

#ifdef __APPLE__
    #define SIM_ENV_APPLE 1
#endif

#ifndef SIM_CPP_LANG_VERSION
    #define SIM_CPP_LANG_VERSION __cplusplus
#endif

#define SIM_CPP11 201103L
#define SIM_CPP14 201402L
#define SIM_CPP17 201703L
#define SIM_CPP20 202002L
#define SIM_CPP23 202302L

#if SIM_CPP_LANG_VERSION >= SIM_CPP11
    #define SIM_HAS_CPP11 1
#else
    #define SIM_HAS_CPP11 0
#endif

#if SIM_CPP_LANG_VERSION >= SIM_CPP14
    #define SIM_HAS_CPP14 1
#else
    #define SIM_HAS_CPP14 0
#endif

#if SIM_CPP_LANG_VERSION >= SIM_CPP17
    #define SIM_HAS_CPP17 1
#else
    #define SIM_HAS_CPP17 0
#endif

#if SIM_CPP_LANG_VERSION >= SIM_CPP20
    #define SIM_HAS_CPP20 1
#else
    #define SIM_HAS_CPP20 0
#endif

#if SIM_CPP_LANG_VERSION >= SIM_CPP23
    #define SIM_HAS_CPP23 1
#else
    #define SIM_HAS_CPP23 0
#endif

#ifndef SIM_ENV_WINDOWS
    #define SIM_ENV_WINDOWS 0
#endif

#ifndef SIM_ENV_UNIX
    #define SIM_ENV_UNIX 0
#endif

#ifndef SIM_COMPILER_MSVC
    #define SIM_COMPILER_MSVC 0
#endif

#ifndef SIM_ENV_APPLE
    #define SIM_ENV_APPLE 0
#endif

enum class AlgorithmType;
enum class CellType;
enum class PerformanceKind;
enum class PositionUpdateMethod;
enum class SimulationType;

struct CellInfo;

class AsyncAction;
class BarnesHut;
class Cell;
class CellAlgorithm;
class CellSimulationModel;
class ClusterFormationModel;
class ClusterModel;
class MassGrowthModel;
class MassRotationModel;
class MoleculeSpace;
class NaiveAlgorithm;
class NetworkFormationModel;
class NormalCell;
class SignalDiffusionCell;
class SignalMoleculeDiffusionModel;
class Simulation;
class SimulationSettings;
class ThreadPool;
class Vec3;
class UserCell;
class UserCellAlgorithm;
class UserSimulationModel;

template <class T>
class Generator;

template <SimulationType SType>
struct SimulationTraits;