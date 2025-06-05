#include "CellSim.Molecular.Molecule.hpp"

#include <stdexcept>

namespace CellSim::Molecular
{
    void Molecule::Amount(double amount)
    {
        if (amount < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'amount' must be greater than or equal to zero.");
        m_amount = amount;
    }
}