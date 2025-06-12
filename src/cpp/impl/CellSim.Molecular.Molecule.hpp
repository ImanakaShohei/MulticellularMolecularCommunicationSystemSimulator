#ifndef CELLSIM_MOLECULAR_MOLECULE_HPP
#define CELLSIM_MOLECULAR_MOLECULE_HPP

#include "base.hpp"
#include "CellSim.Molecular.MoleculeKind.hpp"

namespace CellSim::Molecular
{
    /// @brief 分子クラス
    class Molecule {
        private:

        /// @brief 分子の量
        double m_amount;

        /// @brief 分子の種類
        MoleculeKind m_kind;
        
        public:

        constexpr Molecule(MoleculeKind kind) noexcept;
        constexpr Molecule(MoleculeKind kind, double amount) noexcept;

        /// @brief 分子の量
        [[nodiscard]] constexpr double Amount() const noexcept;

        /// @brief 分子の量を設定
        /// @param amount 量
        /// @exception ::std::invalid_argument amountが負の値の時
        void Amount(double amount);

        /// @brief 分子の種類
        [[nodiscard]] constexpr MoleculeKind Kind() const noexcept;

        /// @brief 分子の量を設定
        /// @param amount 量
        constexpr void SetAmountUnsafe(double amount) noexcept;
    };

    [[nodiscard]] constexpr bool operator==(Molecule const& left, Molecule const& right) noexcept;
    [[nodiscard]] constexpr bool operator!=(Molecule const& left, Molecule const& right) noexcept;
}

namespace CellSim::Molecular
{
    constexpr Molecule::Molecule(MoleculeKind kind) noexcept
        : m_kind(kind)
        , m_amount(0)
    {
    }

    constexpr Molecule::Molecule(MoleculeKind kind, double amount) noexcept
        : m_kind(kind)
        , m_amount(amount)
    {
    }

    constexpr MoleculeKind Molecule::Kind() const noexcept
    {
        return m_kind;
    }

    constexpr void Molecule::SetAmountUnsafe(double amount) noexcept
    {
        m_amount = amount;
    }

    constexpr bool operator==(Molecule const& left, Molecule const& right) noexcept
    {
        return left.Kind() == right.Kind() && left.Amount() == right.Amount();
    }

    constexpr bool operator!=(Molecule const& left, Molecule const& right) noexcept
    {
        return !(left == right);
    }
}

#endif //!CELLSIM_MOLECULAR_MOLECULE_HPP