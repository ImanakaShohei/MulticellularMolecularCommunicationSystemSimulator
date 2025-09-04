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
    CellBehaviorPtr CellBehaviorPtr::FromType(
        CellBehaviorType type
    )
    {
        switch (type) {
            case CellBehaviorType::MoleculeAware: return CellBehaviorPtr(new MoleculeAwareCellBehavior());
            case CellBehaviorType::Normal: return CellBehaviorPtr(new NormalCellBehavior());
            case CellBehaviorType::User: return CellBehaviorPtr(new Users::UserCellBehavior());
            case CellBehaviorType::WavePropagation: return CellBehaviorPtr(new WavePropagationCellBehavior());
            default: [[unlikely]]
            {
                throw ::std::invalid_argument(Messages::Get("Cells.CellBehaviorPtr.FromType.Error"));
            }
        }
    }

    CellBehaviorPtr CellBehaviorPtr::FromPointer(
        CellBehavior* ptr
    )
    {
        if (ptr == nullptr) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Cells.CellBehaviorPtr.FromPointer.Error"));

        return CellBehaviorPtr(ptr);
    }
}