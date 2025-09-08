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

        // <名前, 動画出力時の閾値>
        static ::std::vector<::std::pair<::std::string, double>> s_names;

        uint32_t m_id;

        explicit constexpr MoleculeKind(uint32_t id) noexcept;

        public:

        [[nodiscard]] static constexpr MoleculeKind Invalid() noexcept;

        [[nodiscard]] static MoleculeKind AddName(const char* name, double threshold);
        [[nodiscard]] static MoleculeKind AddName(::std::string_view name, double threshold);
        [[nodiscard]] static MoleculeKind AddName(::std::string name, double threshold);

        [[nodiscard]] static MoleculeKind FromName(::std::string_view name) noexcept;

        /// @brief Invalid以外の種類を削除
        static void ResetUnsafe() noexcept;

        MoleculeKind() = default;

        [[nodiscard]] constexpr uint32_t Id() const noexcept;

        [[nodiscard]] constexpr ::std::string const& Name() const noexcept;

        [[nodiscard]] constexpr double Threshold() const noexcept;
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
    constexpr MoleculeKind::MoleculeKind(uint32_t id) noexcept
        : m_id(id)
    {
    }

    constexpr MoleculeKind MoleculeKind::Invalid() noexcept
    {
        return MoleculeKind(0);
    }

    inline MoleculeKind MoleculeKind::AddName(const char* name, double threshold)
    {
        return AddName(::std::string_view{ name }, threshold);
    }

    constexpr uint32_t MoleculeKind::Id() const noexcept
    {
        return m_id;
    }

    constexpr ::std::string const& MoleculeKind::Name() const noexcept
    {
        return s_names[m_id].first;
    }

    constexpr double MoleculeKind::Threshold() const noexcept
    {
        return s_names[m_id].second;
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