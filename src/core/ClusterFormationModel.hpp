#include "CellSimulationModel.hpp"

/// @brief クラスタ形成モデル
class ClusterFormationModel : public CellSimulationModel {
    public:

    constexpr ClusterFormationModel(CellAlgorithm& cellAlgorithm) noexcept : CellSimulationModel(cellAlgorithm) {}
};