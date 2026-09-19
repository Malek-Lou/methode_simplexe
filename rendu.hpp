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

<<<<<<< HEAD
    void tracer2D(
=======
    void sauvegarder1D(
        const CollectionSimplexe& historique,
        const Fonction& fonction,
        const std::string& nomFichier
    ) const;

    void sauvegarder(
>>>>>>> c5d1116 (Ajout des rendus 1D et 2D et copie du simplexe)
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