// simulation for overdamped particle in heat bath

// used headers and libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

// --------------------------------------------------------------------------------------------------------------------------------

// number of steps
int const N = (int)1e6;
// diffusion coefficient (= kT <--> mu = 1)
double const D = 1.5;
// coefficient for the potential
double const alpha = 0.1;
// initial condition
double const x0 = 100.;
// stepsize
double const eps = 10;
// filen name
std::string fileName = "data0.txt";

// --------------------------------------------------------------------------------------------------------------------------------

// draw from normal distribution to generate uncorrelatex random noise (eta)
auto GaussianNoise = [&](double const &D, double const &eps) {
    // random number generation
    std::random_device rd{};
    std::mt19937 gen(rd());
    // normal distribution with 0 mean and given standard deviation
    std::normal_distribution<double> distr(0, std::sqrt(2 * D * eps));

    // return random number
    return distr(gen);
};

// --------------------------------------------------------------------------------------------------------------------------------

// derivative of V potential
auto PotentialDerivative = [&](double const &x, double const &alpha)
{
    // separate cases
    if (x < 0.)
        return -alpha;
    else if (x > 0.)
        return alpha;
    // special case: x = 0 is not defined --> taking average of x > 0 and x < 0 --> 0
    else
        return 0.;
};

// --------------------------------------------------------------------------------------------------------------------------------

// stepper
auto Stepper = [&](double &x, double const &eps, double const &alpha, double const &D) {
    // update x value
    x += -PotentialDerivative(x, alpha) + GaussianNoise(D, eps);
};

// --------------------------------------------------------------------------------------------------------------------------------

// main function
int main(int, char **)
{
    // set initial condition
    double x = x0;
    // write data to file
    std::ofstream data;
    data.open(fileName);
    // simulation
    for (int i = 0; i < N; i++)
    {
        data << x << std::endl;
        Stepper(x, eps, alpha, D);
    }
    data.close();
}
