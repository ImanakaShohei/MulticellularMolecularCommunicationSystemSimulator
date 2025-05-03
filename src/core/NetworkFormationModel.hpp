#include "CellSimulationModel.hpp"
#include <vector>

class NetworkFormationModel : public CellSimulationModel {
    private:

    static constexpr double s_dMax = 100.0;
    static constexpr double s_dMin = 40.0;
    static constexpr double s_dEx = 20.0;
    static constexpr double s_lambda = 20.0;

    static_assert(s_dMin >= 0, "s_dMinに負の値が指定されました");
    static_assert(s_dMax > s_dMin, "s_dMaxはs_dMinより大きくする必要があります");

    ::std::vector<::std::vector<bool>> m_bondMatrix;
    
    public:

    NetworkFormationModel(CellAlgorithm& cellArgorithm);

    Vec3 calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;

    void onNextStep(const ::std::vector<UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};