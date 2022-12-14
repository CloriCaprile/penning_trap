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
#include "particle.hpp"


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
    bool mutual_interactions;

    // Constructors
    PenningTrap(const double B0_in, const double V0_in, const double d_in, const std::vector<Particle> particles_in, bool mutual_interactions);
    PenningTrap(const int N, const double B0_in, const double V0_in, const double d_in, unsigned int seed, const bool mutual_interactions);
    PenningTrap(const double B0_in, const double V0_in, const double d_in, const std::vector<Particle> particles_in);
    //PenningTrap(const int N, const double B0_in, const double V0_in, const double d_in, const int seed);
    PenningTrap(const int N, const int seed);

    // Default Constructor
    PenningTrap();

    // Add a particle to the trap
    void add_particle(const Particle p_in);

    // External electric field at point r=(x,y,z)
    arma::vec external_E_field(const arma::vec r);

    // External magnetic field at point r=(x,y,z)
    arma::vec external_B_field(const arma::vec r);

    // Set the electric potential
    void set_V(const double V);

    // Force on particle_i from particle_j
    arma::vec force_particle(const int i,const  int j);

    // The total force on particle_i from the external fields
    arma::vec total_force_external(const int i);

    // The total force on particle_i from the other particles
    arma::vec total_force_particles(const int i);

    // The total force on particle_i from both external fields and other particles
    arma::vec total_force(const int i);

    // Evolve the system one time step (h) using Runge-Kutta 4th order
    void evolve_RK4(const double h);
    
    // Evolve the system one time step (h) using Forward Euler
    void evolve_forward_Euler(const double h);

    // Count the number of particles with |r| < d
    int count_particles_in(); 
};
#endif // end of include guard __penning_hpp__

