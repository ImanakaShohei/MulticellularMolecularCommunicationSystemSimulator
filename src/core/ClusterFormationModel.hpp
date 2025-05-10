#pragma once

#include "CellSimulationModel.hpp"

/// @brief クラスタ形成モデル
class ClusterFormationModel : public CellSimulationModel {
    public:

    constexpr ClusterFormationModel(CellAlgorithm& cellAlgorithm) noexcept : CellSimulationModel(cellAlgorithm) {}

    void beforeNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};