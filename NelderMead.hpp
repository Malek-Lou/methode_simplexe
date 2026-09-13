#ifndef NELDERMEAD_HPP
#define NELDERMEAD_HPP

#include "Simplexe.hpp"
#include "Fonction.hpp"

#include <vector>

class NelderMead
{
private:
    double alpha; // réflexion
    double gamma; // expansion
    double rho;   // contraction
    double sigma; // réduction

public:
    NelderMead();

    std::vector<double> minimiser(
        const Fonction& fonction,
        Simplexe simplexe,
        int maxIterations = 1000,
        double tolerance = 1e-8
    );
};

#endif