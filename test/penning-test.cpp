#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cassert>
#include "header.hpp"
#include "particle.hpp"
#include "penning.hpp"

int main()
{

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

    // test add particle
    PenningTrap trap6 = PenningTrap(3, 42);
    assert(trap6.particles.size() == 3);
    trap6.particles.push_back(Particle(1.2, 27., arma::vec(3).fill(1.), arma::vec(3).fill(6.)));
    assert(trap6.particles.at(3).q == 1.2);
    assert(trap6.particles.at(3).m == 27.);
    assert(all(trap6.particles.at(3).r == arma::vec(3).fill(1.)));
    assert(all(trap6.particles.at(3).v == arma::vec(3).fill(6.)));

    // test electric field
    PenningTrap trap7 = PenningTrap();
    arma::vec E = trap7.external_E_field(arma::vec("0. 1. 1."));
    double tmp = trap.V0 / (trap.d * trap.d);
    assert(E(0) == 0);
    assert(E(1) == tmp);
    assert(E(2) == -2 * tmp);
    arma::vec R = arma::vec(3).fill(0.);
    R(2) = trap.d + 10.;
    arma::vec E2 = trap7.external_E_field(R);
    assert(all(E2 == arma::vec(3).fill(0.)));

    // test magnetic field
    PenningTrap trap8 = PenningTrap();
    arma::vec B = trap8.external_B_field(arma::vec("0. 1. 1."));
    assert(B(0) == 0);
    assert(B(1) == 0);
    assert(B(2) == trap8.B0);
    arma::vec R2 = arma::vec(3).fill(0.);
    R2(2) = trap.d + 10.;
    arma::vec B2 = trap8.external_E_field(R2);
    assert(all(B2 == arma::vec(3).fill(0.)));

    // test set_v
    trap8.set_V(232.);
    assert(trap8.V0 == 232.);

    // test force particle
    double k_e = 138935.333;
    arma::vec F = arma::vec(3);
    Particle p1 = trap6.particles.at(1);
    Particle p2 = trap6.particles.at(2);
    arma::vec R_ = p1.r - p2.r;
    double s = norm(R_);
    F = k_e * p1.q * p2.q * R_ / (s * s * s);
    assert(all(trap6.force_particle(1, 1) == arma::vec(3).fill(0.)));
    assert(all(trap6.force_particle(1, 2) == F));

    // test total force particles !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    trap6.mutual_interactions = false;
    assert(all(trap6.total_force_particles(1) == arma::vec(3).fill(0.)));
    trap6.mutual_interactions = true;
    arma::vec F_ = arma::vec(3).fill(0.);
    for (int j = 0; j < trap6.particles.size(); j++)
    {
        F_ += trap6.force_particle(1, j);
    }
    assert(all(trap6.total_force_particles(1) - F_ < 2.)); // questo non passa

    // test total force external
    Particle e = trap6.particles.at(1);
    assert(all(trap6.total_force_external(1) == e.q * trap6.external_E_field(e.r) + e.q * arma::cross(e.v, trap6.external_B_field(e.r))));

    // test total force !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    assert( all( trap6.total_force(1) - trap6.total_force_external(1) - trap6.total_force_particles(1) < 100.)); //questo non passa


    return 0;
}