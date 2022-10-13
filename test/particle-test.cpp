#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cassert>
#include "header.hpp"
#include "particle.hpp"



int main(){

    // test default constructor
    Particle p;
    assert(p.q == 1);
    assert(p.m == 40.078);
    assert(all(p.r == arma::vec(3).fill(0.)));
    assert(all(p.v == arma::vec(3).fill(0.)));

    // test copy constructor
    Particle p_copy(p);
    assert(p_copy.q == 1);
    assert(p_copy.m == 40.078);
    assert(all(p_copy.r == arma::vec(3).fill(0.)));
    assert(all(p_copy.v == arma::vec(3).fill(0.)));
    p.q = 2;
    assert(p_copy.q == 1); //check deep copy
    p.q = 1;

    // test constructor
    arma::vec r = arma::vec(3).fill(1.); 
    arma::vec v = arma::vec(3).fill(3.);
    Particle e(-1, 20, r, v);
    assert(e.q == -1);
    assert(e.m == 20);
    assert(all(e.r == r));
    assert(all(e.v == v));

    // test operator=
    e = p;
    assert(e.q == 1);
    assert(e.m == 40.078);
    assert(all(e.r == arma::vec(3).fill(0.)));
    assert(all(e.v == arma::vec(3).fill(0.)));

    return 0;
}