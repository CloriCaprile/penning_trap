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
    int n = 100000;
    double t_max = 50., t_min = 0., h = (t_max - t_min) / n;

    // print parameters
    int width = 12;
    int prec = 12;

    // time vector
    arma::vec t(n + 1);

    // state vectors of the particle
    arma::vec r = arma::vec("20 0 20");
    arma::vec v = arma::vec("0 25 0");
    /*
    // initial values
    r(0) = 20;  // x0
    r(1) = 0; // y0
    r(2) = 20; // z0
    v(0) = 0; // vx_0
    v(1) = 25; // vy_0
    v(2) = 0;   // vz_0
    */

    // define one particle
    Particle p(q, m, r, v);

    // define empty system of particles
    std::vector<Particle> particles;

    // create empty trap
    PenningTrap trap(B0, V0, d, particles);

    // add one particle to the trap
    trap.add_particle(p);
    // and another one
    trap.add_particle(Particle(q, m, arma::vec("25 25 0"), arma::vec("0 40 5")) );


    // open file in order to save to file (t,x(t),y(t),z(t))
    std::string filename = "data2z_" + std::to_string(n) + ".txt";
    std::ofstream ofile;
    ofile.open(filename);

    // time loop
    t(0) = t_min;
    for (int i = 0; i < n + 1; i++)
    {
        t(i) = t_min + i * h;
        // save to file "t x(t) y(t) z(t)" of the single particle
        ofile << scientific_format(t(i), width, prec)
              << " " << scientific_format(trap.particles[0].r(2), width, prec)
              << " " << scientific_format(trap.particles[1].r(2), width, prec) << std::endl;
        trap.evolve_RK4(h);
    }

    // close file
    ofile.close();

    // all good
    return 0;
}