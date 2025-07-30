#include "CellSim.Settings.Config.Optimization.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <thread>

namespace CellSim::Settings
{
    void Config::Optimization::Load(::nlohmann::json& config)
    {
        if (config.is_null()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Optimization.Load.Error.JsonError"));

        int32_t maxDegreeOfParallelism;
        ::std::string s;
        try {
            s = config.at("peformance").get<::std::string>();
            maxDegreeOfParallelism = config.at("maxDegreeOfParallelism").get<int32_t>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.Optimization.Load.Error.JsonError"));
        }

        if (s == "Fast") s_peformance = PeformanceType::Fast;
        else if (s == "LowMemory") s_peformance = PeformanceType::LowMemory;
        else [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.Optimization.Load.Error.peformance"));

        auto maxThread = (int32_t)::std::thread::hardware_concurrency();

        if (maxDegreeOfParallelism <= 0 || maxThread < maxDegreeOfParallelism) s_maxDegreeOfParallelism = (uint32_t)maxThread;
        else s_maxDegreeOfParallelism = (uint32_t)maxDegreeOfParallelism;
    }
}