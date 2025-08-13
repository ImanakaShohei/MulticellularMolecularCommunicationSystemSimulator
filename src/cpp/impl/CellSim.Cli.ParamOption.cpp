#include "CellSim.Cli.ParamOption.hpp"
#include "CellSim.Messages.hpp"
#include "CellSim.Numerics.Numbers.hpp"
#include "CellSim.Text.JsonHelper.hpp"

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
            
            if (!Numerics::Numbers::ToNumber<T>(value, tValue)) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cli.ParamOption.OverrideParameter.Error.InvalidValue"));

            v = tValue;
        }
    }

    void ParamOption::OverrideParameter(nlohmann::json& config, ::std::string_view param)
    {
        size_t index = param.find('=');

        if (index == ::std::string_view::npos || index == 0) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cli.ParamOption.OverrideParameter.Error.FormatError"));

        ::std::string_view paramName = param.substr(0, index);
        ::std::string_view value = param.substr(index + 1);

        nlohmann::json* pj = Text::JsonHelper::GetParam(config, paramName);

        if (pj == nullptr) [[unlikely]] throw ::std::runtime_error(Messages::Get("Cli.ParamOption.OverrideParameter.Error.NotFound"));
        nlohmann::json& j = *pj;

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

    void ParamOption::OverrideParameter(nlohmann::json& config) const
    {
        for (::std::string const& param : m_values) {
            OverrideParameter(config, param);
        }
    }
}