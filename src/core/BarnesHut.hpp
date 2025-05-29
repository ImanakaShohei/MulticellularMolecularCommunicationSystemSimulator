#pragma once

#include "../SimulationSettings.hpp"
#include "Cell.hpp"
#include "../utils/Vec3.hpp"
#include "CellAlgorithm.hpp"
#include <vector>

// TODO: Barnes-Hutアルゴリズムを追加
// TODO: CellAlgorithmをpublic継承する
class BarnesHut : public CellAlgorithm {
    public:
    //TODO: 必要なメンバー関数を追加

    BarnesHut();

    Generator<CellInfo> iterateAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
    ::std::vector<CellInfo> getAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
};