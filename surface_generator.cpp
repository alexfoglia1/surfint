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
            vx = x.at(j);
            vy = y.at(i);
            double vz = f(vx, vy);
            z.push_back(vz);
        }
    }
    return z;
}

void SurfaceGenerator::GenerateTrainer(std::vector<double>& x, std::vector<double>& y, std::vector<double>& z, std::function<double(double, double)> f)
{
    int x_size = (int) floorf(1.0 + this->Nx);
    int y_size = (int) floorf(1.0 + this->Ny);

    for (int i = 0; i < y_size * x_size; i++)
    {
        x.push_back(0.0);
        y.push_back(0.0);
        z.push_back(0.0);
    }

    double outer = this->y0;
    for (int i = 0; i < y_size; i++)
    {
        double inner = this->x0;
        for (int j = 0; j < x_size; j++)
        {
            x[i * x_size + j] = outer;
            y[i * x_size + j] = inner;
            z[i * x_size + j] = f(x[i], y[i]);
            inner += this->h;
        }
        outer += this->h;
    }
}

