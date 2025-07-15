#ifndef CELLSIM_CELLS_WAVEPROPAGATIONCELLBEHAVIOR_HPP
#define CELLSIM_CELLS_WAVEPROPAGATIONCELLBEHAVIOR_HPP

#include "base.hpp"
#include "CellSim.Cells.NormalCellBehavior.hpp"

#if 0 // コメント文

| 記号                                            | C++変数名                                          | 説明                     |
| ---------------------------------------------- | ----------------------------------------------- | ---------------------- |
| KR                                             | CampReceptorDissociationConstantR               | cAMP-受容体複合体のR状態での解離定数  |
| KD                                             | CampReceptorDissociationConstantD               | cAMP-受容体複合体のD状態での解離定数  |
| k1                                             | RateConstantRtoD                                | R → D 変換の速度定数          |
| k-1                                            | RateConstantDtoR                                | D → R 変換の速度定数          |
| k2                                             | RateConstantRPtoDP                              | RP → DP 変換の速度定数        |
| k-2                                            | RateConstantDPtoRP                              | DP → RP 変換の速度定数        |
| cAMP receptor                                  | CampReceptorCount                               | cAMP受容体の数              |
| Adenylate cyclase                              | AdenylateCyclaseActivity                        | アデニル酸シクラーゼの活性          |
| Cell density                                   | CellDensity                                     | 細胞密度                   |
| Intracellular volume                           | IntracellularVolume                             | 細胞内体積                  |
| Activity of adenylate cyclase (Basal rate)     | AdenylateCyclaseBasalRate                       | アデニル酸シクラーゼの基礎活性        |
| Activity of adenylate cyclase (Max activation) | AdenylateCyclaseMaxRate                         | アデニル酸シクラーゼの最大活性        |
| Km,cyclase                                     | MichaelisConstantAdenylateCyclase               | アデニル酸シクラーゼのミカエリス定数     |
| ki                                             | IntracellularPhosphodiesteraseRateConstant      | 細胞内ホスホジエステラーゼの1次反応速度定数 |
| Vmax,PDE                                       | MaxActivityExtracellularPhosphodiesterase       | 細胞外ホスホジエステラーゼの最大活性     |
| Km,PDE                                         | MichaelisConstantExtracellularPhosphodiesterase | 細胞外ホスホジエステラーゼのミカエリス定数  |
| kt                                             | CampTransportRateConstant                       | 細胞外へのcAMP輸送の1次反応速度定数   |
| ATP                                            | AtpConcentration                                | ATP濃度                  |


#endif //コメント文

namespace CellSim::Cells
{
    class WavePropagationCellBehavior : public NormalCellBehavior {
        CellGrowthResult ComputeGrowth(const Cell* sender) override;
        double ComputeMetabolicChange(const Cell* sender, CellMetabolicArgs args) override;
        double ComputeMoleculeEmitAmount(const Cell* sender, CellMoleculeEmissionArgs args) override;
        
        CellBehavior* CreateClone() const override;
        
        constexpr bool HasState() const noexcept override;
        Numerics::Vector3 OnSenseMolecules(const Cell* sender, CellMoleculeSensingArgs args) override;
        bool ShouldDivideThisStep(const Cell* sender) noexcept override;
    };
}

#endif //!CELLSIM_CELLS_WAVEPROPAGATIONCELLBEHAVIOR_HPP