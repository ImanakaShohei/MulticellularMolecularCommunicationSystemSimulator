#include "CellSim.Molecular.Molecule.hpp"
#include "CellSim.Messages.hpp"
#include <stdexcept>

namespace CellSim::Molecular
{
    void Molecule::Amount(double amount)
    {
        if (amount < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("Molecular.Molecule.Amount.Error"));
        m_amount = amount;
    }
}