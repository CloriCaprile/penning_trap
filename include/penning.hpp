// include guard
#ifndef __penning_hpp__
#define __penning_hpp__


// include headers
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <armadillo>


// Penning trap simulator.
// The class contains the current state of the system
// using member functions of the class.
// Two different methods of evolving the state by a single time step.
class PenningTrap
{
public:
    // Member variables
    double B0, V0, d;
    std::vector<Particle> particles;

    // Constructor
    PenningTrap(double B0_in, double V0_in, double d_in, std::vector<Particle> particles_in);
    // Constructor
    PenningTrap();

    // Add a particle to the trap
    void add_particle(Particle p_in);

    // External electric field at point r=(x,y,z)
    arma::vec external_E_field(arma::vec r);

    // External magnetic field at point r=(x,y,z)
    arma::vec external_B_field(arma::vec r);

    // Force on particle_i from particle_j
    arma::vec force_particle(int i, int j);

    // The total force on particle_i from the external fields
    arma::vec total_force_external(int i);

    // The total force on particle_i from the other particles
    arma::vec total_force_particles(int i);

    // The total force on particle_i from both external fields and other particles
    arma::vec total_force(int i);

    // Evolve the system one time step (h) using Runge-Kutta 4th order
    void evolve_RK4(double h);
    
    // Evolve the system one time step (h) using Forward Euler
    void evolve_forward_Euler(double h);
};
#endif // end of include guard __penning_hpp__

