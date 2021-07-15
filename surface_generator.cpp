#include "surface_generator.h"

std::vector<double> SurfaceGenerator::GenerateSurface(std::vector<double>& x, std::vector<double>& y, std::function<double(double, double)> f)
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

    std::vector<double> z;
    for(long i = 0; i < y_size; i++)
    {
        for(long j = 0; j < x_size; j++)
        {
            vx = x[j];
            vy = y[i];
            double vz = f(vx, vy);
            z.push_back(vz);
        }
    }
    return z;
}

void SurfaceGenerator::GenerateTrainer(std::vector<double>& x, std::vector<double>& y, std::vector<double>& z, std::function<double(double, double)> f)
{

    double outer = this->y0;
    while(outer <= this->yf)
    {
        double inner = this->x0;
        while(inner <= this->xf)
        {
            x.push_back(outer);
            y.push_back(inner);
            z.push_back(f(outer, inner));
            inner += this->h;
        }
        outer += this->h;
    }

}

