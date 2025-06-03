#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.Model.CellGrowthModel.hpp"
#include "CellSim.Model.ClusterFormationModel.hpp"
#include "CellSim.Model.ClusterRotationModel.hpp"
#include "CellSim.Model.ClusterSproutingModel.hpp"
#include "CellSim.Model.NetworkFormationModel.hpp"
#include "CellSim.Model.NullModel.hpp"
#include "CellSim.Model.WavePropagationModel.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"
#include "../CellSim.Users.UserSimulationModel.hpp"

#include <stdexcept>

namespace CellSim::Model
{
    CellSimulationModel* CellSimulationModel::FromType(CellSimulationType type)
    {
        switch (Settings::Config::SimulationModel::SimulationType()) {
            case CellSimulationType::CellGrowth:       return new CellGrowthModel();
            case CellSimulationType::ClusterFormation: return new ClusterFormationModel();
            case CellSimulationType::ClusterRotation:  return new ClusterRotationModel();
            case CellSimulationType::ClusterSprouting: return new ClusterSproutingModel();
            case CellSimulationType::NetworkFormation: return new NetworkFormationModel();
            case CellSimulationType::Null:             return new NullModel();
            case CellSimulationType::User:             return new Users::UserSimulationModel();
            case CellSimulationType::WavePropagation:  return new WavePropagationModel();
            default: [[unlikely]]
            {
                throw ::std::invalid_argument("Invalid CellSim::Model::CellSimulationType argument.");
            }
        }
    }

    void CellSimulationModel::InitializeCells(::std::vector<Cells::Cell>& cells)
    {
        
    }
}