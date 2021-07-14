#include "surface_generator.h"

void SurfaceGenerator::GenerateSurface(std::vector<double> &x, std::vector<double> &y, std::vector<double>& z, std::function<double(double, double)> f)
{
    double vx = this->x0;
    double vy = this->y0;
    while (vx <= this->xf)
    {
        x.push_back(vx);
        vx += this->h;
    }
    while (vy <= this->yf)
    {
        y.push_back(vy);
        vy += this->h;
    }

    long x_size = x.size();
    long y_size = y.size();
    for(long i = 0; i < y_size; i++)
    {
        for(long j = 0; j < x_size; j++)
        {
            vx = x.at(j);
            vy = y.at(i);
            double vz = f(vx, vy);
            z.push_back(vz);
        }
    }
}
