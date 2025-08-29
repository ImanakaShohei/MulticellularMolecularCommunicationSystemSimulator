#include "CellSim.Cells.CellType.hpp"

namespace CellSim::Cells
{
    ::std::vector<CellType::s_data> CellType::s_names;

    bool CellType::Initialize()
    {
        static bool isLoaded = false;

        if (isLoaded) return false;

        s_names.emplace_back(
            ::std::string("Invalid"),
            Graphics::Color{ 0, 0, 0, 0 },
            nullptr
        );

        isLoaded = true;

        return true;
    }

    CellType CellType::AddName(
        ::std::string name,
        Graphics::Color color,
        Model::CellSimulationModel::Params* params
    )
    {
        // すでに名前が存在すればそのIdを返す
        for (size_t index = 0;index != s_names.size(); ++index) {
            if (s_names[index].Name == name) [[unlikely]] return CellType((uint32_t)index);
        }

        s_names.emplace_back(
            ::std::move(name),
            color,
            params
        );

        return CellType((uint32_t)(s_names.size() - 1));
    }

    CellType CellType::AddName(
        ::std::string_view name,
        Graphics::Color color,
        Model::CellSimulationModel::Params* params
    )
    {
        // すでに名前が存在すればそのIdを返す
        for (size_t index = 0;index != s_names.size(); ++index) {
            if (s_names[index].Name == name) [[unlikely]] return CellType((uint32_t)index);
        }

        s_names.emplace_back(
            ::std::string(name),
            color,
            params
        );

        return CellType((uint32_t)(s_names.size() - 1));
    }

    CellType CellType::FromName(::std::string_view name) noexcept
    {
        // すでに名前が存在すればそのIdを返す
        for (size_t index = 0;index != s_names.size(); ++index) {
            if (s_names[index].Name == name) [[unlikely]] return CellType((uint32_t)index);
        }

        return Invalid();
    }
}