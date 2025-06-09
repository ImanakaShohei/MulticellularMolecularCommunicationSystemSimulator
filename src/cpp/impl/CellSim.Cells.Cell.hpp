#ifndef CELLSIM_CELLS_CELL_HPP
#define CELLSIM_CELLS_CELL_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehaviorPtr.hpp"
#include "CellSim.Cells.CellType.hpp"
#include "CellSim.Molecular.Molecule.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

#include <string>
#include <vector>

namespace CellSim::Cells
{
    /// @brief 細胞クラス
    class Cell final {
        private:

        /// @brief 各細胞に割り振るID
        static uint32_t s_id;

        /// @brief 接着している細胞のリスト
        ::std::vector<const Cell*> m_attachedCells;

        /// @brief ふるまい定義
        CellBehaviorPtr m_behaviorPtr;

        /// @brief 細胞が受けた力
        Numerics::Vector3 m_force;

        /// @brief 識別子
        uint32_t m_id;

        /// @brief 細胞内の分子の種類とその量
        ::std::vector<Molecular::Molecule> m_internalMolecules;

        /// @brief この細胞が生きているかどうか
        bool m_isAlive;

        /// @brief 細胞の質量
        double m_mass;

        /// @brief 極性ベクトル
        Numerics::Vector3 m_polarity;

        /// @brief 細胞の位置
        Numerics::Vector3 m_position;

        /// @brief 1step前に細胞が受けた力
        Numerics::Vector3 m_previusForce;

        /// @brief 細胞の半径
        double m_radius;

        /// @brief 細胞の種類
        CellType m_type;
        
        public:

        Cell(
            CellType type,
            CellBehaviorPtr const& pBehavior,
            double mass,
            double radius,
            Numerics::Vector3 position
        );

        Cell(Cell const&) = delete;
        Cell(Cell&&) = default;

        Cell& operator=(Cell const&) = delete;

        // プロパティ

        /// @brief 接着している細胞のリスト
        [[nodiscard]] constexpr ::std::vector<const Cell*> const& AttachedCells() const noexcept;

        /// @brief 接着している細胞の数
        [[nodiscard]] constexpr size_t AttachedCellCount() const noexcept;

        /// @brief 細胞が受けた力
        [[nodiscard]] constexpr Numerics::Vector3 Force() const noexcept;

        /// @brief 識別子
        [[nodiscard]] constexpr uint32_t Id() const noexcept;

        /// @brief 細胞内の分子の種類とその量
        [[nodiscard]] constexpr ::std::vector<Molecular::Molecule> const& InternalMolecules() const noexcept;

        [[nodiscard]] constexpr bool IsAlive() const noexcept;

        /// @brief 細胞の質量
        [[nodiscard]] constexpr double Mass() const noexcept;

        /// @brief 極性ベクトル
        [[nodiscard]] constexpr Numerics::Vector3 Polarity() const noexcept;

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

        [[nodiscard]] bool ShouldDivideThisStep() const noexcept;

        /// @brief 細胞の種類
        [[nodiscard]] constexpr CellType Type() const noexcept;

        /// @brief 細胞の速度
        [[nodiscard]] constexpr Numerics::Vector3 Velocity() const noexcept;

        // メソッド

        /// @brief 細胞に力を加える
        /// @param force 加える力
        constexpr void ApplyForce(Numerics::Vector3 force) noexcept;

        /// @brief 接着
        /// @param cell 接着する細胞
        void Adhere(Cell const& cell);

        /// @brief すべての細胞の接着を解除
        constexpr void ClearAttachedCells() noexcept;

        /// @brief 結合
        /// @param c 結合する細胞
        /// @note 結合すると引数に与えたcは無効になります
        void Combine(Cell& c) noexcept;

        /// @brief 細胞死
        constexpr void Die() noexcept;

        /// @brief 分裂
        /// @return 分裂したもう1つの細胞
        [[nodiscard]] Cell Divide();

        /// @brief 分子空間に分子を放出
        /// @param field 分子空間
        void EmitMolecule(Molecular::MoleculeField& field);

        /// @brief 分子空間に分子を放出
        /// @param fields 分子空間リスト
        void EmitMolecule(::std::vector<Molecular::MoleculeField>& fields);

        /// @brief 細胞が成長
        void Grow();

        [[nodiscard]] bool IsAdheringTo(Cell const& cell) const noexcept;

        /// @brief 代謝
        void Metabolize();

        /// @brief 細胞が移動
        constexpr void Move() noexcept;

        /// @brief 細胞にかかっている力をゼロにする
        constexpr void ResetForce() noexcept;

        void SenseMolecules(Molecular::MoleculeField const& field);
    };

    [[nodiscard]] constexpr bool operator==(Cell const& left, Cell const& right) noexcept;
    [[nodiscard]] constexpr bool operator!=(Cell const& left, Cell const& right) noexcept;
}

namespace CellSim::Cells
{
    constexpr ::std::vector<const Cell*> const& Cell::AttachedCells() const noexcept
    {
        return m_attachedCells;
    }

    constexpr size_t Cell::AttachedCellCount() const noexcept
    {
        return m_attachedCells.size();
    }

    constexpr Numerics::Vector3 Cell::Force() const noexcept
    {
        return m_force;
    }

    constexpr uint32_t Cell::Id() const noexcept
    {
        return m_id;
    }

    constexpr ::std::vector<Molecular::Molecule> const& Cell::InternalMolecules() const noexcept
    {
        return m_internalMolecules;
    }

    constexpr bool Cell::IsAlive() const noexcept
    {
        return m_isAlive;
    }

    constexpr double Cell::Mass() const noexcept
    {
        return m_mass;
    }

    constexpr Numerics::Vector3 Cell::Polarity() const noexcept
    {
        return m_polarity;
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

    constexpr CellType Cell::Type() const noexcept
    {
        return m_type;
    }

    constexpr Numerics::Vector3 Cell::Velocity() const noexcept
    {
        return m_force / m_mass;
    }

    constexpr void Cell::ApplyForce(Numerics::Vector3 force) noexcept
    {
        m_force += force;
    }

    inline void Cell::Adhere(Cell const& cell)
    {
        m_attachedCells.push_back(&cell);
    }

    constexpr void Cell::ClearAttachedCells() noexcept
    {
        m_attachedCells.clear();
    }

    constexpr void Cell::Die() noexcept
    {
        m_isAlive = false;
    }

    inline void Cell::EmitMolecule(::std::vector<Molecular::MoleculeField>& fields)
    {
        for (Molecular::MoleculeField& field : fields) {
            EmitMolecule(field);
        }
    }

    inline bool Cell::IsAdheringTo(Cell const& cell) const noexcept
    {
        const Cell* pCell = &cell;

        for (const Cell* pAttached : m_attachedCells) {
            if (pAttached == pCell) return true;
        }

        return false;
    }

    constexpr void Cell::Move() noexcept
    {
        m_position += m_force / m_mass;
    }

    constexpr void Cell::ResetForce() noexcept
    {
        m_previusForce = m_force;
        m_force = Numerics::Vector3::Zero();
    }

    constexpr bool operator==(Cell const& left, Cell const& right) noexcept
    {
        return left.Id() == right.Id();
    }

    constexpr bool operator!=(Cell const& left, Cell const& right) noexcept
    {
        return left.Id() != right.Id();
    }
}

#endif //!CELLSIM_CELLS_CELL_HPP