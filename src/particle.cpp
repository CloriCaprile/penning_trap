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


// Constructor of the class Particle
Particle::Particle(double q_in, double m_in, arma::vec r_in, arma::vec v_in)
{
    // assign values of charge, mass, position and velocity
    q = q_in;
    m = m_in;
    r = r_in;
    v = v_in;
}

Particle::Particle()
{
    // assign values of charge, mass, position and velocity
    q = 1;
    m = 40.078;
    r = arma::vec(3).fill(0.);
    v = arma::vec(3).fill(0.);
}

Particle::Particle(const Particle &other): q{other.q}, m{other.m}, r{other.r}, v{other.v} {}

Particle Particle::operator=(const Particle &other) {
    q = other.q;
    m = other.m;
    r = other.r;
    v = other.v;
    return *this;
}

// Method that returns particle values in a string
// Format: "q m r_x r_y r_z v_x v_y v_z"
std::string Particle::info()
{
    std::string info_particle = std::to_string(q) + " " + std::to_string(m) +
                                " " + std::to_string(r(0)) + " " + std::to_string(r(1)) + " " + std::to_string(r(2)) + " " + std::to_string(v(0)) + " " + std::to_string(v(1)) + " " + std::to_string(v(2));
    return info_particle;
}