#include "CellSim.Settings.Config.Optimization.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::Optimization::Load(::nlohmann::json const& config)
    {
        ::std::string s;
        try {
            s = config["peformance"].get<::std::string>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.Optimization.Load.Error.JsonError"));
        }

        if (s == "Fast") s_peformance = PeformanceType::Fast;
        else if (s == "LowMemory") s_peformance = PeformanceType::LowMemory;
        else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Optimization.Load.Error.peformance"));
    }
}