#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <cassert>
#include <armadillo>
#include "useful.hpp"


// define global variable - electrostatic constant
#define k_e 138935.333

// Method that returns particle values in a string
// Format: "q m r_x r_y r_z v_x v_y v_z"
std::string Particle::info()
{
    std::string info_particle = std::to_string(q) + " " + std::to_string(m) +
                                " " + std::to_string(r(0)) + " " + std::to_string(r(1)) + " " + std::to_string(r(2)) + " " + std::to_string(v(0)) + " " + std::to_string(v(1)) + " " + std::to_string(v(2));
    return info_particle;
}

// Constructor of class PenningTrap
PenningTrap::PenningTrap(double B0_in, double V0_in, double d_in, std::vector<Particle> particles_in)
{
    // assign input values of magnetic field, potential and distance
    // takes vector of Particles as input
    B0 = B0_in;
    V0 = V0_in;
    d = d_in;
    particles = particles_in;
}

// Constructor 
PenningTrap::PenningTrap()
{
    B0 = 96.5;
    V0 = 9.65*1e+8;
    d = 1e+4;
    particles = p();

}


// Add a particle to the trap
void PenningTrap::add_particle(Particle p_in)
{
    particles.push_back(p_in);
}

// External electric field at point r=(x,y,z)
arma::vec PenningTrap::external_E_field(arma::vec r)
{
    double tmp = V0 / (d * d);
    arma::vec E = arma::vec(3);
    E(0) = tmp * r(0);
    E(1) = tmp * r(1);
    E(2) = -2 * tmp * r(2);
    return E;
}

// External magnetic field at point r=(x,y,z)
arma::vec PenningTrap::external_B_field(arma::vec r)
{
    arma::vec B = arma::vec(3).fill(0.0);
    B(2) = B0;
    return B;
}

// Force on particle_i from particle_j
arma::vec PenningTrap::force_particle(int i, int j)
{   
    if(i == j) //self interaction is not a thing here...
    {
        arma::vec zero = arma::vec(3).fill(0.);
        return zero;
    }
    else
    { 
    // take the two particles
    Particle p1 = particles.at(i);
    Particle p2 = particles.at(j);
    arma::vec F = arma::vec(3);
    // calcluate the difference vector
    arma::vec R = p1.r - p2.r;
    // ..its norm
    double s = sqrt(R(0) * R(0) + R(1) * R(1) + R(2) * R(2));
    // Coulomb interaction between the two particles
    F = k_e * p1.q * p2.q * R / (s * s * s);
    return F;
    }
}
// The total force on particle_i from the other particles
arma::vec PenningTrap::total_force_particles(int i)
{
    arma::vec F = arma::vec(3);
    //no need to skip i=j case because force_particle(i,i)=0 by design
    for (int j = 0; j < particles.size(); j++) 
    {
        F += force_particle(i, j);
    }

    return F;
}

// The total force on particle_i from the external fields
arma::vec PenningTrap::total_force_external(int i)
{
    Particle p = particles.at(i);
    arma::vec F = arma::vec(3);
    // Lorentz-Coulomb interaction
    F = p.q * external_E_field(p.r) + p.q * arma::cross(p.v, external_B_field(p.r));

    return F;
}

// The total force on particle_i from both external fields and other particles
arma::vec PenningTrap::total_force(int i)
{
    arma::vec F = arma::vec(3);
    F = total_force_external(i) + total_force_particles(i);
    return F;
}

// Evolve the system one time step (h) using Forward Euler
void PenningTrap::evolve_forward_Euler(double h)
{
    std::vector<Particle> new_state;
    for (int i = 0; i < particles.size(); i++)
    {
        // for every particle solve the coupled equations
        Particle p = particles.at(i);
        arma::vec tmp = arma::vec(3);
        tmp = p.v;

        // dv/dt = a/m  ==>  v_i+1 = v_i + h*F_i/m   
        p.v += total_force(i)*(h/p.m);
        // dr/dt = v ==> r_i+i = r_i + h*v_i
        p.r += h * tmp;

        //save changes in new state of the particle
        Particle p_new(p.q, p.m, p.r, p.v);

        // append the particle at t+dt at the end
        // of the new_state vector
        new_state.push_back(p_new);
    }
    // update the whole system with the new state at t+dt
    particles = new_state;
}
