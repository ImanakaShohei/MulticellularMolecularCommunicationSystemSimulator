#ifndef CELLSIM_CELLALGORITHMS_CLUSTERMODEL_HPP
#define CELLSIM_CELLALGORITHMS_CLUSTERMODEL_HPP

#include "base.hpp"

#include <vector>

namespace CellSim::CellAlgorithms
{
    /// @brief クラスタモデル
    class ClusterModel final {
        public:

        CELLSIM_STATIC_CLASS(ClusterModel);

        static void Combine(::std::vector<Cells::Cell>& cells, ::std::vector<Molecular::MoleculeField> const& fields);
        static void Combine(::std::vector<Cells::Cell>& cells, ::std::vector<Molecular::MoleculeField> const& fields, const CellList* pCellList);
        static void Combine(::std::vector<Cells::Cell>& cells, ::std::vector<Molecular::MoleculeField> const& fields, ::std::nullptr_t);
    };
}

namespace CellSim::CellAlgorithms
{
    inline void ClusterModel::Combine(::std::vector<Cells::Cell>& cells, ::std::vector<Molecular::MoleculeField> const& fields)
    {
        Combine(cells, fields, (const CellList*)nullptr);
    }

    inline void ClusterModel::Combine(::std::vector<Cells::Cell>& cells, ::std::vector<Molecular::MoleculeField> const& fields, ::std::nullptr_t)
    {
        Combine(cells, fields, (const CellList*)nullptr);
    }
}

#endif //!CELLSIM_CELLALGORITHMS_CLUSTERMODEL_HPP