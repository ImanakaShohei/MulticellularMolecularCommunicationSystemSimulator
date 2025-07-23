#include "CellSim.Settings.Config.CellBehavior.WavePropagation.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    void Config::CellBehavior::WavePropagation::Load(::nlohmann::json const& config)
    {
        if (config.is_null()) return;

        try {
            s_cellDivisionRadius = config.at("cellDivisionRadius").get<double>();
            s_degradationRate = config.at("degradationRate").get<double>();
            s_synthesisRate = config.at("synthesisRate").get<double>();
            s_c = config.at("c").get<double>();
            s_k_1 = config.at("k1").get<double>();
            s_k_2 = config.at("k2").get<double>();
            s_l_1 = config.at("l1").get<double>();
            s_l_2 = config.at("l2").get<double>();
            s_q = config.at("q").get<double>();
            s_sigma = config.at("sigma").get<double>();
            s_k_i = config.at("ki").get<double>();
            s_k_e = config.at("ke").get<double>();
            s_k_t = config.at("kt").get<double>();
            s_alpha = config.at("alpha").get<double>();
            s_h = config.at("h").get<double>();
            s_theta = config.at("theta").get<double>();
            s_lambda = config.at("lambda").get<double>();
            s_epsilon = config.at("epsilon").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.WavePropagation.Load.Error.JsonError"));
        }

        if (s_cellDivisionRadius <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.WavePropagation.Load.Error.cellDivisionRadius"));
        if (s_degradationRate <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.WavePropagation.Load.Error.degradationRate"));
        if (s_synthesisRate <= 0.0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Settings.Config.CellBehavior.WavePropagation.Load.Error.synthesisRate"));
    }
}