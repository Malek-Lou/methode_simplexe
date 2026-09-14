#ifndef COLLECTIONSIMPLEXE_HPP
#define COLLECTIONSIMPLEXE_HPP

#include "Simplexe.hpp"
#include <vector>

class CollectionSimplexe
{
private:
    std::vector<Simplexe> simplexes;

public:
    CollectionSimplexe();

    // Ajoute une copie du simplexe
    void ajouter(const Simplexe& simplexe);

    // Retourne le nombre de simplexes
    std::size_t taille() const;

    // Accède à un simplexe
    const Simplexe& getSimplexe(std::size_t i) const;

    // Supprime tout l'historique
    void vider();
};

#endif
