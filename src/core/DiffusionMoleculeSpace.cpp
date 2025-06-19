#include "DiffusionMoleculeSpace.hpp"

#include "../thirdparty/nameof.hpp"
#include "../SimulationSettings.hpp"
#include "../utils/MakeVector.hpp"
#include <ostream>
#include <random>

// 3次元拡散方程式の参考文献 https://cvtech.cc/diffusion3d/
double DiffusionMoleculeSpace::diffuse(int32_t x, int32_t y, int32_t z) const
{
    return D *
           (moleculeSpace[x + 1][y][z] + moleculeSpace[x - 1][y][z] + moleculeSpace[x][y + 1][z]   //
            + moleculeSpace[x][y - 1][z] + moleculeSpace[x][y][z + 1] + moleculeSpace[x][y][z - 1] //
            - 6.0 * moleculeSpace[x][y][z]) /
           (dr * dr);
}

double DiffusionMoleculeSpace::production(int32_t, int32_t, int32_t)
{
    return 0.0;
}

double DiffusionMoleculeSpace::decay(int32_t, int32_t, int32_t)
{
    return 0.0;
}

double DiffusionMoleculeSpace::advection(int32_t, int32_t, int32_t)
{
    return 0.0;
}

void DiffusionMoleculeSpace::setupBoundary(Field3D<double>& ms, MoleculeSpaceBorderType borderType)
{
    switch (borderType) {
        case MoleculeSpaceBorderType::NEUMANN:
            // #pragma omp parallel for
            for (uint32_t x = 1; x <= width; x++) {
                for (uint32_t y = 1; y <= height; y++) {
                    ms[x][y][0]         = ms[x][y][1];
                    ms[x][y][depth + 1] = ms[x][y][depth];
                }
            }
            // #pragma omp parallel for
            for (uint32_t x = 1; x <= width; x++) {
                for (uint32_t z = 1; z <= depth; z++) {
                    ms[x][0][z]          = ms[x][1][z];
                    ms[x][height + 1][z] = ms[x][height][z];
                }
            }
            // #pragma omp parallel for
            for (uint32_t y = 1; y <= height; y++) {
                for (uint32_t z = 1; z <= depth; z++) {
                    ms[0][y][z]         = ms[1][y][z];
                    ms[width + 1][y][z] = ms[width][y][z];
                }
            }
            break;

        case MoleculeSpaceBorderType::DIRICHLET:
            // #pragma omp parallel for
            for (uint32_t x = 1; x <= width; x++) {
                for (uint32_t y = 1; y <= height; y++) {
                    ms[x][y][0]         = 0;
                    ms[x][y][depth + 1] = 0;
                }
            }
            // #pragma omp parallel for
            for (uint32_t x = 1; x <= width; x++) {
                for (uint32_t z = 1; z <= depth; z++) {
                    ms[x][0][z]          = 0;
                    ms[x][height + 1][z] = 0;
                }
            }
            // #pragma omp parallel for
            for (uint32_t y = 1; y <= height; y++) {
                for (uint32_t z = 1; z <= depth; z++) {
                    ms[0][y][z]         = 0;
                    ms[width + 1][y][z] = 0;
                }
            }
            break;

        case MoleculeSpaceBorderType::PBC:
            // #pragma omp parallel for
            for (uint32_t x = 1; x <= width; x++) {
                for (uint32_t y = 1; y <= height; y++) {
                    ms[x][y][0]         = ms[x][y][depth];
                    ms[x][y][depth + 1] = ms[x][y][1];
                }
            }
            // #pragma omp parallel for
            for (uint32_t x = 1; x <= width; x++) {
                for (uint32_t z = 1; z <= depth; z++) {
                    ms[x][0][z]          = ms[x][height][z];
                    ms[x][height + 1][z] = ms[x][1][z];
                }
            }
            // #pragma omp parallel for
            for (uint32_t y = 1; y <= height; y++) {
                for (uint32_t z = 1; z <= depth; z++) {
                    ms[0][y][z]         = ms[width][y][z];
                    ms[width + 1][y][z] = ms[1][y][z];
                }
            }

            break;
        default:
            std::cerr << "BorderType is Wrong: " << NAMEOF_ENUM(borderType) << std::endl;
            exit(1);

            break;
    }
}

DiffusionMoleculeSpace::DiffusionMoleculeSpace(
    const uint64_t moleculeNum,
    const MoleculeDistributionType distributionType,
    const MoleculeSpaceBorderType borderType,
    std::vector<Cell*>* pCells,
    const uint32_t ID,
    const double _D
)
  : width(SimulationSettings::MOLECULE_FIELD_X_LEN)
  , height(SimulationSettings::MOLECULE_FIELD_Y_LEN)
  , depth(SimulationSettings::MOLECULE_FIELD_Z_LEN)
  , dr((double)SimulationSettings::FIELD_X_LEN / (double)width)
  // , dr(10.0)
  , moleculeNum(moleculeNum)
  , borderType(borderType)
  , deltaMoleculeSpace(make_vector<double>({ (size_t)(width + 2), (size_t)(height + 2), (size_t)(depth + 2) }))
  , moleculeSpace(make_vector<double>({ (size_t)(width + 2), (size_t)(height + 2), (size_t)(depth + 2) }))
  // , moleculeSpace(make_vector<double>({ (size_t)width, (size_t)height, (size_t)depth }))
  , pCells(pCells)
  , D(_D)
  , ID(ID)
{
    std::mt19937 randGen(0); // TODO: シード値を変更できるようにする

    switch (distributionType) {
        case MoleculeDistributionType::UNIFORM: {
            std::cout << "uniform" << std::endl;
            std::uniform_int_distribution<int32_t> randX(0, width - 1);
            std::uniform_int_distribution<int32_t> randY(0, height - 1);
            std::uniform_int_distribution<int32_t> randZ(0, depth - 1);
            std::uniform_real_distribution<double> randMolecule(0.0, 1.0);

            // for (int64_t i = 0; i < moleculeNum; i++) {
            //     int32_t x = randX(randGen);
            //     int32_t y = randY(randGen);
            //     int32_t z = randZ(randGen);

            //     moleculeSpace[x + 1][y + 1][z + 1] += 40.0; // 境界部分からずらす
            // }

            for (uint32_t x = 1; x <= width; x++) {
                for (uint32_t y = 1; y <= height; y++) {
                    for (uint32_t z = 1; z <= depth; z++) {
                        moleculeSpace[x][y][z] = randMolecule(randGen);
                    }
                }
            }

            break;
        }
        case MoleculeDistributionType::GAUSSIAN: {
            std::cout << "gaussian" << std::endl;
            std::normal_distribution<double> randX(width / 2.0, 5.0);
            std::normal_distribution<double> randY(height / 2.0, 5.0);
            std::normal_distribution<double> randZ(depth / 2.0, 5.0);

            for (uint64_t i = 0; i < moleculeNum; i++) {
                int32_t x, y, z;

                do {
                    x = (int32_t)randX(randGen);
                } while (!(0 <= x && (uint32_t)x < width));

                do {
                    y = (int32_t)randY(randGen);
                } while (!(0 <= y && (uint32_t)y < height));

                do {
                    z = (int32_t)randZ(randGen);
                } while (!(0 <= z && (uint32_t)z < depth));

                moleculeSpace[x + 1][y + 1][z + 1] += 1.0; // 境界部分からずらす
            }
            break;
        }
        case MoleculeDistributionType::POINT: {
            moleculeSpace[width / 2 + 1][height / 2 + 1][depth / 2 + 1] = (double)moleculeNum;
            break;
        }
        default:
            std::cerr << "DistributionType is Wrong: " << NAMEOF_ENUM(distributionType) << std::endl;
            break;
    }
}

void DiffusionMoleculeSpace::calcConcentrationDiff()
{
    for (uint32_t x = 1; x <= width; x++) {
        for (uint32_t y = 1; y <= height; y++) {
            for (uint32_t z = 1; z <= depth; z++) {
                deltaMoleculeSpace[x][y][z] = diffuse(x, y, z) + production(x, y, z) - decay(x, y, z) - advection(x, y, z);
            }
        }
    }

    const int32_t width  = SimulationSettings::FIELD_X_LEN;
    const int32_t height = SimulationSettings::FIELD_Y_LEN;
    const int32_t depth  = SimulationSettings::FIELD_Z_LEN;
    for (auto pCell : *pCells) {
        Cell& cell = *pCell;

        int32_t x = (int32_t)((cell.getPosition().x + width / 2) / dr) + 1;
        int32_t y = (int32_t)((cell.getPosition().y + height / 2) / dr) + 1;
        int32_t z = (int32_t)((cell.getPosition().z + depth / 2) / dr) + 1;

        deltaMoleculeSpace[x][y][z] += cell.emitMolecule(ID);
    }
}

void DiffusionMoleculeSpace::nextStep()
{
    // #pragma omp parallel for
    for (uint32_t x = 1; x <= width; x++) {
        for (uint32_t y = 1; y <= height; y++) {
            for (uint32_t z = 1; z <= depth; z++) {
                moleculeSpace[x][y][z] += deltaMoleculeSpace[x][y][z];
                // deltaMoleculeSpace[x][y][z] = 0.0;
            }
        }
    }

    setupBoundary(moleculeSpace, borderType);
}

void DiffusionMoleculeSpace::print(::std::ostream& out) const
{
    if (depth == 1) {
        for (uint32_t x = 0; x <= width + 1; x++) {
            for (uint32_t y = 0; y <= height + 1; y++) {
                out << moleculeSpace[x][y][1] << " ";
            }
            out << "|" << std::endl;
        }

        return;
    }

    for (uint32_t x = 1; x <= width; x++) {
        for (uint32_t y = 1; y <= height; y++) {
            for (uint32_t z = 1; z <= depth; z++) {
                out << moleculeSpace[x][y][z] << " ";
            }
            out << "|";
        }
        out << std::endl;
    }
}

double DiffusionMoleculeSpace::getMoleculeNum(Vec3 pos) const noexcept
{
    const int32_t width  = SimulationSettings::FIELD_X_LEN;
    const int32_t height = SimulationSettings::FIELD_Y_LEN;
    const int32_t depth  = SimulationSettings::FIELD_Z_LEN;
    const double x       = (pos.x + width / 2) / dr + 1;
    const double y       = (pos.y + height / 2) / dr + 1;
    const double z       = (pos.z + depth / 2) / dr + 1;

    return moleculeSpace[(int)x][(int)y][(int)z];
}