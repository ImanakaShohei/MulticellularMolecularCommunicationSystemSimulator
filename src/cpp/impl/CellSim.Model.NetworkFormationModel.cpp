#include "CellSim.Model.NetworkFormationModel.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Settings.Config.SimulationModel.NetworkFormation.hpp"

#include <stdexcept>

namespace CellSim::Model
{
    NetworkFormationModel::NetworkFormationModel()
        : NetworkFormationModel(
            Settings::Config::SimulationModel::NetworkFormation::AdhesiveRepulsionFactor(),
            Settings::Config::SimulationModel::NetworkFormation::AttractionFactor(),
            Settings::Config::SimulationModel::NetworkFormation::Lambda(),
            Settings::Config::SimulationModel::NetworkFormation::MaxAttractionDistance(),
            Settings::Config::SimulationModel::NetworkFormation::MaxRepulsionDistance(),
            Settings::Config::SimulationModel::NetworkFormation::MinAttractionDistance(),
            Settings::Config::SimulationModel::NetworkFormation::RemoteForceFactor()
        )
    {
    }

    NetworkFormationModel::NetworkFormationModel(
        double adhesiveRepulsionFactor,
        double attractionFactor,
        double lambda,
        double maxAttractionDistance,
        double maxRepulsionDistance,
        double minAttractionDistance,
        double remoteForceFactor
    )
    : m_adhesiveRepulsionFactor(adhesiveRepulsionFactor)
    , m_attractionFactor(attractionFactor)
    , m_lambda(lambda)
    , m_maxAttractionDistance(maxAttractionDistance)
    , m_maxRepulsionDistance(maxRepulsionDistance)
    , m_minAttractionDistance(minAttractionDistance)
    , m_remoteForceFactor(remoteForceFactor)
    , m_reverseLambda(1.0 / lambda)
    , m_squareMaxAttractionDistance(maxAttractionDistance * maxAttractionDistance)
    {
        if (adhesiveRepulsionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'adhesiveRepulsionFactor' must be greater than or equal to zero.");
        if (lambda == 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'lambda' must be non-zero.");
        if (remoteForceFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'remoteForceFactor' must be greater than or equal to zero.");
    }

    void NetworkFormationModel::BeforeAdvanceStep(
        ::std::vector<Cells::Cell>&,
        ::std::vector<Molecule::MoleculeDiffusion> const&
    )
    {
    }

    Numerics::Vector3 NetworkFormationModel::ComputeForceOnCell(
        Cells::Cell const& target,
        ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecule::MoleculeDiffusion> const& molecules,
        const CellAlgorithms::CellAlgorithm* pCellAlgorithm
    ) const
    {
        Numerics::Vector3 force;

        Cells::CellInfo info{ target };
        const Cells::Cell* pTarget = &target;

        for (Cells::Cell const& cell : cells) {
            if (&cell == pTarget) continue;

            if (target.IsAdheringTo(cell)) {
                Numerics::Vector3 diff = target.Position() - cell.Position();
                double dist = diff.Length();

                double v = dist - m_minAttractionDistance;

                if (v > 0.0) {
                    force -= (v * m_attractionFactor / dist) * diff;
                }
                else {
                    v = m_maxRepulsionDistance;

                    if (v > 0.0) {
                        force += (v * m_adhesiveRepulsionFactor / (m_maxRepulsionDistance * dist)) * diff;
                    }
                }
            }
        }

        CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
            cellInfo,
            *pCellAlgorithm,
            target,
            cells,
            molecules,
            {
                if (!cellInfo.IsAlive) continue;

                const Numerics::Vector3 diff = info.Position - cellInfo.Position;
                const double mass            = info.Mass * cellInfo.Mass;

                force += (
                    -mass *
                    m_remoteForceFactor *
                    ::exp(-m_reverseLambda)
                ) * diff;
            }
        )

        return force;
    }

    void NetworkFormationModel::OnAdvanceStep(
        ::std::vector<Cells::Cell>& cells,
        ::std::vector<Molecule::MoleculeDiffusion> const& molecules
    )
    {
        for (Cells::Cell& cell : cells) {
            cell.ClearAttachedCells();
        }

        for (auto itr = cells.begin(), end = cells.end(); itr != end; ++itr) {
            Cells::Cell& cell1 = *itr;

            if (!cell1.IsAlive()) continue;

            for (auto itr2 = itr + 1; itr2 != end; ++itr2) {
                Cells::Cell& cell2 = *itr2;

                if (!cell2.IsAlive()) continue;

                Numerics::Vector3 diff = cell1.Position() - cell2.Position();
                
                if (diff.SquareLength() < m_squareMaxAttractionDistance) {
                    cell1.Adhere(cell2);
                    cell2.Adhere(cell1);
                }
            }
        }
    }
}