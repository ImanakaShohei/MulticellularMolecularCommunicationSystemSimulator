#include "SignalDiffusionCell.hpp"

double SignalDiffusionCell::calcSynthesis(double extracellularCAMP) const noexcept
{
    const double y = (activeReceptor * extracellularCAMP) / (1.0 +
    extracellularCAMP);
    const double num = ALPHA * (LAMBDA * THETA + EPSILON * y * y);
    const double den = 1 + ALPHA * THETA + EPSILON * y * y * (1 + ALPHA);
    const double phi = num / den;

    return Q * SIGMA * phi / (Ki + Kt);
}

SignalDiffusionCell SignalDiffusionCell::divide()
{
    // Vec3 pos            = this->getPosition();
    Vec3 childDirection = Vec3::randomDirection2(); // どの方向に分裂するかを決める。分裂元は逆方向に動く。
    // 体積を二分割したときの半径を求める。
    double halfVolumeRadius = this->radius / std::pow(2, 1.0 / 3.0);

    // Cellのtypeはとりあえず継承する形にする
    SignalDiffusionCell c(this->typeID, this->getPosition() + childDirection, halfVolumeRadius);

    this->setRadius(halfVolumeRadius); // 分裂元も体積を半分にする

    c.addForce(childDirection);
    this->addForce(-childDirection);

    return c;
}

void SignalDiffusionCell::setDiffState(double extracellularCAMP) noexcept
{
    diffCamp = calcSynthesis(extracellularCAMP);
    diffActiveReceptor = (-activeReceptor * f1(extracellularCAMP) + (1.0 - activeReceptor) * f2(extracellularCAMP));
}

void SignalDiffusionCell::updateState(double extracellularCAMP) noexcept
{
    cAMP = diffCamp;
    activeReceptor += diffActiveReceptor * SimulationSettings::DELTA_TIME;
    activeReceptor = std::max(0.0, activeReceptor);
}
