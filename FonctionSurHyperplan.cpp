#include "FonctionSurHyperplan.hpp"

#include <cmath>
#include <stdexcept>

FonctionSurHyperplan::FonctionSurHyperplan(
    const Fonction& fonctionOriginale,
    const std::vector<double>& coefficients,
    double secondMembre)
    : fonction(fonctionOriginale),
      normale(coefficients),
      constante(secondMembre),
      indicePivot(0)
{
    if (normale.size() < 2)
    {
        throw std::invalid_argument(
            "Un hyperplan utilise ici doit etre defini dans une dimension >= 2."
        );
    }

    // On choisit comme variable pivot celle dont le coefficient
    // est le plus grand en valeur absolue. Cela evite de diviser
    // par un coefficient tres petit.
    double meilleurCoefficient = 0.0;

    for (std::size_t i = 0; i < normale.size(); ++i)
    {
        double valeur = std::abs(normale[i]);

        if (valeur > meilleurCoefficient)
        {
            meilleurCoefficient = valeur;
            indicePivot = i;
        }
    }

    if (meilleurCoefficient < 1e-14)
    {
        throw std::invalid_argument(
            "Le vecteur normal de l'hyperplan ne peut pas etre nul."
        );
    }
}

std::vector<double> FonctionSurHyperplan::reconstruire(
    const std::vector<double>& parametres) const
{
    if (parametres.size() + 1 != normale.size())
    {
        throw std::invalid_argument(
            "Le nombre de parametres doit etre egal a n-1."
        );
    }

    std::vector<double> point(normale.size(), 0.0);

    std::size_t k = 0;
    double somme = 0.0;

    // Les n-1 variables non pivots sont les parametres libres.
    for (std::size_t i = 0; i < normale.size(); ++i)
    {
        if (i == indicePivot)
            continue;

        point[i] = parametres[k];
        somme += normale[i] * point[i];
        ++k;
    }

    // La variable pivot est imposee par l'equation de l'hyperplan.
    point[indicePivot] =
        (constante - somme) / normale[indicePivot];

    return point;
}

double FonctionSurHyperplan::evaluer(
    const std::vector<double>& parametres) const
{
    return fonction.evaluer(reconstruire(parametres));
}

int FonctionSurHyperplan::getDimensionOriginale() const
{
    return static_cast<int>(normale.size());
}

int FonctionSurHyperplan::getDimensionReduite() const
{
    return static_cast<int>(normale.size()) - 1;
}
