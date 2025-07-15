#ifndef CELLSIM_MOLECULAR_MOLECULEFILED_HPP
#define CELLSIM_MOLECULAR_MOLECULEFILED_HPP

#include "base.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Containers.Span3.hpp"
#include "CellSim.Molecular.MoleculeKind.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

#include <vector>
#include <nlohmann/json_fwd.hpp>

namespace CellSim::Molecular
{
    /// @brief 分子空間
    class MoleculeField final {
        private:

        ::CellSim::Molecular::BoundaryCondition m_boundaryCondition;

        /// @brief 
        Containers::Span3<double> m_concentrations;

        double* m_pConcentration;

        bool m_enable2dMode;

        size_t m_gridCountX;
        size_t m_gridCountY;
        size_t m_gridCountZ;

        double m_gridLengthX;
        double m_gridLengthY;
        double m_gridLengthZ;

        /// @brief 分子の種類
        MoleculeKind m_kind;

        /// @brief ふるまい定義
        MoleculeBehavior* m_pBehavior;

        double m_reverseGridLengthX;
        double m_reverseGridLengthY;
        double m_reverseGridLengthZ;

        public:

        [[nodiscard]] static MoleculeField FromJson(::nlohmann::json const& j);

        MoleculeField(
            size_t gridCount,
            bool enable2DMode,
            MoleculeKind kind,
            ::CellSim::Molecular::BoundaryCondition boundaryCondition,
            InitialMoleculeDistribution distributionType,
            double moleculeAmount,
            MoleculeBehavior* pBehavior,
            uint32_t seed = 0
        );

        MoleculeField(MoleculeField const&) = delete;

        ~MoleculeField();

        MoleculeField& operator=(MoleculeField const&) = delete;

        void BeforeAdvanceStep(::std::vector<Cells::Cell> const& cells);

        [[nodiscard]] constexpr ::CellSim::Molecular::BoundaryCondition BoundaryCondition() const noexcept;

        [[nodiscard]] constexpr Containers::Span3<double> Concentrations() noexcept;
        [[nodiscard]] constexpr Containers::ReadOnlySpan3<double> Concentrations() const noexcept;

        /// @brief 分子を拡散させる
        void Diffuse();

        [[nodiscard]] constexpr size_t GridCountX() const noexcept;
        [[nodiscard]] constexpr size_t GridCountY() const noexcept;
        [[nodiscard]] constexpr size_t GridCountZ() const noexcept;

        [[nodiscard]] constexpr double GridLengthX() const noexcept;
        [[nodiscard]] constexpr double GridLengthY() const noexcept;
        [[nodiscard]] constexpr double GridLengthZ() const noexcept;

        void OnAdvanceStep(::std::vector<Cells::Cell> const& cells);

        [[nodiscard]] Numerics::GridPosition3 ToGridPosition3(Cells::Cell const& cell) const noexcept;
        [[nodiscard]] Numerics::GridPosition3 ToGridPosition3(Numerics::Vector3 position) const noexcept;
    };
}

namespace CellSim::Molecular
{
    constexpr ::CellSim::Molecular::BoundaryCondition MoleculeField::BoundaryCondition() const noexcept
    {
        return m_boundaryCondition;
    }

    constexpr Containers::Span3<double> MoleculeField::Concentrations() noexcept
    {
        return m_concentrations;
    }

    constexpr Containers::ReadOnlySpan3<double> MoleculeField::Concentrations() const noexcept
    {
        return Containers::ReadOnlySpan3<double>(m_gridCountX, m_gridCountY, m_gridCountZ, m_pConcentration);
    }

    constexpr size_t MoleculeField::GridCountX() const noexcept
    {
        return m_gridCountX;
    }

    constexpr size_t MoleculeField::GridCountY() const noexcept
    {
        return m_gridCountY;
    }

    constexpr size_t MoleculeField::GridCountZ() const noexcept
    {
        return m_gridCountZ;
    }

    constexpr double MoleculeField::GridLengthX() const noexcept
    {
        return m_gridLengthX;
    }

    constexpr double MoleculeField::GridLengthY() const noexcept
    {
        return m_gridLengthY;
    }

    constexpr double MoleculeField::GridLengthZ() const noexcept
    {
        return m_gridLengthZ;
    }

    inline Numerics::GridPosition3 MoleculeField::ToGridPosition3(Cells::Cell const& cell) const noexcept
    {
        return ToGridPosition3(cell.Position());
    }
}

#endif //!CELLSIM_MOLECULAR_MOLECULEFILED_HPP