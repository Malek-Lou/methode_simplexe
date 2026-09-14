#include "Polynome.hpp"
#include <stdexcept>
#include <cmath>

Polynome::Polynome(
    const std::vector<double>& coeffs,
    const std::vector<std::vector<int>>& puiss
)
    : coefficients(coeffs), puissances(puiss)
{
    if (coefficients.size() != puissances.size())
    {
        throw std::invalid_argument(
            "Le nombre de coefficients et de termes doit etre identique."
        );
    }
}

double Polynome::evaluer(const std::vector<double>& x) const
{
    double resultat = 0.0;

    for (size_t i = 0; i < coefficients.size(); ++i)
    {
        if (puissances[i].size() != x.size())
        {
            throw std::invalid_argument(
                "La dimension du polynome ne correspond pas au point."
            );
        }

        double terme = coefficients[i];

        for (size_t j = 0; j < x.size(); ++j)
        {
            terme *= std::pow(x[j], puissances[i][j]);
        }

        resultat += terme;
    }

    return resultat;
}