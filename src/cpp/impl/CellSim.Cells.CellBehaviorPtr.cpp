#include "CellSim.Cells.CellBehaviorPtr.hpp"
#include "CellSim.Cells.CellBehaviorType.hpp"
#include "CellSim.Cells.MoleculeAwareCellBehavior.hpp"
#include "CellSim.Cells.NormalCellBehavior.hpp"
#include "CellSim.Cells.WavePropagationCellBehavior.hpp"
#include "CellSim.Messages.hpp"
#include "../CellSim.Users.UserCellBehavior.hpp"
#include <stdexcept>

namespace CellSim::Cells
{

    CellBehaviorPtr CellBehaviorPtr::FromPointer(
        CellBehavior* ptr
    )
    {
        if (ptr == nullptr) [[unlikely]] {
            throw ::std::invalid_argument(
                Messages::Get(
                    "Cells.CellBehaviorPtr.FromPointer.Error"
                )
            );
        }

        return CellBehaviorPtr(ptr);
    }
}