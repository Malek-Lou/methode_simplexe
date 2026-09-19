#ifndef RENDU_HPP
#define RENDU_HPP

#include "CollectionSimplexe.hpp"
#include "Fonction.hpp"

#include <string>

class Rendu
{
public:

    void afficher(
        const CollectionSimplexe& historique
    ) const;

    void sauvegarder1D(
        const CollectionSimplexe& historique,
        const Fonction& fonction,
        const std::string& nomFichier
    ) const;

    void sauvegarder(
        const CollectionSimplexe& historique,
        const Fonction& fonction,
        const std::string& nomFichier
    ) const;

    void exporterGnuplot(
        const CollectionSimplexe& historique,
        const std::string& nomFichier
    ) const;
};

#endif