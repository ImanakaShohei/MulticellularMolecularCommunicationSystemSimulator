#include "CellSim.Cells.MoleculeAwareCellBehavior.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.MolecularProcessArgs.hpp"
#include "CellSim.Cells.MolecularProcessResult.hpp"
#include "CellSim.Cells.CellMoleculeSensingArgs.hpp"
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
        : NormalCellBehavior(cellDivisionRadius)
        , m_synthesisRate(synthesisRate)
        , m_degradationRate(degradationRate)
    {
        if (synthesisRate <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cells.MoleculeAwareCellBehavior.MoleculeAwareCellBehavior.Error.synthesisRate"));
        if (degradationRate <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cells.MoleculeAwareCellBehavior.MoleculeAwareCellBehavior.Error.degradationRate"));
    }

    MolecularProcessResult MoleculeAwareCellBehavior::ComputeMolecularProcess(const Cell* sender, MolecularProcessArgs args)
    {
        MolecularProcessResult result;
        result.ExtracellularChange = 0;
        result.IntracellularChange = (m_synthesisRate - m_degradationRate * args.IntracellularAmount) * Settings::Config::Simulation::DeltaTime();

        return result;
    }

    Numerics::Vector3 MoleculeAwareCellBehavior::OnSenseMolecules(const Cell*, CellMoleculeSensingArgs)
    {
        // TODO: ここに処理を追加します
        return Numerics::Vector3();
    }
}