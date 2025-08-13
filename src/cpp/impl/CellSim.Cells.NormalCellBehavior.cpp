#include "CellSim.Cells.NormalCellBehavior.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellDivisionResult.hpp"
#include "CellSim.Cells.CellGrowthResult.hpp"
#include "CellSim.Cells.CellMoleculeSensingArgs.hpp"
#include "CellSim.Cells.MolecularProcessArgs.hpp"
#include "CellSim.Cells.MolecularProcessResult.hpp"
#include "CellSim.Molecular.MoleculeInfo.hpp"
#include "CellSim.Settings.Config.Cell.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include "CellSim.Settings.Config.CellBehavior.Normal.hpp"
#include "CellSim.Messages.hpp"

#include <numbers>
#include <stdexcept>
#include <random>

namespace CellSim::Cells
{
    NormalCellBehavior::NormalCellBehavior()
        : NormalCellBehavior(
            Settings::Config::CellBehavior::Normal::CellDivisionRadius()
        )
    {
    }

    NormalCellBehavior::NormalCellBehavior(double cellDivisionRadius)
        : m_cellDivisionRadius(cellDivisionRadius)
        , m_growthRate(0)
        , m_isGrowthRateLoaded(false)
    {
        if (cellDivisionRadius <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cells.MoleculeAwareCellBehavior.MoleculeAwareCellBehavior.Error.cellDivisionRadius"));
    }

    CellGrowthResult NormalCellBehavior::ComputeGrowth(const Cell* sender)
    {
        double oldRadius = sender->Radius();

        if (!m_isGrowthRateLoaded) {
            auto type = sender->Type();
            for (auto const& info : Settings::Config::Cell::Cells()) {
                if (info.Type == type) {
                    m_growthRate = info.GrowthRate;
                    m_isGrowthRateLoaded = true;
                    break;
                }
            }
        }

        double newRadius = oldRadius + m_growthRate * Settings::Config::Simulation::DeltaTime();

        double tmp = newRadius / oldRadius;

        double newMass = tmp * tmp * tmp * sender->Mass();

        return CellGrowthResult{ newMass, newRadius };
    }

    CellDivisionResult NormalCellBehavior::ComputeDivisionOutcome(const Cell* sender)
    {
        CellDivisionResult result;

        double newRadius = sender->Radius() * ::cbrt(0.5);
        double newMass = sender->Mass() * 0.5;

        Numerics::Vector3 originalPosition = sender->Position();
        Numerics::Vector3 direction;

        // staticローカル変数はスレッドセーフ(らしい)
        static ::std::mt19937 mt{ Settings::Config::Cell::InitialPlacementSeed() };

        if (Settings::Config::Simulation::Enable2dMode()) {
            ::std::uniform_real_distribution<double> urd(0, ::std::numbers::pi * 2.0);
            double theta = urd(mt);
            direction.X = ::cos(theta);
            direction.Y = ::sin(theta);
        }
        else {
            ::std::uniform_real_distribution<double> urd(0, 1);
            double theta = urd(mt) * (::std::numbers::pi * 2.0);
            double phi = ::acos(1.0 - 2.0 * urd(mt));

            double sinPhi = ::sin(phi);

            direction.X = sinPhi * ::cos(theta);
            direction.Y = sinPhi * ::sin(theta);
            direction.Z = ::cos(phi);
        }

        direction *= newRadius;

        result.NewDaughter.NewMass = newMass;
        result.NewDaughter.NewRadius = newRadius;
        result.NewDaughter.NewPosition = originalPosition + direction;

        result.OriginalDaughter.NewRadius = newRadius;
        result.OriginalDaughter.NewMass = newMass;
        result.OriginalDaughter.NewPosition = originalPosition - direction;

        return result;
    }

    MolecularProcessResult NormalCellBehavior::ComputeMolecularProcess(const Cell*, MolecularProcessArgs)
    {
        return {};
    }

    Numerics::Vector3 NormalCellBehavior::OnSenseMolecules(const Cell*, CellMoleculeSensingArgs)
    {
        return Numerics::Vector3();
    }

    bool NormalCellBehavior::ShouldDivideThisStep(const Cell* sender) noexcept
    {
        return sender->Radius() > m_cellDivisionRadius;
    }
}