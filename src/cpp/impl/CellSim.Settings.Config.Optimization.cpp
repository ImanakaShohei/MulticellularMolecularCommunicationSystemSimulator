#include "CellSim.Settings.Config.Optimization.hpp"

#include "CellSim.Messages.hpp"

#if !CELLSIM_ENV_WINDOWS
    #include "CellSim.Threading.ThreadPool.hpp"
#endif

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

        constexpr int32_t safeMaxThread = 512;

        if (maxDegreeOfParallelism <= 0) s_maxDegreeOfParallelism = static_cast<uint32_t>(maxThread);
        else if (maxDegreeOfParallelism > safeMaxThread) {
            if (maxThread > safeMaxThread) {
                if (maxDegreeOfParallelism < maxThread) s_maxDegreeOfParallelism = static_cast<uint32_t>(maxDegreeOfParallelism);
                else s_maxDegreeOfParallelism = static_cast<uint32_t>(maxThread);
            }
            else s_maxDegreeOfParallelism = static_cast<uint32_t>(safeMaxThread);
        }
        else s_maxDegreeOfParallelism = static_cast<uint32_t>(maxDegreeOfParallelism);

#if !CELLSIM_ENV_WINDOWS
        Threading::ThreadPool::s_pool.SetMaxThreadCount(s_maxDegreeOfParallelism);
#endif
    }
}