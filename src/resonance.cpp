#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <complex>
#include <cmath>
#include "header.hpp"
#include "penning.hpp"
#include "particle.hpp"


int main(){
    const int width = 12, prec = 12;

    const int n = 100, N = 100;
    const double    t_min = 0., 
                    t_max = 500., 
                    h = (t_max - t_min) / n,
                    B0 = 96.5,
                    V0 = 2.41 * 1e+6,
                    d = 500,
                    domegaV = 0.02,
                    f = 0.7;
    const bool mutual_interactions = false;
    double t = t_min, prog, V, n_particle, omegaV=0.2;

    PenningTrap trap(N, B0, V0, d, mutual_interactions, 42);
    //std::cout <<trap.count_particles_in()<<std::endl;
    std::string filename = "resonance_"+ std::to_string(f) + ".txt";
    std::ofstream ofile;
    ofile.open(filename);

    double imax = 2.3/domegaV;

    #pragma omp parallel for
    for (int j = 0; j < imax; j++){
        omegaV += domegaV;
        prog = 0;
        for (int i = 0; i < n + 1; i++){
            t += h;
            V = V0*(1.+f*cos(omegaV*t));
            
            trap.set_V(V);

            prog += 100*h/n;
            std::cout <<"Loading... " << std::setprecision(3) <<prog <<"%                   \r";
            trap.evolve_RK4(h);
        }
        n_particle = trap.count_particles_in();
        ofile   << scientific_format(omegaV, width, prec)    << " " 
                << scientific_format(n_particle, width, prec)<<std::endl;
    }
    std::cout  <<"Completed!    " <<"100%       " <<std::endl;

    // close file
    ofile.close();

    return 0;
}