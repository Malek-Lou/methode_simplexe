#include "CollectionSimplexe.hpp"

CollectionSimplexe::CollectionSimplexe()
{
}

void CollectionSimplexe::ajouter(const Simplexe& simplexe)
{
    simplexes.push_back(simplexe);
}

std::size_t CollectionSimplexe::taille() const
{
    return simplexes.size();
}

const Simplexe& CollectionSimplexe::getSimplexe(std::size_t i) const
{
    return simplexes.at(i);
}

void CollectionSimplexe::vider()
{
    simplexes.clear();
}
