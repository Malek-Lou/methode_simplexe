#ifndef FONCTION_HPP
#define FONCTION_HPP

#include <vector>

class Fonction
{
public:
    virtual double evaluer(
        const std::vector<double>& point
    ) const = 0;

    virtual ~Fonction() = default;
};

#endif