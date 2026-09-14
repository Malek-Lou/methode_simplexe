#ifndef RENDU_HPP
#define RENDU_HPP

#include "CollectionSimplexe.hpp"
#include <string>

class Rendu
{
public:
    Rendu();

    void afficher(
        const CollectionSimplexe& historique
    ) const;

    void tracer2D(
        const CollectionSimplexe& historique,
        const std::string& nomFichier
    ) const;
};

#endif
