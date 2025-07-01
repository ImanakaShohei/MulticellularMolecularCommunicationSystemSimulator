#include "CellSim.Cli.ParamOption.hpp"
#include "CellSim.Cli.CliOptionActivationArgs.hpp"
#include "CellSim.Messages.hpp"

#include <sstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

namespace CellSim::Cli
{
    template <class T>
    void ParamOption::s_changeValue(nlohmann::json& v, ::std::string_view value)
    {
        if constexpr (::std::same_as<T, ::std::string>) {
            v = value;
        }
        else if constexpr (::std::same_as<T, bool>) {
            if (value == "true") v = true;
            else if (value == "false") v = false;
            else [[unlikely]] throw ::std::runtime_error(Messages::Get("Cli.ParamOption.OverrideParameter.Error.InvalidValue"));
        }
        else {
            T tValue;
            ::std::istringstream sin(::std::string(value.data(), value.size()) + ' ');

            sin >> tValue;

            v = tValue;

            if (!sin || sin.tellg() != value.size()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cli.ParamOption.OverrideParameter.Error.InvalidValue"));
        }
    }

    void ParamOption::OverrideParameter(nlohmann::json& config, ::std::string_view param)
    {
        size_t index = param.find('.');

        if (index != ::std::string_view::npos) {
            ::std::string_view param1 = param.substr(0, index);
            ::std::string_view param2 = param.substr(index + 1);

            ::nlohmann::json& j = config[param1];

            if (j.is_null()) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cli.ParamOption.OverrideParameter.Error.NotFound"));

            OverrideParameter(j, param2);
            return;
        }

        index = param.find('=');

        if (index == ::std::string_view::npos || index == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cli.ParamOption.OverrideParameter.Error.FormatError"));

        ::std::string_view paramName = param.substr(0, index);
        ::std::string_view value = param.substr(index + 1);

        nlohmann::json& j = config[paramName];

        switch (j.type()) {
            case nlohmann::detail::value_t::number_float:
            case nlohmann::detail::value_t::number_integer:
            case nlohmann::detail::value_t::number_unsigned: s_changeValue<double>(j, value); break;
            case nlohmann::detail::value_t::boolean: s_changeValue<bool>(j, value); break;
            case nlohmann::detail::value_t::string: s_changeValue<::std::string>(j, value); break;
            case nlohmann::detail::value_t::null: [[unlikely]] throw ::std::runtime_error(Messages::Get("Cli.ParamOption.OverrideParameter.Error.NotFound"));

            default: [[unlikely]] throw ::std::runtime_error(Messages::Get("Cli.ParamOption.OverrideParameter.Error.InvalidParam"));
        }
    }

    void ParamOption::OnActive(const CliOptions* sender, CliOptionActivationArgs args)
    {
    }

    void ParamOption::OverrideParameter(nlohmann::json& config) const
    {
        for (::std::string const& param : m_values) {
            OverrideParameter(config, param);
        }
    }
}