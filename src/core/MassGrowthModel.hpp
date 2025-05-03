#include "CellSimulationModel.hpp"
#include <vector>

/// @brief 細胞塊形成モデル
class MassGrowthModel : public CellSimulationModel {
    private:

    static constexpr double s_dMax = 150.0;
    static constexpr double s_dMin = 80.0;
    static constexpr double s_dCont = 20.0;
    static constexpr double s_lambda = 20.0;

    ::std::vector<std::vector<bool>> m_bondMatrix;
    
    public:

    MassGrowthModel(CellAlgorithm& cellAlgorithm);

    void initCells(::std::vector<UserCell*>& cells) override;

    Vec3 calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;

    void beforeNextStep(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};