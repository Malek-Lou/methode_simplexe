#ifndef FONCTIONSURHYPERPLAN_HPP
#define FONCTIONSURHYPERPLAN_HPP

#include "Fonction.hpp"
#include <vector>
#include <cstddef>

// Restriction d'une fonction à un hyperplan :
// a_1 x_1 + ... + a_n x_n = b.
//
// L'hyperplan possède n-1 paramètres libres. Cette classe
// reconstruit le point de R^n correspondant, puis évalue la
// fonction d'origine en ce point.
class FonctionSurHyperplan : public Fonction
{
private:
    const Fonction& fonction;
    std::vector<double> normale;
    double constante;
    std::size_t indicePivot;

public:
    FonctionSurHyperplan(
        const Fonction& fonctionOriginale,
        const std::vector<double>& coefficients,
        double secondMembre
    );

    double evaluer(
        const std::vector<double>& parametres
    ) const override;

    std::vector<double> reconstruire(
        const std::vector<double>& parametres
    ) const;

    int getDimensionOriginale() const;
    int getDimensionReduite() const;
};

#endif
