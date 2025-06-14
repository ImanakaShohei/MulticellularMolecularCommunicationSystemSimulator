#include "CellSim.CellAlgorithms.CellList.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmStepArgs.hpp"
#include "CellSim.Cells.CellInfo.hpp"
#include "CellSim.Messages.hpp"
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
        , m_searchGridCountX((size_t)(searchRadius / m_gridLengthX))
        , m_searchGridCountY((size_t)(searchRadius / m_gridLengthY))
        , m_searchGridCountZ((size_t)(searchRadius / m_gridLengthZ))
        , m_searchRadius(searchRadius)
        , m_span(gridCountX, gridCountY, gridCountZ, m_cellField.data())
        , m_squareSeachRadius(searchRadius * searchRadius)
    {
        if (gridCountX == 0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("CellAlgorithms.CellList.CellList.Error.gridCountX"));
        if (gridCountY == 0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("CellAlgorithms.CellList.CellList.Error.gridCountY"));
        if (gridCountZ == 0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("CellAlgorithms.CellList.CellList.Error.gridCountZ"));

        if (searchRadius < 0.0) [[unlikely]] throw ::std::invalid_argument(Messages::Get("CellAlgorithms.CellList.CellList.Error.searchRadius"));

        if (m_gridLengthX == 0.0) {
            m_searchGridCountX = 0;
            m_reverseGridLengthX = 0;
        }

        if (m_gridLengthY == 0.0) {
            m_searchGridCountY = 0;
            m_reverseGridLengthY = 0;
        }
        
        if (m_gridLengthZ == 0.0) {
            m_searchGridCountZ = 0;
            m_reverseGridLengthZ = 0;
        }
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

            int32_t atX = (int32_t)(x * m_reverseGridLengthX);
            int32_t atY = (int32_t)(y * m_reverseGridLengthY);
            int32_t atZ = (int32_t)(z * m_reverseGridLengthZ);

            if ((size_t)atX >= m_gridCountX) continue;
            if ((size_t)atY >= m_gridCountY) continue;
            if ((size_t)atZ >= m_gridCountZ) continue;

            m_span.At(atX, atY, atZ).emplace_back(cell);
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

        int32_t xMin = (int32_t)(gridPosition.X - m_searchGridCountX);
        int32_t yMin = (int32_t)(gridPosition.Y - m_searchGridCountY);
        int32_t zMin = (int32_t)(gridPosition.Z - m_searchGridCountZ);
        int32_t xMax = (int32_t)(gridPosition.X + m_searchGridCountX);
        int32_t yMax = (int32_t)(gridPosition.Y + m_searchGridCountY);
        int32_t zMax = (int32_t)(gridPosition.Z + m_searchGridCountZ);

        if (xMin < 0) xMin = 0;
        if (yMin < 0) yMin = 0;
        if (zMin < 0) zMin = 0;

        if ((size_t)xMax >= m_gridCountX) xMax = (int32_t)(m_gridCountX) - 1;
        if ((size_t)yMax >= m_gridCountY) yMax = (int32_t)(m_gridCountY) - 1;
        if ((size_t)zMax >= m_gridCountZ) zMax = (int32_t)(m_gridCountZ) - 1;

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
        
        int32_t xMin = (int32_t)(gridPosition.X - m_searchGridCountX);
        int32_t yMin = (int32_t)(gridPosition.Y - m_searchGridCountY);
        int32_t zMin = (int32_t)(gridPosition.Z - m_searchGridCountZ);
        int32_t xMax = (int32_t)(gridPosition.X + m_searchGridCountX);
        int32_t yMax = (int32_t)(gridPosition.Y + m_searchGridCountY);
        int32_t zMax = (int32_t)(gridPosition.Z + m_searchGridCountZ);

        if (xMin < 0) xMin = 0;
        if (yMin < 0) yMin = 0;
        if (zMin < 0) zMin = 0;

        if ((size_t)xMax >= m_gridCountX) xMax = (int32_t)(m_gridCountX) - 1;
        if ((size_t)yMax >= m_gridCountY) yMax = (int32_t)(m_gridCountY) - 1;
        if ((size_t)zMax >= m_gridCountZ) zMax = (int32_t)(m_gridCountZ) - 1;

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
            (int32_t)((position.X + Settings::Config::Simulation::FieldRadiusX()) * m_reverseGridLengthX),
            (int32_t)((position.Y + Settings::Config::Simulation::FieldRadiusY()) * m_reverseGridLengthY),
            (int32_t)((position.Z + Settings::Config::Simulation::FieldRadiusZ()) * m_reverseGridLengthZ)
        );
    }

}