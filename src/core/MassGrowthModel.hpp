#pragma once

#include "CellSimulationModel.hpp"
#include <vector>

/// @brief 細胞塊形成モデル
class MassGrowthModel : public CellSimulationModel {
    private:
    
    double m_adhesionThreshold; //接着している細胞の数がこの値以下の時に反発力が働く
    double m_coefficientCd; //反発力にかける係数
    double m_contactDistance; //細胞同士がこの値より近づくと反発力が発生
    double m_followerAttractionFactor; //接着している細胞の数がadhesion_thresholdより多い時に受ける引力にかける係数
    double m_globalAttractionFactor; //すべての細胞間にかかる力の係数
    double m_leaderRepulsionFactor; //接着している細胞の数がadhesion_thresholdの時に受ける反発力にかける係数
    double m_leaderRepulsionMaxDistance; //リーダーに届く反発力の最大距離
    double m_leaderRepulsionMinDistance; //リーダーに届く反発力の最小距離
    double m_leaderRepulsionRange; // m_leaderRepulsionMaxDistance - m_leaderRepulsionMinDistance
    double m_lambda; //力の届く範囲を決める値
    
    
    public:

    MassGrowthModel(CellAlgorithm& cellArgorithm) noexcept;

    void initCells(::std::vector<Cell*>& cells) override;

    Vec3 calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) override;

    void beforeNextStep(::std::vector<Cell*>& cells, ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
};