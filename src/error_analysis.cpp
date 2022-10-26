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

std::complex<double> f(double t, double x0, double z0, double v0, double omega_plus, double omega_minus)
{
    const std::complex<double> imag_unit(0, 1);
    double A_plus = (v0 + omega_minus * x0) / (omega_minus - omega_plus);
    double A_minus = -(v0 + omega_plus * x0) / (omega_minus - omega_plus);
    std::complex<double> f_plus = A_plus * std::exp(-omega_plus * t * imag_unit);
    std::complex<double> f_minus = A_minus * std::exp(-omega_minus * t * imag_unit);
    return f_plus + f_minus;
}

int main()
{
    // particle parameters
    const double q = 1., m = 40.078;

    // trap parameters
    const double B0 = 96.5, V0 = 2.41 * 1e+6, d = 500;
    const bool mutual_interactions = false;

    // steps, boundary t values
    // const int n = 8000;
    const double t_max = 50., t_min = 0.; //, h = (t_max - t_min) / n;

    // initial values
    const double x0 = 20., z0 = 20., v0 = 25.;

    // analyticytical solution parameters
    const double omega0 = q * B0 / m, omega2_z = 2. * q * V0 / (m * d * d), discriminant = std::sqrt(omega0 * omega0 - 2. * omega2_z);
    const double omega_plus = (omega0 + discriminant) * 0.5, omega_minus = (omega0 - discriminant) * 0.5;
    std::complex<double> sol_analytic;
    long double x_analytic, y_analytic, z_analytic, err_rk4, err_fe;

    // print parameters
    const int width = 12;
    const int prec = 12;

    // define empty system of particles
    std::vector<Particle> particles;

    // create empty trap
    PenningTrap trap1(B0, V0, d, particles, mutual_interactions);
    PenningTrap trap2(B0, V0, d, particles, mutual_interactions);

    // add one particle to the trap
    Particle p_initial = Particle(q, m, arma::vec(std::to_string(x0) + " 0 " + std::to_string(z0)), arma::vec("0 " + std::to_string(v0) + " 0"));
    trap1.add_particle(p_initial);
    trap2.add_particle(p_initial);

    arma::vec steps = arma::vec("4000 8000 16000 32000");
    arma::vec delta_max_rk4 = arma::vec(steps.size()).fill(0.);
    arma::vec delta_max_fe = arma::vec(steps.size()).fill(0.);


    for (int k = 0; k <= steps.size()-1; k++)
    {
        // open file in order to save to file (t,x(t),y(t),z(t))
        std::string filename = "data/err_" + std::to_string((int)steps(k)) + ".txt";

        trap1.particles.at(0) = p_initial;
        trap2.particles.at(0) = p_initial;

        arma::vec delta_tmp_rk4 = arma::vec(steps(k)).fill(0.);
        arma::vec delta_tmp_fe = arma::vec(steps(k)).fill(0.);

        std::ofstream ofile;
        ofile.open(filename);

        // time vector
        arma::vec t(steps(k) + 1);

        //std::cout << "NEW NUMBER OF STEPS__________________________" << std::endl;
        // time loop
        t(0) = t_min;
        double h = (t_max - t_min) / steps(k);
        for (int i = 0; i < steps(k) - 1; i++)
        {

            t(i) = t_min + i * h;

            sol_analytic = f(t(i), x0, z0, v0, omega_plus, omega_minus);
            x_analytic = std::real(sol_analytic);
            y_analytic = std::imag(sol_analytic);
            z_analytic = z0 * cos(std::sqrt(omega2_z) * t(i));
            arma::vec r_analytic = arma::vec(std::to_string(x_analytic) + " " + std::to_string(y_analytic) + " " + std::to_string(z_analytic));

            trap1.evolve_RK4(h);
            trap2.evolve_forward_Euler(h);

            // relative error
            err_rk4 = arma::norm(trap1.particles[0].r - r_analytic) / norm(r_analytic);
            err_fe = arma::norm(trap2.particles[0].r - r_analytic) / norm(r_analytic);
            // absolute error
            delta_tmp_rk4(i) = arma::norm(trap1.particles[0].r - r_analytic);
            delta_tmp_fe(i) = arma::norm(trap2.particles[0].r - r_analytic);

            ofile << " " << scientific_format(t(i), width, prec)
                  << " " << scientific_format(err_rk4, width, prec)
                  << " " << scientific_format(err_fe, width, prec)
                  << std::endl;
        }
        // close file
        ofile.close();
        // save the max absolute error
        delta_max_rk4(k) = arma::max(delta_tmp_rk4);
        delta_max_fe(k) = arma::max(delta_tmp_fe);
        //std::cout << delta_max_rk4(k) << "  " << delta_max_fe(k) << std::endl;
    }
    double conv_rate_rk4 = 0., conv_rate_fe = 0.;

    double stepsizes_k = 0., stepsizes_k_ = 0.;

    for (int k = 1; k <= steps.size()-1; k++)
    {
        stepsizes_k = (t_max - t_min) / steps(k);
        stepsizes_k_ = (t_max - t_min) / steps(k - 1);
        //std::cout << "Stepsize   " << stepsizes_k << "    " << stepsizes_k_ << "    " <<std::log(stepsizes_k / stepsizes_k_) << std::endl;
        conv_rate_rk4 += std::log(delta_max_rk4(k) / delta_max_rk4(k - 1)) / ( (steps.size()-1) * std::log(stepsizes_k / stepsizes_k_));
        conv_rate_fe += std::log(delta_max_fe(k) / delta_max_fe(k - 1)) / ( (steps.size()-1) * std::log(stepsizes_k / stepsizes_k_));
        // std::cout << std::log(delta_max_rk4(k) / delta_max_rk4(k - 1)) / (3 * std::log(stepsizes_k / stepsizes_k_))<< " "<< std::log(delta_max_fe(k) / delta_max_fe(k - 1)) / (3 * std::log(stepsizes_k / stepsizes_k_)) << std::endl;
        //std::cout << std::log(stepsizes_k / stepsizes_k_) << std::endl;
    }

    std::cout << "CONVERGENCE RATE:" << std::endl
              << "RK4 " << conv_rate_rk4 << std::endl
              << "FE " << conv_rate_fe << std::endl;
    // all good
    return 0;
}