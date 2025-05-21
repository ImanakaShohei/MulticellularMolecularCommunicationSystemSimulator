/**
 * @file MoleculeSpace.hpp
 * @author Takanori Saiki
 * @brief
 * @version 0.1
 * @date 2023-07-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "../utils/Vec3.hpp"
#include <iosfwd>

enum class MoleculeDistributionType
{
    UNIFORM,
    GAUSSIAN,
    POINT
};

enum class MoleculeSpaceBorderType
{
    NEUMANN,   // 境界部分を分子が通過できない(その場にとどまる)
    DIRICHLET, // 境界部分で分子が消失する
    PBC,       // 境界部分で分子が反対側に出現する
};

// class Distribution
// {
//   private:
//     MoleculeDistributionType distributionType;

//     std::normal_distribution<double> normalDistribution;
//     std::uniform_real_distribution<double> uniformDistribution;

//   public:
//     Distribution(/* args */);
//     ~Distribution();

//     void setDistributionType(MoleculeDistributionType distributionType);
//     double generate(auto &randGen);
// };

class MoleculeSpace
{
    public:
    MoleculeSpace() = default;
    virtual ~MoleculeSpace() = default;

    virtual void calcConcentrationDiff() = 0;
    virtual void nextStep() = 0;

    virtual double getMoleculeNum(Vec3 pos) const noexcept = 0;

    virtual void print(::std::ostream& out) const = 0;
};