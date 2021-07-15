#pragma once

#include <vector>
#include <stdio.h>

class OctaveCodegen
{
public:
    void GenerateCode(std::vector<double> real_values, std::vector<double> interp_values, double x_min, double x_max, double y_min, double y_max, double h);
private:
    void dump_matrix(std::vector<double> values, FILE* f, const char* name, const long y_size, const long x_size);
};
