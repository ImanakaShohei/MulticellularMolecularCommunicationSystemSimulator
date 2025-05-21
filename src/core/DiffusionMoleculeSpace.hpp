#pragma once

#include "MoleculeSpace.hpp"
#include "Cell.hpp"
#include "../utils/Util.hpp"

class DiffusionMoleculeSpace : public MoleculeSpace {
    protected:
    uint32_t width;                    // x方向の格子数(横幅)
    uint32_t height;                   // y方向の格子数(高さ)
    uint32_t depth;                    // z方向の格子数(縦幅)
    const double dr;                    // 空間の各格子の大きさ
    uint64_t moleculeNum;              // 現在の分子の総数
    MoleculeSpaceBorderType borderType; // 境界条件の種類

    Field3D<double> deltaMoleculeSpace;            // 次のステップでの分子の増減を格納する空間
    Field3D<double> moleculeSpace;                 // 分子を扱う空間。各格子に分子の数を格納する。
    std::vector<Cell*>* pCells; // 格子の情報を格納する配列

    const double D; // 拡散係数
    const uint32_t ID;

    double diffuse(int32_t x, int32_t y, int32_t z) const;
    double production(int32_t x, int32_t y, int32_t z);
    double decay(int32_t x, int32_t y, int32_t z);
    double advection(int32_t x, int32_t y, int32_t z);

    void setupBoundary(Field3D<double>& ms, MoleculeSpaceBorderType borderType);

    public:
    DiffusionMoleculeSpace(
        const uint64_t moleculeNum,
        const MoleculeDistributionType distributionType,
        const MoleculeSpaceBorderType borderType,
        std::vector<Cell*>* cells,
        const uint32_t ID,
        const double _D
    );

    void calcConcentrationDiff() override;
    void nextStep() override;

    double getMoleculeNum(Vec3 pos) const noexcept override;

    void print(::std::ostream& out) const override;
};