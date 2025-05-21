#include "CellSimulationModel.hpp"

class SignalMoleculeDiffusionModel : public CellSimulationModel {
    private:
    
    public:

    constexpr SignalMoleculeDiffusionModel(CellAlgorithm& cellAlgorithm) noexcept : CellSimulationModel(cellAlgorithm) {}

    void initCells(::std::vector<Cell*>& cells) override;

    constexpr Vec3 calcCellForce(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces) noexcept override;
    void onNextStep(::std::vector<Cell*>& cells, ::std::vector<MoleculeSpace*>& moleculeSpaces) override;
};

constexpr Vec3 SignalMoleculeDiffusionModel::calcCellForce(Cell&, ::std::vector<Cell*> const&, const ::std::vector<MoleculeSpace*>&) noexcept
{
    return Vec3::zero();
}