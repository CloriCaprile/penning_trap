#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cassert>
#include "header.hpp"
#include "particle.hpp"
#include "penning.hpp"

void test_constructors(){
    // test default constructor
    PenningTrap trap = PenningTrap();
    assert(trap.B0 == 96.5);
    assert(trap.V0 == 2.41 * 1e+6);
    assert(trap.d == 500);
    assert(trap.mutual_interactions == true);

    // test constructor
    std::vector<Particle> particles;
    arma::vec r = arma::vec(3).fill(1.);
    arma::vec v = arma::vec(3).fill(3.);
    particles.push_back(Particle(-1, 20, r, v));
    particles.push_back(Particle(2, 10, -r, -v));
    PenningTrap trap2 = PenningTrap(1., 2., 3., particles, true);
    assert(trap2.B0 == 1);
    assert(trap2.V0 == 2);
    assert(trap2.d == 3);
    assert(all(trap2.particles.at(0).r == Particle(-1, 20, r, v).r));
    assert(all(trap2.particles.at(1).v == Particle(2, 10, -r, -v).v));
    assert(trap2.mutual_interactions == true);

    // test constructor
    std::vector<Particle> particles2;
    arma::vec r2 = arma::vec(3).fill(1.);
    arma::vec v2 = arma::vec(3).fill(3.);
    particles2.push_back(Particle(-1, 20, r2, v2));
    particles2.push_back(Particle(2, 10, -r2, -v2));
    PenningTrap trap3 = PenningTrap(1., 2., 3., particles2);
    assert(trap3.B0 == 1.);
    assert(trap3.V0 == 2.);
    assert(trap3.d == 3.);
    assert(all(trap3.particles.at(0).r == Particle(-1, 20, r2, v2).r));
    assert(all(trap3.particles.at(1).v == Particle(2, 10, -r2, -v2).v));
    assert(trap3.mutual_interactions == true);

    // test constructor random
    PenningTrap trap4 = PenningTrap(3, 1., 2., 3., 42, true);
    assert(trap4.particles.size() == 3);
    assert(trap4.B0 == 1.);
    assert(trap4.V0 == 2.);
    assert(trap4.d == 3.);
    assert(trap4.mutual_interactions == true);

    // test constructor random 2
    PenningTrap trap5 = PenningTrap(3, 42);
    assert(trap5.particles.size() == 3);
    assert(trap5.B0 == 96.5);
    assert(trap5.V0 == 2.41 * 1e+6);
    assert(trap5.d == 500);
    assert(trap5.mutual_interactions == true);
}

void  test_add_particle(){
    // test add particle
    PenningTrap trap = PenningTrap(3, 42);
    assert(trap.particles.size() == 3);
    trap.particles.push_back(Particle(1.2, 27., arma::vec(3).fill(1.), arma::vec(3).fill(6.)));
    assert(trap.particles.at(3).q == 1.2);
    assert(trap.particles.at(3).m == 27.);
    assert(all(trap.particles.at(3).r == arma::vec(3).fill(1.)));
    assert(all(trap.particles.at(3).v == arma::vec(3).fill(6.)));
}

void test_fields(){
    // test electric field
    PenningTrap trapE = PenningTrap();
    arma::vec E = trapE.external_E_field(arma::vec("0. 1. 1."));
    double V0_tmp = 2.41 * 1e+6, d_tmp = 500, E_tmp = V0_tmp/(d_tmp*d_tmp);
    assert(E(0) == 0);
    assert(E(1) == E_tmp);
    assert(E(2) == -2 * E_tmp);
    arma::vec R = arma::vec(3).fill(0.);
    // field is zero outside the trap
    R(2) = d_tmp + 10.;
    arma::vec E2 = trapE.external_E_field(R);
    assert(all(E2 == arma::vec(3).fill(0.)));

    // test magnetic field
    PenningTrap trapB = PenningTrap();
    arma::vec B = trapB.external_B_field(arma::vec("0. 1. 1."));
    assert(B(0) == 0);
    assert(B(1) == 0);
    assert(B(2) == trapB.B0);
    // field is zero outside the trap
    arma::vec B2 = trapB.external_B_field(R);
    assert(all(B2 == arma::vec(3).fill(0.)));

    // test set_v
    trapB.set_V(232.);
    assert(trapB.V0 == 232.);
}

void test_forces(){
    // test force particle
    double k_e = 138935.333;
    arma::vec F = arma::vec(3);
    PenningTrap trap = PenningTrap(3, 42);
    trap.particles.push_back(Particle(1.2, 27., arma::vec(3).fill(1.), arma::vec(3).fill(6.)));
    Particle p1 = trap.particles.at(1);
    Particle p2 = trap.particles.at(2);
    arma::vec R_ = p1.r - p2.r;
    double s = norm(R_);
    F = k_e * p1.q * p2.q * R_ / (s * s * s);
    assert(all(trap.force_particle(1, 1) == arma::vec(3).fill(0.)));
    assert(all(trap.force_particle(1, 2) == F));
    
    // test total force particles
    arma::vec F_tmp = arma::vec(3).fill(0.);
    trap.mutual_interactions = false;
    assert(all(trap.total_force_particles(1) == F_tmp));
    trap.mutual_interactions = true;
    for (int j = 0; j < trap.particles.size(); j++)
    {
        F_tmp += trap.force_particle(1, j);
    }
    assert(all(trap.total_force_particles(1) == F_tmp));

    // test total force external
    Particle e = trap.particles.at(1);
    assert(all(trap.total_force_external(1) == e.q * trap.external_E_field(e.r) + e.q * arma::cross(e.v, trap.external_B_field(e.r))));

    // test total force
    assert( all( trap.total_force(1) - trap.total_force_particles(1) == e.q * trap.external_E_field(e.r) + e.q * arma::cross(e.v, trap.external_B_field(e.r))  ));
}

int main()
{
    test_constructors();
    test_add_particle();
    test_fields();
    test_forces();

    return 0;
}