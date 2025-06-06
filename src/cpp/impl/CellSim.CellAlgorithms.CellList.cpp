#include "CellSim.CellAlgorithms.CellList.hpp"
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
        , m_searchRadius(searchRadius)
        , m_span(gridCountX, gridCountY, gridCountZ, m_cellField.data())
        , m_squareSeachRadius(searchRadius * searchRadius)
    {
        if (gridCountX == 0) [[unlikely]] throw ::std::invalid_argument("The parameter 'gridCountX' must be non-zero.");
        if (gridCountY == 0) [[unlikely]] throw ::std::invalid_argument("The parameter 'gridCountY' must be non-zero.");
        if (gridCountZ == 0) [[unlikely]] throw ::std::invalid_argument("The parameter 'gridCountZ' must be non-zero.");

        if (searchRadius < 0.0) [[unlikely]] throw ::std::invalid_argument("The parameter 'searchRadius' must be greater than or equal to zero.");
    }

    CellList::~CellList()
    {
        // TODO: ここに処理を追加します
    }

    void CellList::BeforeAdvanceStep(
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecular::MoleculeField> const&
    )
    {
        // TODO: ここに処理を追加します
    }

    ::std::vector<Cells::CellInfo> CellList::GetAffectableCellInfos(
        [[maybe_unused]] Cells::Cell const& target,
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecular::MoleculeField> const&
    ) const
    {
        //: ここに処理を追加します
        return {};
    }

    Threading::Generator<Cells::CellInfo> CellList::IterateAffectableCellInfos(
        [[maybe_unused]] Cells::Cell const& target,
        [[maybe_unused]] ::std::vector<Cells::Cell> const& cells,
        ::std::vector<Molecular::MoleculeField> const&
    ) const
    {
        //: ここに処理を追加します
        co_return;
    }

    void CellList::OnAdvanceStep(
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Molecular::MoleculeField> const&
    )
    {
        for (auto& vec : m_cellField) {
            vec.clear();
        }
    }
}