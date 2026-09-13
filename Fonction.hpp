#ifndef FONCTION_HPP
#define FONCTION_HPP

#include <vector>

class Fonction
{
public:

    // Calcule la valeur de la fonction au point donné
    virtual double evaluer(
        const std::vector<double>& point
    ) const = 0;

    // Destructeur virtuel
    virtual ~Fonction() = default;
};

#endif