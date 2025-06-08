#include "CellSim.Model.ClusterRotationModel.hpp"
#include "CellSim.Model.SimulationModelForceComputationArgs.hpp"
#include "CellSim.Model.SimulationModelStepArgs.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Numerics.Vector3T.hpp"
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
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }

    Numerics::Vector3 ClusterRotationModel::ComputeForceOnCell(
        const Simulation*,
        SimulationModelForceComputationArgs args
    ) const
    {
        Numerics::Vector3 force;
        Numerics::Vector3 forceCenter;
        Numerics::Vector3 forceCont;
        Cells::CellInfo info{ *args.Target };

        forceCenter = info.Position * (-m_centralForceFactor / info.Position.Length());

        CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE(
            cellInfo,
            *args.CellAlgorithm,
            args.Target,
            args.Cells,
            args.Fields,
            {
                Numerics::Vector3 diff = info.Position - cellInfo.Position;
                double dist = diff.Length();

                if (dist < m_repulsionMaxDistance) {
                    force += diff * ((m_repulsionMaxDistance - dist) / (m_repulsionMaxDistance * dist));
                }

                if (dist < m_adhesionDistanceThreshold) {
                    forceCont += cellInfo.PreviusForce;
                }
            }
        )

        return m_repulsionFactor * force + m_adhesionForceFactor * forceCont + forceCenter;
    }

    void ClusterRotationModel::OnAdvanceStep(
        const Simulation*,
        SimulationModelStepArgs
    )
    {
    }
}