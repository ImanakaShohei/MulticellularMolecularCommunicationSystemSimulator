#include "CellSim.Cli.ParamSweepOption.hpp"
#include "CellSim.Cli.ParamOption.hpp"
#include "CellSim.Cli.CliOptionActivationArgs.hpp"
#include "CellSim.IO.DirectoryCreater.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Simulation.hpp"
#include "CellSim.SimulationOption.hpp"
#include "CellSim.Settings.Config.hpp"
#include <nlohmann/json.hpp>

#include <sstream>
#include <stdexcept>

namespace CellSim::Cli
{
    ::nlohmann::json& ParamSweepOption::s_checkValue(::nlohmann::json& config, ::std::string_view param)
    {
        size_t index = param.find('.');
        if (index != ::std::string_view::npos) {
            ::std::string_view paramName = param.substr(0, index);

            ::nlohmann::json& j = config[paramName];

            if (j.is_null()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cli.ParamSweepOption.CheckValue.Error.NotFound"));

            return s_checkValue(config[paramName], param.substr(index + 1));
        }

        ::nlohmann::json& j = config[param];

        if (!j.is_null() && !j.is_number()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cli.ParamSweepOption.CheckValue.Error.NotNumber"));

        return j;
    }

    template <Numerics::NumberType TNum>
    void ParamSweepOption::s_sweep(::std::string_view first, ::std::string_view second, ::std::string_view third, ::std::string const& paramName, nlohmann::json& config, CliOptionActivationArgs args)
    {
        TNum begin;
        TNum end;
        TNum delta;

        ::std::string buffer;

        buffer.append(first);
        buffer.push_back(' ');
        buffer.append(second);
        buffer.push_back(' ');
        buffer.append(third);
        buffer.push_back(' ');

        ::std::istringstream sin(::std::move(buffer));

        sin >> begin >> end >> delta;

        if (!sin) [[unlikely]] throw ::std::runtime_error("Cli.ParamSweepOption.OnActive.Error");

        for (TNum current = begin; current <= end; current += delta) {

            ::nlohmann::json& j = s_checkValue(config, paramName);

            j = current;

            Settings::Config::Load(config);

            ::std::ostringstream sout;
            sout << args.Options->at(CliOptionType::Output)->Value() << paramName << '=' << current;

            ::std::string path = sout.str();

            IO::DirectoryCreater::Create(path);

            SimulationOption option{
                args.Options->at(CliOptionType::Binary)->IsEnabled(),
                args.Options->at(CliOptionType::Csv)->IsEnabled(),
                args.Options->at(CliOptionType::Image)->IsEnabled(),
                args.Options->at(CliOptionType::Video)->IsEnabled(),
                ::std::move(path)
            };

            Simulation simulation{ ::std::move(option) };

            simulation.Run();
        }
    }

    void ParamSweepOption::OnActive(const CliOptions* sender, CliOptionActivationArgs args)
    {
        ::std::string_view paramView = m_value;

        size_t index = paramView.find('=');

        if (index == ::std::string_view::npos) [[unlikely]] throw ::std::runtime_error("Cli.ParamSweepOption.OnActive.Error");

        paramView = paramView.substr(index + 1);
        ::std::string paramName = m_value.substr(0, index);

        index = paramView.find(':');

        if (index == ::std::string_view::npos) [[unlikely]] throw ::std::runtime_error("Cli.ParamSweepOption.OnActive.Error");

        ::std::string_view first = paramView.substr(0, index);

        paramView = paramView.substr(index + 1);

        index = paramView.find(':');

        if (index == ::std::string_view::npos) [[unlikely]] throw ::std::runtime_error("Cli.ParamSweepOption.OnActive.Error");

        ::std::string_view second = paramView.substr(0, index);

        ::std::string_view third = paramView.substr(index + 1);

        bool isFloatingPoint = false;

        if (first.find('.') != ::std::string_view::npos) isFloatingPoint = true;
        if (second.find('.') != ::std::string_view::npos) isFloatingPoint = true;
        if (third.find('.') != ::std::string_view::npos) isFloatingPoint = true;

        ::nlohmann::json config = Settings::Config::OpenJsonFile(args.Options->at(CliOptionType::Setting)->Value());

        auto pParamOption = static_cast<ParamOption*>(args.Options->at(CliOptionType::Param));

        if (pParamOption->IsEnabled()) {
            pParamOption->OverrideParameter(config);
        }

        if (isFloatingPoint) s_sweep<double>(first, second, third, paramName, config, args);
        else s_sweep<int64_t>(first, second, third, paramName, config, args);
    }
}