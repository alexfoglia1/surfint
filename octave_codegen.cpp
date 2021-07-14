#include "octave_codegen.h"

#include <stdio.h>

void OctaveCodegen::GenerateCode(Eigen::MatrixXd real_values, Eigen::MatrixXd interp_values, double x_min, double x_max, double y_min, double y_max, double h)
{
    double x0 = fmin(x_min, x_max);
    double xf = fmax(x_min, x_max);
    double y0 = fmin(y_min, y_max);
    double yf = fmax(y_min, y_max);

    long x_size = (long) floorf(1.0 + ((x_max - x_min) / h));
    long y_size = (long) floorf(1.0 + ((y_max - y_min) / h));

    if (real_values.cols() != x_size)
    {
        printf("%% [WARNING] Unvalid number of columns: expected(%ld), actual(%ld)\n", x_size, real_values.cols());
    }
    if (real_values.rows() != y_size)
    {
        printf("%% [WARNING] Unvalid number of rows: expected(%ld), actual(%ld)\n", y_size, real_values.rows());
    }

    printf("x = linspace(%f, %f, %ld)\n", x0, xf, x_size);
    printf("y = linspace(%f, %f, %ld)\n\n", y0, yf, y_size);

    printf("real =\n[");
    for(long i = 0; i < y_size; i++)
    {
        printf("[");
        for(long j = 0; j < x_size; j++)
        {
            printf("%f, ", real_values(i, j));
        }
        printf("],\n");
    }
    printf("];\n");

    printf("interpolated =\n[");
    for(long i = 0; i < y_size; i++)
    {
        printf("[");
        for(long j = 0; j < x_size; j++)
        {
            printf("%f, ", interp_values(i, j));
        }
        printf("],\n");
    }
    printf("];\n");

    printf("err =\n[");
    for(long i = 0; i < y_size; i++)
    {
        printf("[");
        for(long j = 0; j < x_size; j++)
        {
            printf("%f, ", fabs(real_values(i, j) - interp_values(i, j)));
        }
        printf("],\n");
    }
    printf("];\n\n");


    printf("figure();\nsurf(x, y, real);\nfigure();\nsurf(x, y, interpolated);\nfigure();\nsurf(x, y, err);\n");
}