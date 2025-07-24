#ifndef CELLSIM_CELLS_CELLTYPE_HPP
#define CELLSIM_CELLS_CELLTYPE_HPP

#include "base.hpp"
#include <string>
#include <string_view>
#include <vector>

namespace CellSim::Cells
{
    /// @brief 細胞の種類
    /// @note このクラスはスレッドセーフではありません
    class CellType final {
        private:

        static ::std::vector<::std::string> s_names;

        uint32_t m_id;

        explicit constexpr CellType(uint32_t id) noexcept;

        public:

        [[nodiscard]] static constexpr CellType Invalid() noexcept;

        /// @brief 種類を追加
        /// @param name 名前
        /// @return その名前に対応するCellType値
        [[nodiscard]] static CellType AddName(const char* name);

        /// @brief 種類を追加
        /// @param name 名前
        /// @return その名前に対応するCellType値
        [[nodiscard]] static CellType AddName(::std::string name);

        /// @brief 種類を追加
        /// @param name 名前
        /// @return その名前に対応するCellType値
        [[nodiscard]] static CellType AddName(::std::string_view name);
        
        CellType() = default;

        /// @brief 
        [[nodiscard]] constexpr uint32_t Id() const noexcept;

        /// @brief 名前
        [[nodiscard]] constexpr ::std::string const& Name() const noexcept;
    };

    [[nodiscard]] constexpr bool operator==(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr bool operator!=(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr bool operator<(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr bool operator<=(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr bool operator>(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr bool operator>=(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr ::std::strong_ordering operator<=>(CellType left, CellType right) noexcept;
}

namespace CellSim::Cells
{
    constexpr CellType::CellType(uint32_t id) noexcept
        : m_id(id)
    {
    }

    constexpr CellType CellType::Invalid() noexcept
    {
        return CellType(0);
    }

    inline CellType CellType::AddName(const char* name)
    {
        return AddName(::std::string_view{ name });
    }

    constexpr uint32_t CellType::Id() const noexcept
    {
        return m_id;
    }

    constexpr ::std::string const& CellType::Name() const noexcept
    {
        return s_names[m_id];
    }

    constexpr bool operator==(CellType left, CellType right) noexcept
    {
        return left.Id() == right.Id();
    }

    constexpr bool operator!=(CellType left, CellType right) noexcept
    {
        return left.Id() != right.Id();
    }

    constexpr bool operator<(CellType left, CellType right) noexcept
    {
        return left.Id() < right.Id();
    }

    constexpr bool operator<=(CellType left, CellType right) noexcept
    {
        return left.Id() <= right.Id();
    }

    constexpr bool operator>(CellType left, CellType right) noexcept
    {
        return left.Id() < right.Id();
    }

    constexpr bool operator>=(CellType left, CellType right) noexcept
    {
        return left.Id() <= right.Id();
    }

    constexpr ::std::strong_ordering operator<=>(CellType left, CellType right) noexcept
    {
        return left.Id() <=> right.Id();
    }
}

#endif //!CELLSIM_CELLS_CELLTYPE_HPP