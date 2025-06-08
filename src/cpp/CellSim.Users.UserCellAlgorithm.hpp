#ifndef CELLSIM_USERS_USERCELLALGORITHM_HPP
#define CELLSIM_USERS_USERCELLALGORITHM_HPP

#include "impl/base.hpp"
#include "impl/CellSim.CellAlgorithms.CellAlgorithm.hpp"

namespace CellSim::Users
{
    /// @brief ユーザー定義高速化アルゴリズム
    class UserCellAlgorithm : public CellAlgorithms::CellAlgorithm {
        private:

        // TODO: ここにメンバーを追加します

        public:

        // ここで引数は指定してはいけなウイ
        UserCellAlgorithm();
        ~UserCellAlgorithm();

        void BeforeAdvanceStep(
            const Simulation* sender,
            CellAlgorithms::CellAlgorithmStepArgs args
        ) override;

        ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            const Model::CellSimulationModel* sender,
            CellAlgorithms::CellAlgorithmAffectableCellQueryArgs args
        ) const override;

        constexpr bool HasMultithreadingSupport() const noexcept override;

        Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            const Model::CellSimulationModel* sender,
            CellAlgorithms::CellAlgorithmAffectableCellQueryArgs args
        ) const override;

        void OnAdvanceStep(
            const Simulation* sender,
            CellAlgorithms::CellAlgorithmStepArgs args
        ) override;
    };
}

#endif //!CELLSIM_USERS_USERCELLALGORITHM_HPP