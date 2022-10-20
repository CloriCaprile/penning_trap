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
    PenningTrap trap = PenningTrap() ;
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
    assert(trap3.B0 == 1);
    assert(trap3.V0 == 2);
    assert(trap3.d == 3);
    assert(all(trap3.particles.at(0).r == Particle(-1, 20, r2, v2).r));
    assert(all(trap3.particles.at(1).v == Particle(2, 10, -r2, -v2).v));
    assert(trap3.mutual_interactions == true);


    return 0;
}