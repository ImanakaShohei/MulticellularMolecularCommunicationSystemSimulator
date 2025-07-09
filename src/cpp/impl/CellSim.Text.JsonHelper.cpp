#include "CellSim.Text.JsonHelper.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std;

namespace CellSim::Text
{
    nlohmann::json* JsonHelper::GetParam(json& j, string_view paramName) noexcept
    {
        size_t index = paramName.find('.');

        try {
            if (index == string_view::npos) return &(j.at(paramName));
        }
        catch (...) {
            return nullptr;
        }
        
        string_view param1 = paramName.substr(0, index);
        
        json* pj;

        try {
            pj = &(j.at(param1));
        }
        catch (...) {
            return nullptr;
        }

        string_view newParamName = paramName.substr(index + 1);

        return GetParam(*pj, newParamName);
    }
}