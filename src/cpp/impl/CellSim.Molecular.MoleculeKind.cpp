#include "CellSim.Molecular.MoleculeKind.hpp"

#include <stdexcept>

namespace CellSim::Molecular
{
    ::std::vector<::std::pair<::std::string, double>> MoleculeKind::s_names{ { "Invalid", 0 } };

    MoleculeKind MoleculeKind::AddName(::std::string_view name, double threshold)
    {
        for (size_t i = 0; i < s_names.size(); i++) {
            if (s_names[i].first == name) [[unlikely]] throw ::std::invalid_argument("AddNameに既に存在する名前が指定されました");
        }

        s_names.emplace_back(::std::move(name), threshold);

        return MoleculeKind((uint32_t)(s_names.size() - 1));
    }

    MoleculeKind MoleculeKind::AddName(::std::string name, double threshold)
    {
        for (size_t i = 0; i < s_names.size(); i++) {
            if (s_names[i].first == name) [[unlikely]] throw ::std::invalid_argument("AddNameに既に存在する名前が指定されました");
        }

        s_names.emplace_back(::std::move(name), threshold);

        return MoleculeKind((uint32_t)(s_names.size() - 1));
    }

    MoleculeKind MoleculeKind::FromName(::std::string_view name) noexcept
    {
        for (size_t i = 0; i < s_names.size(); i++) {
            if (s_names[i].first == name) return MoleculeKind((uint32_t)i);
        }

        return Invalid();
    }

    void MoleculeKind::ResetUnsafe() noexcept
    {
        s_names.erase(
            s_names.begin() + 1,
            s_names.end()
        );
    }
}