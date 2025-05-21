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

#include "core/DiffusionMoleculeSpace.hpp"

class UserMoleculeSpace : public DiffusionMoleculeSpace
{
  private:
    static constexpr double _D = 0.024 * 1000000.0;

  public:
    UserMoleculeSpace(const uint64_t moleculeNum, const MoleculeDistributionType distributionType, const MoleculeSpaceBorderType borderType, std::vector<Cell*>* cells,
                      const uint32_t ID);
    ~UserMoleculeSpace();

    void calcConcentrationDiff() noexcept override;
    void nextStep() noexcept override;
};