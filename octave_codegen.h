#pragma once

#include <vector>

class OctaveCodegen
{
public:
    void GenerateCode(std::vector<double> real_values, std::vector<double> interp_values, double x_min, double x_max, double y_min, double y_max, double h);
};
