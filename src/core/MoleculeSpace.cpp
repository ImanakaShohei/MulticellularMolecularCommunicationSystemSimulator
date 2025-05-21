#include "MoleculeSpace.hpp"

// Distribution::Distribution(/* args */)
// {
// }

// Distribution::~Distribution()
// {
// }

// void Distribution::setDistributionType(MoleculeDistributionType distributionType)
// {
//     this->distributionType = distributionType;
// }

// double Distribution::generate(auto& randGen)
// {
//     switch (distributionType) {
//         case MoleculeDistributionType::UNIFORM:
//             return normalDistribution(randGen);
//             break;
//         case MoleculeDistributionType::GAUSSIAN:
//             return uniformDistribution(randGen);
//             break;
//         default:
//             std::cerr << "DistributionType is Wrong: " << NAMEOF_ENUM(distributionType) << std::endl;
//             exit(1);
//     }
// }

// void MoleculeSpace::calcConcentrationDiff() noexcept
// {
//     for (int32_t x = 1; x <= width; x++) {
//         for (int32_t y = 1; y <= height; y++) {
//             for (int32_t z = 1; z <= depth; z++) {
//                 deltaMoleculeSpace[x][y][z] = diffuse(x, y, z) + production(x, y, z) - decay(x, y, z) - advection(x, y, z);
//             }
//         }
//     }

//     // for (uint32_t i = 0; i < cells.size(); i++) {
//     //     Cell* cell = cells[i];
//     //     int32_t x  = (int32_t)(cell->getPosition().x / dr) + 1;
//     //     int32_t y  = (int32_t)(cell->getPosition().y / dr) + 1;
//     //     int32_t z  = (int32_t)(cell->getPosition().z / dr) + 1;

//     //     deltaMoleculeSpace[x][y][z] += cell->emitMolecule(ID);
//     // }
// }

// void MoleculeSpace::nextStep() noexcept
// {
//     for (int32_t x = 1; x <= width; x++) {
//         for (int32_t y = 1; y <= height; y++) {
//             for (int32_t z = 1; z <= depth; z++) {
//                 moleculeSpace[x][y][z] += deltaMoleculeSpace[x][y][z];
//                 deltaMoleculeSpace[x][y][z] = 0.0;
//             }
//         }
//     }

//     setupBoundary(moleculeSpace, MoleculeSpaceBorderType::NEUMANN);
// }
