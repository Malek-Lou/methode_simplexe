#ifndef RENDU_HPP
#define RENDU_HPP

#include "CollectionSimplexe.hpp"
#include <string>

class Rendu
{
public:
    Rendu();

    // Affiche l'historique dans le terminal
    void afficher(
        const CollectionSimplexe& historique
    ) const;

    // Sauvegarde les coordonnées dans un fichier
    void sauvegarder(
        const CollectionSimplexe& historique,
        const std::string& nomFichier
    ) const;
};

#endif
