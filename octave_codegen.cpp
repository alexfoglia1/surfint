#include "octave_codegen.h"

#include <math.h>


void OctaveCodegen::dump_matrix(std::vector<double> values, FILE* f, const char* name, const long y_size, const long x_size)
{
    fprintf(f,"%s = [", name);
    for(long i = 0; i < y_size; i++)
    {
        fprintf(f, "[");
        for(long j = 0; j < x_size; j++)
        {
            fprintf(f, "%f, ", values[i * x_size + j]);
        }
        fprintf(f, "];\n");
    }
    fprintf(f, "];\n");
}

void OctaveCodegen::GenerateCode(std::vector<double> real_values, std::vector<double> interp_values, double x_min, double x_max, double y_min, double y_max, double h)
{
    double x0 = fmin(x_min, x_max);
    double xf = fmax(x_min, x_max);
    double y0 = fmin(y_min, y_max);
    double yf = fmax(y_min, y_max);

    long x_size = (long) floorf(((x_max - x_min) / h));
    long y_size = (long) floorf(((y_max - y_min) / h));

    std::vector<double> err_values;
    for (long i = 0; i < x_size * y_size; i++)
    {
        err_values.push_back(fabs(real_values[i] - interp_values[i]));
    }

    FILE* f = fopen("../script.m", "w");

    printf("Writing script... ");

    fprintf(f, "x = linspace(%f, %f, %ld);\n", x0, xf, x_size);
    fprintf(f, "y = linspace(%f, %f, %ld);\n\n", y0, yf, y_size);

    dump_matrix(real_values, f, "real", y_size, x_size);
    dump_matrix(interp_values, f, "interpolated", y_size, x_size);
    dump_matrix(err_values, f, "err", y_size, x_size);

    fprintf(f, "figure();\nsurf(x, y, real);\nfigure();\nsurf(x, y, interpolated);\nfigure();\nsurf(x, y, err);\n");

    fclose(f);

    printf("Done!\n");
}
