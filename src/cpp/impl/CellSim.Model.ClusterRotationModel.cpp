#include "CellSim.Model.ClusterRotationModel.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include "CellSim.Settings.Config.SimulationModel.ClusterRotation.hpp"

#include <stdexcept>

namespace CellSim::Model
{
    ClusterRotationModel::ClusterRotationModel()
        : ClusterRotationModel(
            Settings::Config::SimulationModel::ClusterRotation::AdhesionDistanceThreshold(),
            Settings::Config::SimulationModel::ClusterRotation::AdhesionForceFactor(),
            Settings::Config::SimulationModel::ClusterRotation::CentralForceFactor(),
            Settings::Config::SimulationModel::ClusterRotation::RepulsionFactor(),
            Settings::Config::SimulationModel::ClusterRotation::RepulsionMaxDistance()
        )
    {
    }

    ClusterRotationModel::ClusterRotationModel(
        double adhesionDistanceThreshold,
        double adhesionForceFactor,
        double centralForceFactor,
        double repulsionFactor,
        double repulsionMaxDistance
    )
        : m_adhesionDistanceThreshold(adhesionDistanceThreshold)
        , m_adhesionForceFactor(adhesionForceFactor)
        , m_centralForceFactor(centralForceFactor)
        , m_repulsionFactor(repulsionFactor)
        , m_repulsionMaxDistance(repulsionMaxDistance)
    {
        if (adhesionDistanceThreshold < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'adhesionDistanceThreshold' must be greater than or equal to zero.");
        if (adhesionForceFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'adhesionForceFactor' must be greater than or equal to zero.");
        if (centralForceFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'centralForceFactor' must be greater than or equal to zero.");
        if (repulsionFactor < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'repulsionFactor' must be greater than or equal to zero.");
        if (repulsionMaxDistance < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'repulsionMaxDistance' must be greater than or equal to zero.");

        if (repulsionMaxDistance >= adhesionDistanceThreshold) [[unlikely]] throw ::std::invalid_argument("'repulsionMaxDistance' must be less than 'adhesionDistanceThreshold'.");
    }

    void ClusterRotationModel::BeforeAdvanceStep(
        ::std::vector<Cells::Cell>&,
        ::std::vector<Molecular::MoleculeField> const&
    )
    {
    }

    Numerics::Vector3 ClusterRotationModel::ComputeForceOnCell(
        Cells::Cell const& target,
        ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecular::MoleculeField> const& molecules,
        const CellAlgorithms::CellAlgorithm* pCellAlgorithm
    ) const
    {
        Numerics::Vector3 force;
        Numerics::Vector3 forceCont;
        Cells::CellInfo info{ target };

        force -= info.Position * (m_centralForceFactor / info.Position.Length());

        CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
            cellInfo,
            *pCellAlgorithm,
            target,
            cells,
            molecules,
            {
                Numerics::Vector3 diff = info.Position - cellInfo.Position;
                double dist = diff.Length();

                if (dist < m_repulsionMaxDistance) {
                    force += diff * (m_repulsionFactor * (m_repulsionMaxDistance - dist) / (m_repulsionMaxDistance * dist));
                }

                if (dist < m_adhesionDistanceThreshold) {
                    forceCont += m_adhesionForceFactor * cellInfo.PreviusForce;
                }
            }
        )

        return (force + forceCont) * Settings::Config::Simulation::DeltaTime();
    }

    void ClusterRotationModel::OnAdvanceStep(
        ::std::vector<Cells::Cell>&,
        ::std::vector<Molecular::MoleculeField> const&
    )
    {
    }
}