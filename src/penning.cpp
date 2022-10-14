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
#include "header.hpp"
#include "particle.hpp"
#include "penning.hpp"

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
PenningTrap::PenningTrap(const double B0_in, const double V0_in, const double d_in, const std::vector<Particle> particles_in, const bool mutual_int_in)
{
    // assign input values of magnetic field, potential and distance
    // takes vector of Particles as input
    B0 = B0_in;
    V0 = V0_in;
    d = d_in;
    particles = particles_in;
    mutual_interactions = mutual_int_in;
}

PenningTrap::PenningTrap(const double B0_in, const double V0_in, const double d_in, const std::vector<Particle> particles_in)
{
    // assign input values of magnetic field, potential and distance
    // takes vector of Particles as input
    B0 = B0_in;
    V0 = V0_in;
    d = d_in;
    particles = particles_in;
    mutual_interactions = true;
}

// Default Constructor
PenningTrap::PenningTrap()
{
    B0 = 96.5;
    V0 = 2.41 * 1e+6;
    d = 500;
    mutual_interactions = true;
}

// Constructor with number of random initial valued particles
PenningTrap::PenningTrap(const int N)
{
    B0 = 96.5;
    V0 = 2.41 * 1e+6;
    d = 500;
    // Set the seed for random number generator
    arma::arma_rng::set_seed_random();

    // Fill particles vector randomly
    for (int i = 0; i < N; i++)
    {
        Particle p = Particle();
        p.r = arma::vec(3).randn() * 0.1 * d;
        p.v = arma::vec(3).randn() * 0.1 * d;
        particles.push_back(p);
    }
    // Defualt: interactions are on
    mutual_interactions = true;
}

// Add a particle to the trap
void PenningTrap::add_particle(const Particle p_in)
{
    particles.push_back(p_in);
}

// External electric field at point r=(x,y,z)
arma::vec PenningTrap::external_E_field(const arma::vec r)
{
    if (norm(r) <= d)
    {
        double tmp = V0 / (d * d);
        arma::vec E = arma::vec(3);
        E(0) = tmp * r(0);
        E(1) = tmp * r(1);
        E(2) = -2 * tmp * r(2);
        return E;
    }
    else
        return arma::vec(3).fill(0.0);
}

// External magnetic field at point r=(x,y,z)
arma::vec PenningTrap::external_B_field(const arma::vec r)
{
    if (norm(r) <= d)
    {
        arma::vec B = arma::vec(3).fill(0.0);
        B(2) = B0;
        return B;
    }
    else
        return arma::vec(3).fill(0.0);
}

// Force on particle_i from particle_j
arma::vec PenningTrap::force_particle(const int i, const int j)
{
    if (i == j) // self interaction is not a thing here...
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
        double s = norm(R);
        // Coulomb interaction between the two particles
        F = k_e * p1.q * p2.q * R / (s * s * s);
        return F;
    }
}
// The total force on particle_i from the other particles
arma::vec PenningTrap::total_force_particles(const int i)
{
    if (mutual_interactions == false)
    {
        return arma::vec(3).fill(0.);
    }
    else
    {
        arma::vec F = arma::vec(3);
        // no need to skip i=j case because force_particle(i,i)=0 by design
        for (int j = 0; j < particles.size(); j++)
        {
            F += force_particle(i, j);
        }

        return F;
    }
}

// The total force on particle_i from the external fields
arma::vec PenningTrap::total_force_external(const int i)
{
    Particle p = particles.at(i);
    arma::vec F = arma::vec(3);
    // Lorentz-Coulomb interaction
    F = p.q * external_E_field(p.r) + p.q * arma::cross(p.v, external_B_field(p.r));

    return F;
}

// The total force on particle_i from both external fields and other particles
arma::vec PenningTrap::total_force(const int i)
{
    arma::vec F = arma::vec(3);
    F = total_force_external(i) + total_force_particles(i);
    return F;
}

// Evolve the system one time step (h) using Forward Euler
void PenningTrap::evolve_forward_Euler(const double h)
{
    std::vector<Particle> new_state;
    for (int i = 0; i < particles.size(); i++)
    {
        // for every particle solve the coupled equations
        Particle p = particles.at(i);
        arma::vec tmp = arma::vec(3);
        tmp = p.v;

        // dv/dt = a/m  ==>  v_i+1 = v_i + h*F_i/m
        p.v += total_force(i) * (h / p.m);
        // dr/dt = v ==> r_i+i = r_i + h*v_i
        p.r += h * tmp;

        // save changes in new state of the particle
        Particle p_new(p);

        // append the particle at t+dt at the end
        // of the new_state vector
        new_state.push_back(p_new);
    }
    // update the whole system with the new state at t+dt
    particles = new_state;
}

// Evolve the system one time step (h) using Runge-Kutta 4th order
void PenningTrap::evolve_RK4(const double h)
{
    std::vector<Particle> initial_state = particles, final_state;
    arma::mat kr_all1 = arma::mat(3, particles.size()).fill(0.);
    arma::mat kv_all1 = arma::mat(3, particles.size()).fill(0.);
    arma::mat kr_all2 = arma::mat(3, particles.size()).fill(0.);
    arma::mat kv_all2 = arma::mat(3, particles.size()).fill(0.);
    arma::mat kr_all3 = arma::mat(3, particles.size()).fill(0.);
    arma::mat kv_all3 = arma::mat(3, particles.size()).fill(0.);
    arma::mat kr_all4 = arma::mat(3, particles.size()).fill(0.);
    arma::mat kv_all4 = arma::mat(3, particles.size()).fill(0.);

    //k1
    for (int i = 0; i < particles.size(); i++)
    {
        kv_all1.col(i) = total_force(i) * h / particles.at(i).m;
        kr_all1.col(i) = h * particles.at(i).v;
    }


    for (int i = 0; i < particles.size(); i++)
    {
        particles.at(i).r += 0.5 * kr_all1.col(i);
        particles.at(i).v += 0.5 * kv_all1.col(i);
    }
    evolve_forward_Euler(0.5 * h);
    //k2
    for (int i = 0; i < particles.size(); i++)
    {
        kv_all2.col(i) = total_force(i) * h / particles.at(i).m;
        kr_all2.col(i) = h * particles.at(i).v;
    }


    particles = initial_state;
    for (int i = 0; i < particles.size(); i++)
    {
        particles.at(i).r += 0.5 * kr_all2.col(i);
        particles.at(i).v += 0.5 * kv_all2.col(i);
    }
    evolve_forward_Euler(0.5 * h);
    //k3
    for (int i = 0; i < particles.size(); i++)
    {
        kv_all3.col(i) = total_force(i) * h / particles.at(i).m;
        kr_all3.col(i) = h * particles.at(i).v;
    }

    particles = initial_state;

    for (int i = 0; i < particles.size(); i++)
    {
        particles.at(i).r += 1 * kr_all3.col(i);
        particles.at(i).v += 1 * kv_all3.col(i);
    }
    evolve_forward_Euler(0.5 * h);
    //k4
    for (int i = 0; i < particles.size(); i++)
    {
        kv_all4.col(i) = total_force(i) * h / particles.at(i).m;
        kr_all4.col(i) = h * particles.at(i).v;
    }

    for (int i = 0; i < particles.size(); i++)
    {
        final_state.at(i).r = initial_state.at(i).r + kr_all1.col(i)/6 + kr_all2.col(i)/3 + kr_all3.col(i)/3+ kr_all4.col(i)/6;
        final_state.at(i).v = initial_state.at(i).v + kv_all1.col(i)/6 + kv_all2.col(i)/3 + kv_all3.col(i)/3+ kv_all4.col(i)/6;
    }
    particles = final_state;
}

// Count the number of particles with |r| < d
int PenningTrap::count_particles_in()
{
    int cnt = 0;
    for (int i = 0; i < particles.size(); i++)
    {
        if (norm(particles[i].r) < d)
            cnt += 1;
    }
    return cnt;
}
