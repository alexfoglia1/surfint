#pragma once

#include <Eigen/Dense>

class OctaveCodegen
{
public:
    void GenerateCode(Eigen::MatrixXd real_values, Eigen::MatrixXd interp_values, double x_min, double x_max, double y_min, double y_max, double h);
};
