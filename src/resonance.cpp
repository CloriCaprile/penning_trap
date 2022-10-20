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

    const int n = 16000, N = 100;
    const double    t_min = 0., 
                    t_max = 500., 
                    h = (t_max - t_min) / n,
                    B0 = 96.5,
                    V0 = 2.41 * 1e+6,
                    d = 500,
                    domegaV = 0.02,
                    f = 0.1;
    const bool mutual_interactions = false;
    double t = t_min, prog, V, n_particle=0, omegaV_min=0.2, omegaV_max = 2.5;

    PenningTrap trap(N, B0, V0, d, 1, mutual_interactions);
    //std::cout <<trap.count_particles_in()<<std::endl;
    std::string filename = "resonance_"+ std::to_string(f) + ".txt";
    std::ofstream ofile;
    ofile.open(filename);


    //#pragma omp parallel for
    for (double omegaV = omegaV_min; omegaV <= omegaV_max; omegaV += domegaV){
        t=0;
        std::cout << "Now calculating " << scientific_format(omegaV, 3, 3) << "  "<<std::endl;
        for (int i = 0; i < n + 1; i++){
            
            
            V = V0*(1.+f*cos(omegaV*t));
            trap.set_V(V);

            prog = 100*i/n;
            std::cout <<"Loading... " << std::setprecision(3) <<prog <<"%                   \r";
            trap.evolve_RK4(h);
            t += h;
        }
        n_particle = trap.count_particles_in();
        ofile   << scientific_format(omegaV, width, prec)    << " " 
                << scientific_format(n_particle, width, prec)<<std::endl;

        std::cout << "==> Particles still inside: " << n_particle << std::endl;
    }
    std::cout  <<"Completed!    " <<"100%       " <<std::endl;

    // close file
    ofile.close();

    return 0;
}