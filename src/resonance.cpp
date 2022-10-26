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
    // Set print parameters
    const int width = 12, prec = 12;

    // Set trap and time evolution parameters
    const int n = 16000, N = 100;
    const double    t_min = 0., 
                    t_max = 500., 
                    h = (t_max - t_min) / n,
                    B0 = 96.5,
                    V0 = 2.41 * 1e+6,
                    d = 500,

                    // Change for fine tuning
                    domegaV = 0.005,
                    // Change for different values of frequency
                    f = 0.7;

    // Set on/off interaction between particles               
    const bool mutual_interactions = true;
    double t = t_min, prog, V, n_particle=0, omegaV_min=1.0, omegaV_max = 1.1;


    //Set file name
    std::string interact_str = mutual_interactions ? "int_" : "nonint_";
    std::string filename = "resonance" + interact_str + std::to_string(f) + "_" + std::to_string(domegaV) + ".txt";
    std::ofstream ofile;
    ofile.open(filename);

    PenningTrap trap(N, B0, V0, d, 42, mutual_interactions);
    std::vector<Particle> particles0{trap.particles};

    // Angular frequancy loop
    for (double omegaV = omegaV_min; omegaV <= omegaV_max; omegaV += domegaV){
        // Sets time and particles to zero for each omega iteration
        trap.particles = particles0;
        t=0;
        std::cout << "Now calculating " << scientific_format(omegaV, 3, 4) << "  "<<std::endl;

        //time loop
        for (int i = 0; i < n + 1; i++){
            // Set a time dependent potential
            V = V0*(1.+f*std::cos(omegaV*t));
            trap.set_V(V);

            // Prints progression of code
            prog = 100.*i/n;
            std::cout <<"Loading... " << std::setprecision(3) <<prog <<"%                   \r";

            // Evolves the trap and update t
            trap.evolve_RK4(h);
            t += h;
        }
        // Counts number of particles inside trap
        n_particle = trap.count_particles_in();

         // Save to file data: omegaV, number of particles
        ofile   << scientific_format(omegaV, width, prec)    << " " 
                << scientific_format(n_particle, width, prec)<<std::endl;

        // Print on terminal n_particles 4 each iteration
        std::cout << "==> Particles still inside: " << n_particle << std::endl;
    }
    std::cout  <<"Completed!    " <<"100%       " <<std::endl;

    // close file
    ofile.close();

    return 0;
}
