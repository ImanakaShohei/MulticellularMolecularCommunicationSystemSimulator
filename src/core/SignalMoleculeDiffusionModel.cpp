#include "SignalMoleculeDiffusionModel.hpp"
#include "SignalDiffusionCell.hpp"

void SignalMoleculeDiffusionModel::onNextStep(::std::vector<Cell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    UserMoleculeSpace* pSpace = moleculeSpaces[0];
    for (Cell* p : cells) {
        SignalDiffusionCell* pCell = static_cast<SignalDiffusionCell*>(p);

        switch (pCell->getCellType()) {
            case CellType::NONE:
            case CellType::DEAD:
                break;

            default:
            {
                pCell->updateState(
                    pSpace->getMoleculeNum(
                        pCell->getPosition()
                    )
                );
                break;
            }
            
        }
        
    }
}