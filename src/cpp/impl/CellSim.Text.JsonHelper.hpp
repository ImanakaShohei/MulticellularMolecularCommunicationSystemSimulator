#ifndef CELLSIM_TEXT_JSONHELPER_HPP
#define CELLSIM_TEXT_JSONHELPER_HPP

#include "base.hpp"
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <string_view>

namespace CellSim::Text
{
    class JsonHelper final {

        public:

        [[nodiscard]] static nlohmann::json* GetParam(
            nlohmann::json& j,
            ::std::string_view paramName
        ) noexcept;
    };
}

#endif //!CELLSIM_TEXT_JSONHELPER_HPP