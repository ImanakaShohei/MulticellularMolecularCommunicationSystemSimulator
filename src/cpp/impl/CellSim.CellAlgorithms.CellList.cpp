#include "CellSim.CellAlgorithms.CellList.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmStepArgs.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Settings.Config.Simulation.hpp"
#include "CellSim.Settings.Config.CellAlgorithm.CellList.hpp"
#include "CellSim.Threading.Generator.hpp"

#include <stdexcept>

namespace CellSim::CellAlgorithms
{
    CellList::CellList()
        : CellList(
            Settings::Config::CellAlgorithm::CellList::GridCountX(),
            Settings::Config::CellAlgorithm::CellList::GridCountY(),
            Settings::Config::CellAlgorithm::CellList::GridCountZ(),
            Settings::Config::CellAlgorithm::CellList::SearchRadius()
        )
    {
    }

    CellList::CellList(
        size_t gridCountX,
        size_t gridCountY,
        size_t gridCountZ,
        double searchRadius
    )
        : m_cellField(gridCountX * gridCountY * gridCountZ)
        , m_gridCountX(gridCountX)
        , m_gridCountY(gridCountY)
        , m_gridCountZ(gridCountZ)
        , m_gridLengthX(Settings::Config::Simulation::FieldRadiusX() * 2.0 / gridCountX)
        , m_gridLengthY(Settings::Config::Simulation::FieldRadiusY() * 2.0 / gridCountY)
        , m_gridLengthZ(Settings::Config::Simulation::FieldRadiusZ() * 2.0 / gridCountZ)
        , m_reverseGridLengthX(1.0 / m_gridLengthX)
        , m_reverseGridLengthY(1.0 / m_gridLengthY)
        , m_reverseGridLengthZ(1.0 / m_gridLengthZ)
        , m_searchGridCountX(searchRadius / m_gridLengthX)
        , m_searchGridCountY(searchRadius / m_gridLengthY)
        , m_searchGridCountZ(searchRadius / m_gridLengthZ)
        , m_searchRadius(searchRadius)
        , m_span(gridCountX, gridCountY, gridCountZ, m_cellField.data())
        , m_squareSeachRadius(searchRadius * searchRadius)
    {
        if (gridCountX == 0) [[unlikely]] throw ::std::invalid_argument("The parameter 'gridCountX' must be non-zero.");
        if (gridCountY == 0) [[unlikely]] throw ::std::invalid_argument("The parameter 'gridCountY' must be non-zero.");
        if (gridCountZ == 0) [[unlikely]] throw ::std::invalid_argument("The parameter 'gridCountZ' must be non-zero.");

        if (searchRadius < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'searchRadius' must be greater than or equal to zero.");
    }

    void CellList::BeforeAdvanceStep(
        const Simulation*,
        CellAlgorithmStepArgs args
    )
    {
        for (Cells::Cell const& cell : *args.Cells) {
            Numerics::Vector3 position = cell.Position();

            double x = position.X + Settings::Config::Simulation::FieldRadiusX();

            if (x < 0.0) continue;

            double y = position.Y + Settings::Config::Simulation::FieldRadiusY();

            if (y < 0.0) continue;

            double z = position.Z + Settings::Config::Simulation::FieldRadiusZ();

            if (z < 0.0) continue;

            m_span.At((size_t)(x * m_reverseGridLengthX), (size_t)(y * m_reverseGridLengthY), (size_t)(z * m_reverseGridLengthZ)).emplace_back(cell);
        }
    }

    ::std::vector<Cells::CellInfo> CellList::GetAffectableCellInfos(
        const Model::CellSimulationModel*,
        CellAlgorithmAffectableCellQueryArgs args
    ) const
    {
        Numerics::Vector3 position = args.Target->Position();
        Numerics::GridPosition3 gridPosition = ToGridPosition3(position);
        
        ::std::vector<Cells::CellInfo> result;

        size_t xMin = gridPosition.X - m_searchGridCountX;
        size_t yMin = gridPosition.Y - m_searchGridCountY;
        size_t zMin = gridPosition.Z - m_searchGridCountZ;
        size_t xMax = gridPosition.X + m_searchGridCountX;
        size_t yMax = gridPosition.Y + m_searchGridCountY;
        size_t zMax = gridPosition.Z + m_searchGridCountZ;

        if (gridPosition.X < m_reverseGridLengthX) xMin = 0;
        if (gridPosition.Y < m_reverseGridLengthY) yMin = 0;
        if (gridPosition.Z < m_reverseGridLengthZ) zMin = 0;

        if (xMax >= m_gridCountX) xMax = m_gridCountX - 1;
        if (yMax >= m_gridCountY) yMax = m_gridCountY - 1;
        if (zMax >= m_gridCountZ) zMax = m_gridCountZ - 1;

        for (size_t x = xMin; x <= xMax; x++) {
            auto span2 = m_span[x];
            for (size_t y = yMin; y <= yMax; y++) {
                auto span = span2[y];
                for (size_t z = zMin; z <= zMax; z++) {
                    for (Cells::CellInfo const& info : span[z]) {
                        if (info.Position == position) continue;

                        if (IsWithinSearchRadius(position, info.Position)) {
                            result.emplace_back(info);
                        }
                    }
                }
            }
        }

        return result;
    }

    Threading::Generator<Cells::CellInfo> CellList::IterateAffectableCellInfos(
        const Model::CellSimulationModel*,
        CellAlgorithmAffectableCellQueryArgs args
    ) const
    {
        Numerics::Vector3 position = args.Target->Position();
        Numerics::GridPosition3 gridPosition = ToGridPosition3(position);
        

        size_t xMin = gridPosition.X - m_searchGridCountX;
        size_t yMin = gridPosition.Y - m_searchGridCountY;
        size_t zMin = gridPosition.Z - m_searchGridCountZ;
        size_t xMax = gridPosition.X + m_searchGridCountX;
        size_t yMax = gridPosition.Y + m_searchGridCountY;
        size_t zMax = gridPosition.Z + m_searchGridCountZ;

        if (gridPosition.X < m_reverseGridLengthX) xMin = 0;
        if (gridPosition.Y < m_reverseGridLengthY) yMin = 0;
        if (gridPosition.Z < m_reverseGridLengthZ) zMin = 0;

        if (xMax >= m_gridCountX) xMax = m_gridCountX - 1;
        if (yMax >= m_gridCountY) yMax = m_gridCountY - 1;
        if (zMax >= m_gridCountZ) zMax = m_gridCountZ - 1;

        for (size_t x = xMin; x <= xMax; x++) {
            auto span2 = m_span[x];
            for (size_t y = yMin; y <= yMax; y++) {
                auto span = span2[y];
                for (size_t z = zMin; z <= zMax; z++) {
                    for (Cells::CellInfo const& info : span[z]) {
                        if (info.Position == position) continue;

                        if (IsWithinSearchRadius(position, info.Position)) {
                            co_yield info;
                        }
                    }
                }
            }
        }

        co_return;
    }

    void CellList::OnAdvanceStep(
        const Simulation*,
        CellAlgorithmStepArgs
    )
    {
        for (auto& vec : m_cellField) {
            vec.clear();
        }
    }

    Numerics::GridPosition3 CellList::ToGridPosition3(Numerics::Vector3 position) const noexcept
    {
        double x = position.X + Settings::Config::Simulation::FieldRadiusX();

        double y = position.Y + Settings::Config::Simulation::FieldRadiusY();

        double z = position.Z + Settings::Config::Simulation::FieldRadiusZ();

        return Numerics::GridPosition3(
            (size_t)((position.X + Settings::Config::Simulation::FieldRadiusX()) * m_reverseGridLengthX),
            (size_t)((position.Y + Settings::Config::Simulation::FieldRadiusY()) * m_reverseGridLengthY),
            (size_t)((position.Z + Settings::Config::Simulation::FieldRadiusZ()) * m_reverseGridLengthZ)
        );
    }

}