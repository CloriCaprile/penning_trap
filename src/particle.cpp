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
