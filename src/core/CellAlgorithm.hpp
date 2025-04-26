#pragma once

#include "../SimulationSettings.hpp"
#include "../UserCell.hpp"
#include "../utils/Util.hpp"
#include "../utils/Vec3.hpp"
#include "../UserMoleculeSpace.hpp"
#include <memory>

class CellAlgorithm {
    private:

    protected:

    CellAlgorithm() = default;
    CellAlgorithm(CellAlgorithm const&) = default;
    CellAlgorithm(CellAlgorithm&&) = default;

    CellAlgorithm& operator=(CellAlgorithm const&) = default;
    CellAlgorithm& operator=(CellAlgorithm&&) = default;

    public:

    constexpr virtual ~CellAlgorithm() {}

    /**
     * @brief  与えられたCellに対して他のCellから働く力を計算する。
     *
     * @param c
     * @return Vec3
     * @details Cellから働く力は遠隔力と近隣力の2つで構成される。さらに、近接力は体積排除効果と接着力の2つに分類される。
     */
    virtual Vec3 calcCellForce(const ::std::shared_ptr<UserCell>& c, ::std::vector<::std::shared_ptr<UserCell>> const& cells, const ::std::vector<::std::unique_ptr<UserMoleculeSpace>>& moleculeSpaces) = 0;
    constexpr virtual void beforeNextStep(const ::std::vector<::std::shared_ptr<UserCell>>&, const ::std::vector<::std::unique_ptr<UserMoleculeSpace>>&) {}
    constexpr virtual void onNextStep(const ::std::vector<::std::shared_ptr<UserCell>>&, const ::std::vector<::std::unique_ptr<UserMoleculeSpace>>&) {}
};