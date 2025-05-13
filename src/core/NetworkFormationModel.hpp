#pragma once

#include "ClusterFormationModel.hpp"

class NetworkFormationModel : public ClusterFormationModel {
    private:

    static constexpr double s_dMax = 100.0;
    static constexpr double s_dMin = 40.0;
    static constexpr double s_dEx  = 20.0;

    static_assert(s_dMin >= 0, "s_dMinに負の値が指定されました");
    static_assert(s_dMax > s_dMin, "s_dMaxはs_dMinより大きくする必要があります");
    static_assert(s_dMin> s_dEx, "s_dExはs_dMinより小さくする必要があります");
    
    public:

    constexpr NetworkFormationModel(CellAlgorithm& cellArgorithm) noexcept : ClusterFormationModel(cellArgorithm) {}

    Vec3 calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;

    void onNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};