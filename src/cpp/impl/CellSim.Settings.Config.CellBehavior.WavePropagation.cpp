#include "CellSim.Settings.Config.CellBehavior.WavePropagation.hpp"
#include "CellSim.Cells.CellBehaviorPtr.hpp"
#include "CellSim.Cells.WavePropagationCellBehavior.hpp"

#include "CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Settings
{
    Cells::CellBehaviorPtr Config::CellBehavior::WavePropagation::FromJson(
        ::nlohmann::json const& config
    )
    {
        if (config.is_null()) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.WavePropagation.FromJson.Error.JsonError"
                )
            );
        }

        double cellDivisionRadius;
        double degradationRate;
        double growthRate;
        double synthesisRate;

        double c;
        double k_1;
        double k_2;
        double l_1;
        double l_2;
        double q;
        double sigma;
        double k_i;
        double k_e;
        double k_t;
        double alpha;
        double h;
        double theta;
        double lambda;
        double epsilon;

        try {
            cellDivisionRadius = config.at("cellDivisionRadius").get<double>();
            degradationRate = config.at("degradationRate").get<double>();
            growthRate = config.at("growthRate").get<double>();
            synthesisRate = config.at("synthesisRate").get<double>();
            c = config.at("c").get<double>();
            k_1 = config.at("k1").get<double>();
            k_2 = config.at("k2").get<double>();
            l_1 = config.at("l1").get<double>();
            l_2 = config.at("l2").get<double>();
            q = config.at("q").get<double>();
            sigma = config.at("sigma").get<double>();
            k_i = config.at("ki").get<double>();
            k_e = config.at("ke").get<double>();
            k_t = config.at("kt").get<double>();
            alpha = config.at("alpha").get<double>();
            h = config.at("h").get<double>();
            theta = config.at("theta").get<double>();
            lambda = config.at("lambda").get<double>();
            epsilon = config.at("epsilon").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.WavePropagation.Load.Error.JsonError"
                )
            );
        }

        if (cellDivisionRadius <= 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.WavePropagation.Load.Error.cellDivisionRadius"
                )
            );
        }
        if (degradationRate <= 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.WavePropagation.Load.Error.degradationRate"
                )
            );
        }
        if (synthesisRate <= 0.0) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get(
                    "Settings.Config.CellBehavior.WavePropagation.Load.Error.synthesisRate"
                )
            );
        }

        return Cells::CellBehaviorPtr::FromPointerUnsafe(
            new Cells::WavePropagationCellBehavior(
                cellDivisionRadius,
                growthRate,
                synthesisRate,
                degradationRate,
                c,
                k_1,
                k_2,
                l_1,
                l_2,
                q,
                sigma,
                k_i,
                k_e,
                k_t,
                alpha,
                h,
                theta,
                lambda,
                epsilon
            )
        );
    }
}