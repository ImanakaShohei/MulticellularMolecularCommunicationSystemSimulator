#include "CellSim.Settings.Config.Molecular.hpp"
#include "CellSim.Messages.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    void Config::Molecular::Load(::nlohmann::json const& config)
    {
        if (config.is_null()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Molecular.Load.Error.JsonError"));

        ::std::string s1;
        ::std::string s2;

        try {
            s1 = config.at("boundaryCondition").get<::std::string>();
            s2 = config.at("initialDistribution").get<::std::string>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.Molecular.Load.Error.JsonError"));
        }

        if (s1 == "Absorbing") s_boundaryCondition = ::CellSim::Molecular::BoundaryCondition::Absorbing;
        else if (s1 == "Periodic") s_boundaryCondition = ::CellSim::Molecular::BoundaryCondition::Periodic;
        else if (s1 == "Reflective") s_boundaryCondition = ::CellSim::Molecular::BoundaryCondition::Reflective;
        else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Molecular.Load.Error.boundaryCondition"));

        if (s2 == "Centered") s_initialDistribution = ::CellSim::Molecular::InitialMoleculeDistribution::Centered;
        else if (s2 == "Gaussian") s_initialDistribution = ::CellSim::Molecular::InitialMoleculeDistribution::Gaussian;
        else if (s2 == "Uniform") s_initialDistribution = ::CellSim::Molecular::InitialMoleculeDistribution::Uniform;
        else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Molecular.Load.Error.initialDistribution"));
    }
}