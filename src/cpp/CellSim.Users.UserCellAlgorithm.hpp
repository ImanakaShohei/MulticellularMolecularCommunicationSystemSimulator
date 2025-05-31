#ifndef CELLSIM_USERS_USERCELLALGORITHM_HPP
#define CELLSIM_USERS_USERCELLALGORITHM_HPP

#include "impl/base.hpp"
#include "impl/CellSim.CellAlgorithms.CellAlgorithm.hpp"

namespace CellSim::Users
{
    /// @brief ユーザー定義高速化アルゴリズム
    class UserCellAlgorithm : public CellAlgorithms::CellAlgorithm {
        public:

        // ここで引数は指定してはいけなウイ
        UserCellAlgorithm() = default;

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;

        ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            Cells::Cell const& c,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;

        Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            Cells::Cell const& c,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;

        void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;
    };
}

#endif //!CELLSIM_USERS_USERCELLALGORITHM_HPP