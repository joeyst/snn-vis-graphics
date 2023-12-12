
#include <utility>
#include <vector> 
#include <cstdint>
#include "config.h"
#include "Point3D.h"

#ifndef _UTILS_H
#define _UTILS_H

std::pair<PointCoords3D, PointCoords3D> GetConnectionEndpoints(const PointCoords3D& start, const PointCoords3D& end, float segmentPercent);

float GetTolFactor(int n_fires);
std::vector<float> GetOjaWeightChanges(const std::vector<float>& energies, const std::vector<float>& weights); 

// SOURCE: https://stackoverflow.com/questions/109023/count-the-number-of-set-bits-in-a-32-bit-integer 
int NumberOfSetBits(uint32_t i);

float RandomWeight(); // Returns random weight in range [0.01, 1]. 

std::vector<PointIds3D> GetCoordsInRectangularPrism(PointIds3D start, PointIds3D dxyz);

#endif 
