#pragma once

#include "Cell.hpp"

class SignalDiffusionCell : public Cell {
    private:

    static constexpr double C = 10;
    static constexpr double K1 = 0.036;
    static constexpr double K2 = 0.666;
    static constexpr double L1 = 10;
    static constexpr double L2 = 0.005;
    static constexpr double Q = 4000;
    static constexpr double SIGMA = 6.0;
    static constexpr double Ki = 1.7;
    static constexpr double Ke = 5.4;
    static constexpr double Kt = 0.9;
    static constexpr double ALPHA = 1;
    static constexpr double H = 5;
    static constexpr double THETA = 0.01;
    static constexpr double LAMBDA = 0.01;
    static constexpr double EPSILON = 1;

    double cAMP = 0;
    double activeReceptor = 0.0;
    double diffCamp = 0;
    double diffActiveReceptor = 0;
        
    public:

    using Cell::Cell;

    constexpr double emitMolecule(int32_t moleculeId) noexcept override;
    double calcSynthesis(double extracellularCAMP) const noexcept;
    constexpr double f1(double cAMP) const noexcept;
    constexpr double f2(double cAMP) const noexcept;

    SignalDiffusionCell divide();

    void setDiffState(double extracellularCAMP) noexcept;
    void updateState(double extracellularCAMP) noexcept;
};

constexpr double SignalDiffusionCell::emitMolecule(int32_t moleculeId) noexcept
{
    return cAMP * Kt / H;
}

constexpr double SignalDiffusionCell::f1(double cAMP) const noexcept
{
    return (K1 + K2 * cAMP) / (1 + cAMP);
}

constexpr double SignalDiffusionCell::f2(double cAMP) const noexcept
{
    return (K1 * L1 + K2 * L2 * C * cAMP) / (1 + C * cAMP);
}

