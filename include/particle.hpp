// include guard
#ifndef __particle_hpp__
#define __particle_hpp__

// include headers
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <armadillo>



// Particle class
// 4 member variables: q charge, m mass, r position and v velocity
class Particle
{
public:
    // values of the particle
    double q;
    double m;
    arma::vec r = arma::vec(3);
    arma::vec v = arma::vec(3);
    // constructor
    Particle(double q_in, double m_in, arma::vec r_in, arma::vec v_in);
    // default constructor
    Particle();
    // copy constructor
    Particle(const Particle &other);
    
    Particle operator=(const Particle &other);

    // Method that returns particle values in a string
    // Format: "q m r_x r_y r_z v_x v_y v_z"
    std::string info();
};


#endif // end of include guard 
