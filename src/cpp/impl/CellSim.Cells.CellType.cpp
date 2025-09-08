#include "CellSim.Cells.CellType.hpp"

namespace CellSim::Cells
{
    ::std::vector<::std::pair<::std::string, Graphics::Color>> CellType::s_names{ {"Invalid", { 0, 0, 0, 0 }} };

    CellType CellType::AddName(::std::string name, Graphics::Color color)
    {
        // すでに名前が存在すればそのIdを返す
        for (size_t index = 0;index != s_names.size(); ++index) {
            if (s_names[index].first == name) [[unlikely]] return CellType((uint32_t)index);
        }

        s_names.emplace_back(::std::move(name), color);

        return CellType((uint32_t)(s_names.size() - 1));
    }

    CellType CellType::AddName(::std::string_view name, Graphics::Color color)
    {
        // すでに名前が存在すればそのIdを返す
        for (size_t index = 0;index != s_names.size(); ++index) {
            if (s_names[index].first == name) [[unlikely]] return CellType((uint32_t)index);
        }

        s_names.emplace_back(name, color);

        return CellType((uint32_t)(s_names.size() - 1));
    }

    CellType CellType::FromName(::std::string_view name) noexcept
    {
        // すでに名前が存在すればそのIdを返す
        for (size_t index = 0;index != s_names.size(); ++index) {
            if (s_names[index].first == name) [[unlikely]] return CellType((uint32_t)index);
        }

        return Invalid();
    }

    void CellType::ResetUnsafe() noexcept
    {
        s_names.erase(
            s_names.begin() + 1,
            s_names.end()
        );
    }
}