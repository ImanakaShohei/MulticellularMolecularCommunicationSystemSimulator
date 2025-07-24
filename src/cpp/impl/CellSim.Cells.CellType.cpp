#include "CellSim.Cells.CellType.hpp"

namespace CellSim::Cells
{
    ::std::vector<::std::string> CellType::s_names{ "Invalid" };

    CellType CellType::AddName(::std::string name)
    {
        // すでに名前が存在すればそのIdを返す
        for (size_t index = 0;index != s_names.size(); ++index) {
            if (s_names[index] == name) [[unlikely]] return CellType((uint32_t)index);
        }

        s_names.emplace_back(::std::move(name));

        return CellType((uint32_t)s_names.size());
    }

    CellType CellType::AddName(::std::string_view name)
    {
        // すでに名前が存在すればそのIdを返す
        for (size_t index = 0;index != s_names.size(); ++index) {
            if (s_names[index] == name) [[unlikely]] return CellType((uint32_t)index);
        }

        s_names.emplace_back(name);
    }
}