#include <iostream>
#include <libInterpolate/Interpolate.hpp>

#include "octave_codegen.h"
#include "surface_generator.h"

const double x_start = 0;
const double y_start = 0;

const double x_end = 6.50;
const double y_end = 6.50;

const double h_train = 0.2;
const double h_real = 0.1;

const std::function<double(double, double)> f = [] (double x, double y) -> double { return sin(x) * cos(y);};

int main()
{
    _2D::ExtendedBicubicInterpolator<double> interp;
    OctaveCodegen codegen;

    SurfaceGenerator traingen(x_start, x_end, y_start, y_end, h_train);
    SurfaceGenerator realgen(x_start, x_end, y_start, y_end, h_real);
    SurfaceGenerator apprgen(x_start, x_end, y_start, y_end, h_real);
    std::vector<double> x_train, y_train, z_train;
    std::vector<double> x_real, y_real;
    std::vector<double> x_appr, y_appr;

    traingen.GenerateTrainer(x_train, y_train, z_train, f);
    interp.setData(x_train, y_train, z_train);

    std::vector<double> z_real = realgen.GenerateSurface(x_real, y_real, f);
    std::vector<double> z_appr = apprgen.GenerateSurface(x_appr, y_appr, [&interp] (double x, double y) -> double { return interp(x, y); });

    codegen.GenerateCode(z_real, z_appr, x_start, x_end, y_start, y_end, h_real);

}
