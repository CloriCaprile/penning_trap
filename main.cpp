#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "header.hpp"
#include "penning.hpp"
#include "particle.hpp"


int main()
{
    // particle parameters
    double q = 1.,  m = 40.078;

    // trap parameters
    double B0 = 96.5, V0 = 2.41 * 1e+6, d = 500;

    // steps, boundary t values
    int n = 10000;
    double t_max = 50., t_min = 0., h = (t_max - t_min) / n;

    // print parameters
    int width = 12;
    int prec = 12;

    // time vector
    arma::vec t(n + 1);

    // define empty system of particles
    std::vector<Particle> particles;

    // create empty trap
    PenningTrap trap(B0, V0, d, particles);

    // add one particle to the trap
    trap.add_particle(Particle(q, m, arma::vec("20 0 20"), arma::vec("0 25 0")) );
    // and another one
    trap.add_particle(Particle(q, m, arma::vec("25 25 0"), arma::vec("0 40 5")) );

    // open file in order to save to file (t,x(t),y(t),z(t))
    std::string filename = "data2part_" + std::to_string(n) + ".txt";
    std::ofstream ofile;
    ofile.open(filename);

    // time loop
    t(0) = t_min;
    for (int i_particle = 1; i_particle <= 2; i_particle++){
        for (int i = 0; i < n + 1; i++)
        {
            t(i) = t_min + i * h;
            // save to file "t x(t) y(t) z(t)" of the single particle
            ofile   << i_particle
                    << " " << scientific_format(t(i), width, prec)
                    << " " << scientific_format(trap.particles[0].r(0), width, prec)
                    << " " << scientific_format(trap.particles[0].r(1), width, prec)
                    << " " << scientific_format(trap.particles[0].r(2), width, prec)
                    << " " << scientific_format(trap.particles[0].v(0), width, prec)
                    << " " << scientific_format(trap.particles[0].v(1), width, prec)
                    << " " << scientific_format(trap.particles[0].v(2), width, prec) << std::endl;
            trap.evolve_RK4(h);
        }
    }

    // close file
    ofile.close();

    // all good
    return 0;
}