#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <complex>
#include <cmath>
#include "header.hpp"
#include "penning.hpp"
#include "particle.hpp"


std::complex<double> f(double t, double x0, double z0, double v0, double omega_plus, double omega_minus){
    const std::complex<double> imag_unit(0,1);
    double A_plus = (v0 + omega_minus*x0)/(omega_minus - omega_plus);
    double A_minus = -(v0 + omega_plus*x0)/(omega_minus - omega_plus);
    std::complex<double> f_plus = A_plus*std::exp(-omega_plus*t*imag_unit);
    std::complex<double> f_minus = A_minus*std::exp(-omega_minus*t*imag_unit);
    return f_plus + f_minus;
}


int main()
{
    // particle parameters
    const double q = 1.,  m = 40.078;

    // trap parameters
    const double B0 = 96.5, V0 = 2.41 * 1e+6, d = 500;
    const bool mutual_interactions = false;

    // initial values
    const double x0 = 20., z0 = 20., v0 = 25.;
    const double t_max = 50., t_min = 0.;

    // analytical solution parameters
    const double omega0 = q*B0/m, omega2_z = 2.*q*V0/(m*d*d), discriminant=std::sqrt(omega0*omega0 - 2.*omega2_z);
    const double omega_plus = (omega0+discriminant)*0.5, omega_minus = (omega0-discriminant)*0.5;
    std::complex<double> sol_anal;
    double x_anal, y_anal, z_anal, erel_rk4, erel_fe, err_rk4, err_fe;


    // print parameters
    const int width = 12;
    const int prec = 12;

    // define empty system of particles
    std::vector<Particle> particles;

    // create empty trap
    PenningTrap trap1(B0, V0, d, particles, mutual_interactions);
    PenningTrap trap2(B0, V0, d, particles, mutual_interactions);

    // add one particle to the trap
    trap1.add_particle(Particle(q, m, arma::vec(std::to_string(x0)+" 0 "+ std::to_string(z0)), arma::vec("0 "+std::to_string(v0)+" 0")) );
    trap2.add_particle(Particle(q, m, arma::vec(std::to_string(x0)+" 0 "+ std::to_string(z0)), arma::vec("0 "+std::to_string(v0)+" 0")) );
    
    // convergence
    const int k_max = 4;
    arma::Mat<double> Delta(3,k_max);

    // steps, boundary t values
    for (int k=0, n=4000; k<k_max; n*=2, k++){
        const double h = (t_max - t_min) / n;

        // open file in order to save to file (t,x(t),y(t),z(t))
        std::string filename = "err_"+ std::to_string(n) + ".txt";

        std::ofstream ofile;
        ofile.open(filename);

        // time vector
        arma::vec t(n + 1);

        // time loop
        t(0) = t_min;

        for (int i = 0; i < n + 1; i++){
            t(i) = t_min + i * h;

            sol_anal = f(t(i), x0, z0, v0, omega_plus, omega_minus);
            x_anal = std::real(sol_anal);
            y_anal = std::imag(sol_anal);
            z_anal = z0*cos(std::sqrt(omega2_z)*t(i));
        
            trap1.evolve_RK4(h);
            trap2.evolve_forward_Euler(h);
            err_rk4 = norm(trap1.particles[0].r - arma::vec(std::to_string(x_anal)+" " +std::to_string(y_anal)+ " " + std::to_string(z_anal)));
            err_fe = norm(trap2.particles[0].r - arma::vec(std::to_string(x_anal)+" " +std::to_string(y_anal)+ " " + std::to_string(z_anal)));

            erel_rk4 = err_rk4/norm(arma::vec(std::to_string(x_anal)+" " +std::to_string(y_anal)+ " " + std::to_string(z_anal)));
            erel_fe = err_fe/norm(arma::vec(std::to_string(x_anal)+" " +std::to_string(y_anal)+ " " + std::to_string(z_anal)));

            ofile   << " " << scientific_format(t(i), width, prec)
                    << " " << scientific_format(erel_rk4, width, prec)
                    << " " << scientific_format(erel_fe, width, prec)
                    << std::endl;

            Delta(0, k) = h;
            if (Delta(1, k) < err_rk4) Delta(1, k) = err_rk4;
            if (Delta(2, k) < err_fe) Delta(2, k) = err_fe;
        }

        // close file
        ofile.close();
    }

    // error convergence rate
    double r_err_rk4 = 0., r_err_fe = 0.;
    for (int k=1; k<k_max; k++){
        r_err_rk4 += std::log(Delta(1,k)/Delta(1,k-1)) / std::log(Delta(0,k)/Delta(0,k-1));
        r_err_fe += std::log(Delta(2,k)/Delta(2,k-1)) / std::log(Delta(0,k)/Delta(0,k-1));
    }
    r_err_rk4 /= (k_max-1);
    r_err_fe /= (k_max-1);

    std::cout   <<"\nERROR CONVERGENCE RATE\n-----------------------------------\nRungeKutta4\t: r_err = " 
                <<r_err_rk4 
                <<"\nForwardEuler\t: r_err = " 
                <<r_err_fe
                <<"\n"<<std::endl;

    // all good
    return 0;
}