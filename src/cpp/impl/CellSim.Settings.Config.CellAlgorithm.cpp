#include "CellSim.Settings.Config.CellAlgorithm.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.BarnesHut.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.CellList.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.ParticleMesh.hpp"
#include "CellSim.Messages.hpp"
#include "../CellSim.Settings.Config.CellAlgorithm.User.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    void Config::CellAlgorithm::Load(::nlohmann::json& config)
    {
        if (config.is_null()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellAlgorithm.Load.Error.JsonError"));

        ::std::string s;
        try {
            s_useClusterModel = config.at("useClusterModel").get<bool>();
            s = config.at("algorithmType").get<::std::string>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.CellAlgorithm.Load.Error.JsonError"));
        }

        if (s == "BarnesHut") s_algorithmType = CellAlgorithms::CellAlgorithmType::BarnesHut;
        else if (s == "CellList") s_algorithmType = CellAlgorithms::CellAlgorithmType::CellList;
        else if (s == "Naive") s_algorithmType = CellAlgorithms::CellAlgorithmType::Naive;
        else if (s == "Null") s_algorithmType = CellAlgorithms::CellAlgorithmType::Null;
        else if (s == "ParticleMesh") s_algorithmType = CellAlgorithms::CellAlgorithmType::ParticleMesh;
        else if (s == "User") s_algorithmType = CellAlgorithms::CellAlgorithmType::User;
        else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellAlgorithm.Load.Error.algorithmType"));
        
        BarnesHut::Load(config["barnesHut"]);
        CellList::Load(config["cellList"]);
        ParticleMesh::Load(config["particleMesh"]);
        User::Load(config["User"]);
    }
}