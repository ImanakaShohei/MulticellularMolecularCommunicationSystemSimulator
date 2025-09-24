#include "CellSim.Settings.Config.Molecular.Behavior.hpp"
#include "CellSim.Settings.Config.Molecular.Behavior.Normal.hpp"
#include "CellSim.Molecular.NormalMoleculeBehavior.hpp"

#include "CellSim.Messages.hpp"

#include <stdexcept>

#include <nlohmann/json.hpp>

namespace CellSim::Settings
{
    ::CellSim::Molecular::NormalMoleculeBehavior*
    Config::Molecular::Behavior::Normal::FromJson(
        ::nlohmann::json const& config
    )
    {
        if (config.is_null()) [[unlikely]] {
            throw ::std::runtime_error(
                Messages::Get("Settings.Config.Molecular.Behavior.Normal.FromJson.Error.JsonError")
            );
        }

        double diffusionFactor;
        try {
            diffusionFactor = config.at("diffusionFactor").get<double>();
        }
        catch (...) {
            throw ::std::runtime_error(
                Messages::Get("Settings.Config.Molecular.Behavior.Normal.FromJson.Error.JsonError")
            );
        }

        try {
            return new ::CellSim::Molecular::NormalMoleculeBehavior(diffusionFactor);
        }
        catch (::std::invalid_argument) {
            throw ::std::runtime_error(
                Messages::Get("Settings.Config.Molecular.Behavior.Normal.FromJson.Error.diffusionFactor")
            );
        }
        
    }
}