#pragma once

enum class SimulationType
{
    ClusterFormation,           // クラスタ形成モデル
    MassGrowth,                 // 細胞塊成長モデル
    MassRotation,               // 細胞塊回転モデル
    NetworkFormation,           // ネットワーク形成モデル
    SignalMoleculeDiffusion,    // 信号分子拡散モデル
    UserSimulation,             // ユーザー定義モデル
};