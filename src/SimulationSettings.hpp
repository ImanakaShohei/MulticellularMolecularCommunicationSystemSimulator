/**
 * @file SimulationSettings.hpp
 * @author Takanori Saiki
 * @brief シミュレーションのパラメータなどの設定を管理するクラス
 * @version 0.1
 * @date 2022-06-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cstdint>
#include <vector>
#include "PositionUpdateMethod.hpp"
#include "AlgorithmType.hpp"
#include "SimulationType.hpp"
#include "PerformanceKind.hpp"
#include <yaml-cpp/node/node.h>

class SimulationSettings final
{
    private:

    public:
    SimulationSettings() = delete;
    SimulationSettings(SimulationSettings const&) = delete;

    SimulationSettings& operator=(SimulationSettings const&) = delete;

    static bool init_settings();
    static void printSettings();

    static PerformanceKind PERFORMANCE;

    // 入力値チェックのため、uintではなくintを使う
    // そもそもuintを使ったところでそれほど大きな値を扱うわけではないので、intで十分
    static AlgorithmType ALGORITHM_TYPE;
    static SimulationType SIMULATION_TYPE;
    static int32_t CELL_SEED;
    static int32_t SIM_STEP;             //!< シミュレーションで行うステップの絶対数。シミュレーションの時間はDELTA_TIME*SIM_STEP[単位時間]となる。
    static int32_t OUTPUT_INTERVAL_STEP; //!< シミュレーション結果を出力するステップ間隔。

    static int32_t CELL_NUM;                            //!< シミュレーションで生成するCell数
    static PositionUpdateMethod POSITION_UPDATE_METHOD; //!< 細胞位置の更新方法(陽オイラー法やAdams-Bashforth法など)

    static int32_t CELL_LIST_GRID_SIZE_MAGNIFICATION; //!< CellListで使用するグリッドサイズの倍率。最小は1、値は2^nである必要がある。
    static int32_t CELL_LIST_SEARCH_RADIUS;           //!< この半径内(positionの差)にあるcellを力の計算の対象とする。

    static bool   USE_CLUSTER_MODEL; //シミュレーションでクラスタモデルを使うかどうか
    static double LAMBDA; //力が届く範囲を決める値
    static double REVERSE_LAMBDA; //力が届く範囲を決める値

    static int32_t FIELD_X_LEN; //!< シミュレーションをおこなうフィールドのx方向の辺の長さ。長さは2のn乗とする。
    static int32_t FIELD_Y_LEN; //!< シミュレーションをおこなうフィールドのy方向の辺の長さ。長さは2のn乗とする。
    static int32_t FIELD_Z_LEN; //!< シミュレーションをおこなうフィールドのz方向の辺の長さ。長さは2のn乗とする。

    static std::vector<int64_t> DEFAULT_MOLECULE_NUMS; //!< 分子の初期数(各分子の種類ごとに設定する)
    static int32_t MOLECULE_TYPE_NUM;                  //!< 分子の種類の数

    static int32_t MOLECULE_FIELD_X_LEN; //!< 分子のフィールドのx方向の辺の長さ。長さは2のn乗とする。
    static int32_t MOLECULE_FIELD_Y_LEN; //!< 分子のフィールドのy方向の辺の長さ。長さは2のn乗とする。
    static int32_t MOLECULE_FIELD_Z_LEN; //!< 分子のフィールドのz方向の辺の長さ。長さは2のn乗とする。

    static double DELTA_TIME;          //!< 時間スケール(1が通常時)
    static double MOLECULE_DELTA_TIME; //!< 分子の時間スケール(だいたいDELTA_TIMEより小さい)

    static bool CELL_GROWTH; //細胞の成長・分裂

    // 細胞塊成長モデル
    static uint32_t MG_ADHESIONTHRESHOLD; //接着している細胞の数がこの値以下の時に反発力が働く
    static double MG_COEFFICIENT_CD; //反発力にかける係数
    static double MG_CONTACT_DISTANCE; //細胞同士がこの値より近づくと反発力が発生
    static double MG_FOLLOWER_ATTRACTION_FACTOR; //接着している細胞の数がadhesion_thresholdより多い時に受ける引力にかける係数
    static double MG_GLOBAL_ATTRACTION_FACTOR; //すべての細胞間にかかる力の係数
    static double MG_INITIAL_RADIUS;  //細胞塊の初期半径
    static double MG_LEADER_REPULSION_FACTOR; //接着している細胞の数がadhesion_thresholdの時に受ける反発力にかける係数
    static double MG_LEADER_REPULSION_MAX_DISTANCE; //リーダーに届く反発力の最大距離
    static double MG_LEADER_REPULSION_MIN_DISTANCE; //リーダーに届く反発力の最小距離

    // 細胞塊成長モデル
    static double MR_ADHESION_DISTANCE_THRESHOLD; // 細胞同士がこの値より近いと接着力が働く
    static double MR_ADHESION_FORCE_FACTOR; // 接着力にかける係数
    static double MR_CENTRAL_FORCE_FACTOR; // 中心力にかける係数
    static double MR_REPULSION_FACTOR; // 反発力の係数
    static double MR_REPULSION_MAX_DISTANCE; // 細胞同士がこの値より近いと反発する

    // ネットワーク形成モデル
    static double NF_MAX_ATTRACTION_DISTANCE; //引力が届く最大距離
    static double NF_MIN_ATTRACTION_DISTANCE; //引力が働く最小距離
    static double NF_MAX_REPULSION_DISTANCE;  //斥力が働く最大距離
    static double NF_COEFFICIENT;             //力に掛ける係数

    // 信号分子拡散モデル
    static double SMD_DIFFUSION_COEFFICIENT; //拡散係数
    static double SMD_HYDROLYSYS_COEFFICIENT; // 加水分解係数
};
