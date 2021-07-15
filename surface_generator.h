#pragma once

#include <vector>
#include <functional>
#include <math.h>

class SurfaceGenerator
{
public:
    SurfaceGenerator(double x0, double xf, double y0, double yf, double h)
    {
        this->x0 = fmin(x0, xf);
        this->xf = fmax(x0, xf);
        this->y0 = fmin(y0, yf);
        this->yf = fmax(y0, yf);

        this->h = fabs(h);
        this->Nx = (this->xf - this->x0) / h;
        this->Ny = (this->yf - this->y0) / h;
    }

    std::vector<double> GenerateSurface(std::vector<double> &x, std::vector<double> &y, std::function<double(double, double)> f);
    void GenerateTrainer(std::vector<double>& x, std::vector<double>& y, std::vector<double>& z, std::function<double(double, double)> f);

private:
    double x0, xf, y0, yf, h, Nx, Ny;
};
