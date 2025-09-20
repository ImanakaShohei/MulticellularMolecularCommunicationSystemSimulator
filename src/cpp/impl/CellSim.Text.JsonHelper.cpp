#include "CellSim.Text.JsonHelper.hpp"
#include "CellSim.Numerics.Numbers.hpp"

#include <stdexcept>
#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std;

namespace CellSim::Text
{
    nlohmann::json* JsonHelper::GetParam(
        json& j,
        string_view paramName
    ) noexcept
    {
        size_t index = paramName.find('.');

        if (index == string_view::npos) {
            try {
                if (j.is_array()) {
                    size_t arrIndex;

                    if (!Numerics::Numbers::ToNumber(paramName, arrIndex)) return nullptr;

                    return &(j.at(arrIndex));
                }

                return &(j.at(paramName));
            }
            catch (...) {
                return nullptr;
            }
        }
        
        string_view param1 = paramName.substr(0, index);
        
        json* pj;

        try {
            if (j.is_array()) {

                size_t arrIndex;

                if (!Numerics::Numbers::ToNumber(param1, arrIndex)) return nullptr;
                
                pj = &(j.at(arrIndex));
            }
            else {
                pj = &(j.at(param1));
            }
        }
        catch (...) {
            return nullptr;
        }

        string_view newParamName = paramName.substr(index + 1);

        return GetParam(*pj, newParamName);
    }
}