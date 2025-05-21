#pragma once

#include "CellSimulationModel.hpp"
#include <vector>

/// @brief 細胞塊形成モデル
class MassGrowthModel : public CellSimulationModel {
    private:

    static constexpr double s_dMax = 150.0;
    static constexpr double s_dMin = 80.0;
    static constexpr double s_dCont = 20.0;
    static constexpr double s_lambda = 20.0;
    
    public:

    constexpr MassGrowthModel(CellAlgorithm& cellArgorithm) noexcept : CellSimulationModel(cellArgorithm) {}

    void initCells(::std::vector<Cell*>& cells) override;

    Vec3 calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;

    void beforeNextStep(::std::vector<Cell*>& cells, ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
};