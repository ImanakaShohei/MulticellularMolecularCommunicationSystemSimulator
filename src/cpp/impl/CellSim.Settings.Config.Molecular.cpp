#include "CellSim.Settings.Config.Molecular.hpp"
#include "CellSim.Settings.Config.Molecular.Behavior.hpp"
#include "CellSim.Molecular.MoleculeBehaviorKind.hpp"
#include "CellSim.Molecular.MoleculeKind.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    void Config::Molecular::Load(
        ::nlohmann::json& config
    )
    {
        if (config.is_null()) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get("Settings.Config.Molecular.Load.Error.JsonError")
            );
        }

        ::std::string s1;
        ::std::string s2;
        ::std::string s3;
        ::CellSim::Molecular::BoundaryCondition boundaryCondition;
        ::CellSim::Molecular::InitialMoleculeDistribution initialDistribution;
        ::CellSim::Molecular::MoleculeBehaviorKind behaviorkind;

        ::CellSim::Molecular::MoleculeKind::ResetUnsafe();

        try {
            for (::nlohmann::json& obj : config) {
                ::CellSim::Molecular::MoleculeCreateInfo info;

                s1 = obj.at("boundaryCondition").get<::std::string>();
                s2 = obj.at("initialDistribution").get<::std::string>();
                s3 = obj.at("behaviorType").get<::std::string>();

                if (s1 == "Absorbing") boundaryCondition = ::CellSim::Molecular::BoundaryCondition::Absorbing;
                else if (s1 == "Periodic") boundaryCondition = ::CellSim::Molecular::BoundaryCondition::Periodic;
                else if (s1 == "Reflective") boundaryCondition = ::CellSim::Molecular::BoundaryCondition::Reflective;
                else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Molecular.Load.Error.boundaryCondition"));

                if (s2 == "Centered") initialDistribution = ::CellSim::Molecular::InitialMoleculeDistribution::Centered;
                else if (s2 == "Gaussian") initialDistribution = ::CellSim::Molecular::InitialMoleculeDistribution::Gaussian;
                else if (s2 == "Uniform") initialDistribution = ::CellSim::Molecular::InitialMoleculeDistribution::Uniform;
                else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Molecular.Load.Error.initialDistribution"));

                if (s3 == "Normal") behaviorkind = ::CellSim::Molecular::MoleculeBehaviorKind::Normal;
                else if (s3 == "Null") behaviorkind = ::CellSim::Molecular::MoleculeBehaviorKind::Null;
                else if (s3 == "User") behaviorkind = ::CellSim::Molecular::MoleculeBehaviorKind::User;
                else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Molecular.Load.Error.behaviorType"));

                double colorIntensityThreshold = obj.at("colorIntensityThreshold").get<double>();

                if (colorIntensityThreshold <= 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Molecular.Load.Error.colorIntensityThreshold"));

                info.Behavior = ::std::unique_ptr<::CellSim::Molecular::MoleculeBehavior>(Behavior::FromJson(obj["behaviorParameters"], behaviorkind));
                info.BoundaryCondition = boundaryCondition;
                info.InitialDistribution = initialDistribution;
                info.GridCount = obj.at("gridCount").get<size_t>();
                info.MoleculeAmount = obj.at("moleculeAmount").get<double>();

                try {
                    info.Kind = ::CellSim::Molecular::MoleculeKind::AddName(
                        obj.at("moleculeKind").get<::std::string>(),
                        colorIntensityThreshold
                    );
                }
                catch (...) {
                    throw ::std::runtime_error(
                        Messages::Get("Settings.Config.Molecular.Load.Error.moleculeKind")
                    );
                }
                
                s_molecularConfigs.emplace_back(::std::move(info));
            }
        }
        catch (::std::runtime_error) {
            ::std::rethrow_exception(::std::current_exception());
        }
        catch (::std::exception) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.Molecular.Load.Error.JsonError"));
        }
    }
}