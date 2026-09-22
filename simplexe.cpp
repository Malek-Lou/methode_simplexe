#include "Simplexe.hpp"
#include <stdexcept>

Simplexe::Simplexe(int dim, const std::vector<std::vector<double>>& points)
    : dimension(dim), noeuds(points)
{
    // Un simplexe de dimension d possède d + 1 nœuds
    if (noeuds.size() != static_cast<std::size_t>(dimension + 1))
    {
        throw std::invalid_argument(
            "Un simplexe de dimension d doit avoir d+1 noeuds."
        );
    }

    // Chaque nœud doit avoir d coordonnées
    for (const auto& noeud : noeuds)
    {
        if (noeud.size() != static_cast<std::size_t>(dimension))
        {
            throw std::invalid_argument(
                "La dimension d'un noeud est incorrecte."
            );
        }
    }
}
Simplexe::Simplexe(const Simplexe& autre)
    : dimension(autre.dimension), noeuds(autre.noeuds)
{
}

int Simplexe::getDimension() const
{
    return dimension;
}

int Simplexe::nombreNoeuds() const
{
    return noeuds.size();
}

const std::vector<double>& Simplexe::getNoeud(int i) const
{
    return noeuds.at(i);
}
void Simplexe::setNoeud(
    int i,
    const std::vector<double>& point)
{
    if (point.size() != static_cast<std::size_t>(dimension))
    {
        throw std::invalid_argument(
            "Le point n'a pas la bonne dimension."
        );
    }

    noeuds.at(i) = point;
}
Simplexe& Simplexe::operator=(const Simplexe& autre)
{
    if (this != &autre)
    {
        dimension = autre.dimension;
        noeuds = autre.noeuds;
    }

    return *this;
}
