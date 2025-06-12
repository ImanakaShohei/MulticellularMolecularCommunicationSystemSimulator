#include "CellSim.Cells.MoleculeAwareCellBehavior.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellMetabolicArgs.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Settings.Config.CellBehavior.MoleculeAware.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include <stdexcept>

namespace CellSim::Cells
{
    MoleculeAwareCellBehavior::MoleculeAwareCellBehavior()
        : MoleculeAwareCellBehavior(
            Settings::Config::CellBehavior::MoleculeAware::CellDivisionRadius(),
            Settings::Config::CellBehavior::MoleculeAware::SynthesisRate(),
            Settings::Config::CellBehavior::MoleculeAware::DegradationRate()
        )
    {
    }

    MoleculeAwareCellBehavior::MoleculeAwareCellBehavior(
        double cellDivisionRadius,
        double synthesisRate,
        double degradationRate
    )
        : m_cellDivisionRadius(cellDivisionRadius)
        , m_synthesisRate(synthesisRate)
        , m_degradationRate(degradationRate)
    {
        if (m_cellDivisionRadius <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cells.MoleculeAwareCellBehavior.MoleculeAwareCellBehavior.Error.cellDivisionRadius"));
        if (m_synthesisRate <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cells.MoleculeAwareCellBehavior.MoleculeAwareCellBehavior.Error.synthesisRate"));
        if (m_degradationRate <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cells.MoleculeAwareCellBehavior.MoleculeAwareCellBehavior.Error.degradationRate"));
    }

    double MoleculeAwareCellBehavior::ComputeMetabolicChange(const Cell* sender, CellMetabolicArgs args)
    {
        return (m_synthesisRate + m_degradationRate * args.MoleculeInfo.Amount) * Settings::Config::Simulation::DeltaTime();
    }

    bool MoleculeAwareCellBehavior::ShouldDivideThisStep(const Cell* sender) noexcept
    {
        return sender->Radius() > m_cellDivisionRadius;
    }
}