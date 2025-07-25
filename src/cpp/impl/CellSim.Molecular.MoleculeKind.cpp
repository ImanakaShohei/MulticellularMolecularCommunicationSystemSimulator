#include "CellSim.Molecular.MoleculeKind.hpp"

namespace CellSim::Molecular
{
    ::std::vector<::std::string> MoleculeKind::s_names{ "Invalid" };

    MoleculeKind MoleculeKind::AddName(::std::string_view name)
    {
        for (size_t i = 0; i < s_names.size(); i++) {
            if (s_names[i] == name) [[unlikely]] return MoleculeKind((uint32_t)i);
        }

        s_names.emplace_back(::std::move(name));

        return MoleculeKind((uint32_t)s_names.size());
    }

    MoleculeKind MoleculeKind::AddName(::std::string name)
    {
        for (size_t i = 0; i < s_names.size(); i++) {
            if (s_names[i] == name) [[unlikely]] return MoleculeKind((uint32_t)i);
        }

        s_names.emplace_back(::std::move(name));

        return MoleculeKind((uint32_t)s_names.size());
    }

    MoleculeKind MoleculeKind::FromName(::std::string_view name) noexcept
    {
        for (size_t i = 0; i < s_names.size(); i++) {
            if (s_names[i] == name) return MoleculeKind((uint32_t)i);
        }

        return Invalid();
    }
}