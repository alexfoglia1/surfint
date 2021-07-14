#include <iostream>
#include <libInterpolate/Interpolate.hpp>

#include "octave_codegen.h"
#include "surface_generator.h"

const double x_start = 0.0;
const double y_start = 0.0;

const double x_end = 1.0;
const double y_end = 1.0;

const double h_train = 0.25;
const double h_real = 0.1;

const std::function<double(double, double)> f = [] (double x, double y) -> double { return x + y; };

int main()
{
    _2D::BicubicInterpolator<double> interp;
    OctaveCodegen codegen;

    SurfaceGenerator traingen(x_start, x_end, y_start, y_end, h_train);
    SurfaceGenerator realgen(x_start, x_end, y_start, y_end, h_real);
    SurfaceGenerator apprgen(x_start, x_end, y_start, y_end, h_real);
    std::vector<double> x_train, y_train, z_train;
    std::vector<double> x_real, y_real, z_real;
    std::vector<double> x_appr, y_appr, z_appr;

    traingen.GenerateSurface(x_train, y_train, z_train, f);
    interp.setData(x_train, y_train, z_train);

    realgen.GenerateSurface(x_real, y_real, z_real, f);
    apprgen.GenerateSurface(x_appr, y_appr, z_appr, [interp] (double x, double y) -> double { return interp(x, y); });

    Eigen::MatrixXd appr_surface(y_real.size(), x_real.size());
    Eigen::MatrixXd real_surface(y_real.size(), x_real.size());
    for (long i = 0; i < real_surface.rows(); i++)
    {
        for(long j = 0; j < real_surface.cols(); j++)
        {
            real_surface(i, j) = z_real[i * real_surface.rows() + j];
            appr_surface(i, j) = z_appr[i * real_surface.rows() + j];
        }
    }

    codegen.GenerateCode(real_surface, appr_surface, x_start, x_end, y_start, y_end, h_real);

}
