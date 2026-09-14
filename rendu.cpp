#include "Rendu.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>

Rendu::Rendu()
{
}

void Rendu::afficher(
    const CollectionSimplexe& historique) const
{
    std::cout << "===== HISTORIQUE =====\n";

    for (std::size_t i = 0;
         i < historique.taille();
         ++i)
    {
        const Simplexe& simplexe =
            historique.getSimplexe(i);

        std::cout << "\nSimplexe "
                  << i << " :\n";

        for (std::size_t j = 0;
             j < simplexe.nombreNoeuds();
             ++j)
        {
            const std::vector<double>& point =
                simplexe.getNoeud(j);

            std::cout << "(";

            for (std::size_t k = 0;
                 k < point.size();
                 ++k)
            {
                std::cout << point[k];

                if (k + 1 < point.size())
                {
                    std::cout << ", ";
                }
            }

            std::cout << ")\n";
        }
    }
}

void Rendu::sauvegarder(
    const CollectionSimplexe& historique,
    const std::string& nomFichier) const
{
    std::ofstream fichier(nomFichier);

    if (!fichier)
    {
        throw std::runtime_error(
            "Impossible d'ouvrir le fichier."
        );
    }

    for (std::size_t i = 0;
         i < historique.taille();
         ++i)
    {
        const Simplexe& simplexe =
            historique.getSimplexe(i);

        fichier << "Simplexe " << i << "\n";

        for (std::size_t j = 0;
             j < simplexe.nombreNoeuds();
             ++j)
        {
            const std::vector<double>& point =
                simplexe.getNoeud(j);

            fichier << "(";

            for (std::size_t k = 0;
                 k < point.size();
                 ++k)
            {
                fichier << point[k];

                if (k + 1 < point.size())
                {
                    fichier << ", ";
                }
            }

            fichier << ")\n";
        }

        fichier << "\n";
    }
}
