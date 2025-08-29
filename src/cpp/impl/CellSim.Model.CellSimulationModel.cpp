#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.Model.CellGrowthModel.hpp"
#include "CellSim.Model.ClusterFormationModel.hpp"
#include "CellSim.Model.ClusterRotationModel.hpp"
#include "CellSim.Model.ClusterSproutingModel.hpp"
#include "CellSim.Model.NetworkFormationModel.hpp"
#include "CellSim.Model.NullModel.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Settings.Config.Cell.hpp"
#include "CellSim.Settings.Config.CellBehavior.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include "CellSim.Settings.Config.SimulationModel.hpp"
#include "../CellSim.Users.UserSimulationModel.hpp"

#include <numbers>
#include <random>
#include <stdexcept>

#include <nlohmann/json.hpp>

namespace CellSim::Model
{
    CellSimulationModel::Params* CellSimulationModel::Params::FromJson(::nlohmann::json& j, CellSimulationType type)
    {
        if (j.is_null()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Model.CellSimulationModel.Params.FromJson.JsonError"));

        switch (type) {
            case CellSimulationType::CellGrowth:       return CellGrowthModel::Params::FromJson(j["cellGrowth"]);
            case CellSimulationType::ClusterFormation: return ClusterFormationModel::Params::FromJson(j["clusterFormation"]);
            case CellSimulationType::ClusterRotation:  return ClusterRotationModel::Params::FromJson(j["clusterRotation"]);
            case CellSimulationType::ClusterSprouting: return ClusterSproutingModel::Params::FromJson(j["clusterSprouting"]);
            case CellSimulationType::NetworkFormation: return NetworkFormationModel::Params::FromJson(j["networkFormation"]);
            case CellSimulationType::Null:             return NullModel::Params::FromJson();
            case CellSimulationType::User:             return Users::UserSimulationModel::Params::FromJson(j["user"]);
            default: [[unlikely]]
            {
                throw ::std::invalid_argument(Messages::Get("Model.CellSimulationModel.Params.FromJson.TypeError"));
            }
        }
    }

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
            default: [[unlikely]]
            {
                throw ::std::invalid_argument(Messages::Get("Model.CellSimulationModel.FromType.Error"));
            }
        }
    }

    void CellSimulationModel::InitializeCells(
        const Simulation*,
        ::std::vector<Cells::Cell>& cells
    )
    {
        ::std::mt19937 mt{ Settings::Config::Cell::InitialPlacementSeed() }; //乱数生成器(生成器はとりあえずメルセンヌ・ツイスタ)

        std::uniform_real_distribution<double> rand_theta(0, 2.0 * ::std::numbers::pi);
        std::uniform_real_distribution<double> rand_r(0, 1.0);

        
        double initialPlacementRadius = Settings::Config::Cell::InitialPlacementRadius();

        for (Cells::CellCreateInfo const& info : Settings::Config::Cell::Cells()) {
            Cells::CellBehaviorPtr pBehavior = Cells::CellBehaviorPtr::FromType(info.BehaviorType);

            if (Settings::Config::Simulation::Enable2dMode()) {
                for (int32_t i = 0; i != info.CellCount; i++) {
                    double r = ::sqrt(rand_r(mt)) * initialPlacementRadius;
                    double theta = rand_theta(mt);
                    double x = r * ::cos(theta);
                    double y = r * ::sin(theta);

                    cells.emplace_back(
                        info.Type,
                        pBehavior,
                        info.Mass,
                        info.Radius,
                        Numerics::Vector3(x, y, 0)
                    );
                }
            }
            else {
                for (int32_t i = 0; i != info.CellCount; i++) {
                    double v = rand_r(mt);

                    double theta = rand_theta(mt);
                    double phi = ::acos(1.0 - 2.0 * v);

                    double x = ::sin(phi) * ::cos(theta) * initialPlacementRadius;
                    double y = ::sin(phi) * ::sin(theta) * initialPlacementRadius;
                    double z = ::cos(phi) * initialPlacementRadius;

                    cells.emplace_back(
                        info.Type,
                        pBehavior,
                        info.Mass,
                        info.Radius,
                        Numerics::Vector3(x, y, z)
                    );
                }
            }
        }

    }
}