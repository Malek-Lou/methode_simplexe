#ifndef POLYNOME_HPP
#define POLYNOME_HPP

#include "Fonction.hpp"
#include <vector>

class Polynome : public Fonction
{
private:
    std::vector<double> coefficients;
    std::vector<std::vector<int>> puissances;

public:
    Polynome(
        const std::vector<double>& coeffs,
        const std::vector<std::vector<int>>& puiss
    );

    double evaluer(const std::vector<double>& x) const override;
};

#endif