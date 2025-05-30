#ifndef CELLSIM_CELLS_CELL_HPP
#define CELLSIM_CELLS_CELL_HPP

#include "base.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Cells
{
    class Cell {
        private:

        /// @brief 細胞が受けた力
        Numerics::Vector3 m_force;

        /// @brief 識別子
        int32_t m_id;

        /// @brief この細胞が生きているかどうか
        bool m_isAlive;

        /// @brief 細胞の質量
        double m_mass;

        /// @brief 細胞の位置
        Numerics::Vector3 m_position;

        /// @brief 1step前に細胞が受けた力
        Numerics::Vector3 m_previusForce;

        /// @brief 細胞の半径
        double m_radius;

        protected:

        public:

        // プロパティ

        /// @brief 細胞が受けた力
        [[nodiscard]] constexpr Numerics::Vector3 Force() const noexcept;

        /// @brief 識別子
        [[nodiscard]] constexpr int32_t Id() const noexcept;

        [[nodiscard]] constexpr bool IsAlive() const noexcept;

        /// @brief 細胞の質量
        [[nodiscard]] constexpr double Mass() const noexcept;

        /// @brief 細胞の位置
        [[nodiscard]] constexpr Numerics::Vector3 Position() const noexcept;

        /// @brief 細胞のX座標
        [[nodiscard]] constexpr double PositionX() const noexcept;

        /// @brief 細胞のY座標
        [[nodiscard]] constexpr double PositionY() const noexcept;

        /// @brief 細胞のZ座標
        [[nodiscard]] constexpr double PositionZ() const noexcept;

        /// @brief 1step前に細胞が受けた力
        [[nodiscard]] constexpr Numerics::Vector3 PreviusForce() const noexcept;

        /// @brief 1step前の細胞の速度
        [[nodiscard]] constexpr Numerics::Vector3 PreviusVelocity() const noexcept;

        /// @brief 細胞の半径
        [[nodiscard]] constexpr double Radius() const noexcept;

        /// @brief 細胞の種類
        [[nodiscard]] CellType Type() const noexcept;

        /// @brief 細胞の速度
        [[nodiscard]] constexpr Numerics::Vector3 Velocity() const noexcept;

        // メソッド

        void Combine(Cell& c);

        void Move() noexcept;
    };
}

namespace CellSim::Cells
{
    constexpr Numerics::Vector3 Cell::Force() const noexcept
    {
        return m_force;
    }

    constexpr int32_t Cell::Id() const noexcept
    {
        return m_id;
    }

    constexpr bool Cell::IsAlive() const noexcept
    {
        return m_isAlive;
    }

    constexpr double Cell::Mass() const noexcept
    {
        return m_mass;
    }

    constexpr Numerics::Vector3 Cell::Position() const noexcept
    {
        return m_position;
    }

    constexpr double Cell::PositionX() const noexcept
    {
        return m_position.X;
    }

    constexpr double Cell::PositionY() const noexcept
    {
        return m_position.Y;
    }

    constexpr double Cell::PositionZ() const noexcept
    {
        return m_position.Z;
    }

    constexpr Numerics::Vector3 Cell::PreviusForce() const noexcept
    {
        return m_previusForce;
    }

    constexpr Numerics::Vector3 Cell::PreviusVelocity() const noexcept
    {
        return m_previusForce / m_mass;
    }

    constexpr double Cell::Radius() const noexcept
    {
        return m_radius;
    }

    constexpr Numerics::Vector3 Cell::Velocity() const noexcept
    {
        return m_force / m_mass;
    }
}

#endif //!CELLSIM_CELLS_CELL_HPP