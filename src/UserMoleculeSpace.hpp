/**
 * @file UserMoleculeSpace.hpp
 * @author Takanori Saiki
 * @brief
 * @version 0.1
 * @date 2024-01-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "core/MoleculeSpace.hpp"

class UserMoleculeSpace : public MoleculeSpace
{
  private:
    const double _D = 0.024 * 1000000.0;

  public:
    UserMoleculeSpace(const uint64_t moleculeNum, const MoleculeDistributionType distributionType, const MoleculeSpaceBorderType borderType, std::vector<std::shared_ptr<UserCell>>& cells,
                      const uint32_t ID);
    ~UserMoleculeSpace();

    void calcConcentrationDiff() noexcept override;
    void nextStep() noexcept override;
};