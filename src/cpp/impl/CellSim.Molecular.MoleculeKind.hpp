#ifndef CELLSIM_MOLECULAR_MOLECULEKIND_HPP
#define CELLSIM_MOLECULAR_MOLECULEKIND_HPP

#include "base.hpp"

#include <string>
#include <string_view>
#include <vector>

namespace CellSim::Molecular
{
    /// @brief 分子の種類
    /// @note このクラスはスレッドセーフではありません
    class MoleculeKind {
        private:

        static ::std::vector<::std::string> s_names;

        uint32_t m_id;

        explicit constexpr MoleculeKind(uint32_t id) noexcept;

        public:

        [[nodiscard]] static constexpr MoleculeKind Invalid() noexcept;

        [[nodiscard]] static MoleculeKind AddName(const char* name);
        [[nodiscard]] static MoleculeKind AddName(::std::string_view name);
        [[nodiscard]] static MoleculeKind AddName(::std::string name);

        [[nodiscard]] static MoleculeKind FromName(::std::string_view name) noexcept;

        [[nodiscard]] constexpr uint32_t Id() const noexcept;

        [[nodiscard]] ::std::string const& Name() const noexcept;
    };

    [[nodiscard]] constexpr bool operator==(MoleculeKind left, MoleculeKind right) noexcept;
    [[nodiscard]] constexpr bool operator!=(MoleculeKind left, MoleculeKind right) noexcept;
    [[nodiscard]] constexpr bool operator<(MoleculeKind left, MoleculeKind right) noexcept;
    [[nodiscard]] constexpr bool operator<=(MoleculeKind left, MoleculeKind right) noexcept;
    [[nodiscard]] constexpr bool operator>(MoleculeKind left, MoleculeKind right) noexcept;
    [[nodiscard]] constexpr bool operator>=(MoleculeKind left, MoleculeKind right) noexcept;
    [[nodiscard]] constexpr ::std::strong_ordering operator<=>(MoleculeKind left, MoleculeKind right) noexcept;
}

namespace CellSim::Molecular
{
    MoleculeKind MoleculeKind::AddName(const char* name)
    {
        return AddName(::std::string_view{ name });
    }

    constexpr uint32_t MoleculeKind::Id() const noexcept
    {
        return m_id;
    }

    inline ::std::string const& MoleculeKind::Name() const noexcept
    {
        return s_names[m_id];
    }

    constexpr bool operator==(MoleculeKind left, MoleculeKind right) noexcept
    {
        return left.Id() == right.Id();
    }

    constexpr bool operator!=(MoleculeKind left, MoleculeKind right) noexcept
    {
        return left.Id() != right.Id();
    }

    constexpr bool operator<(MoleculeKind left, MoleculeKind right) noexcept
    {
        return left.Id() < right.Id();
    }

    constexpr bool operator<=(MoleculeKind left, MoleculeKind right) noexcept
    {
        return left.Id() <= right.Id();
    }

    constexpr bool operator>(MoleculeKind left, MoleculeKind right) noexcept
    {
        return left.Id() > right.Id();
    }

    constexpr bool operator>=(MoleculeKind left, MoleculeKind right) noexcept
    {
        return left.Id() >= right.Id();
    }

    constexpr ::std::strong_ordering operator<=>(MoleculeKind left, MoleculeKind right) noexcept
    {
        return left.Id() <=> right.Id();
    }
}

#endif //!CELLSIM_MOLECULAR_MOLECULEKIND_HPP