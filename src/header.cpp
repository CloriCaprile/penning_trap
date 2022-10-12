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

// define global variable - electrostatic constant
#define k_e 138935.333


// return a string in scientific notation
std::string scientific_format(double d, const int &width, const int &prec)
{
    std::stringstream s;
    s << std::setw(width) << std::setprecision(prec) << std::scientific << d;
    return s.str();
}

// Return a string with a vector<double> in scientific notation
std::string scientific_format(const std::vector<double> &v, const int &width, const int &prec)
{
    std::stringstream ss;
    for (double elem : v)
    {
        ss << scientific_format(elem, width, prec);
    }
    return ss.str();
}



