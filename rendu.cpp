#include "Rendu.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

Rendu::Rendu()
{
}

void Rendu::afficher(
    const CollectionSimplexe& historique) const
{
    for (std::size_t i = 0;
         i < historique.taille();
         ++i)
    {
        const Simplexe& s =
            historique.getSimplexe(i);

        std::cout << "\n===== ITERATION "
                  << i
                  << " =====\n";

        for (std::size_t j = 0;
             j < s.nombreNoeuds();
             ++j)
        {
            const std::vector<double>& p =
                s.getNoeud(j);

            std::cout << "Noeud " << j << " : ";

            for (std::size_t k = 0;
                 k < p.size();
                 ++k)
            {
                std::cout << p[k];

                if (k + 1 < p.size())
                    std::cout << ", ";
            }

            std::cout << '\n';
        }
    }
}


void Rendu::tracer2D(
    const CollectionSimplexe& historique,
    const std::string& nomFichier) const
{
    // ------------------------------------
    // Création du fichier de données
    // ------------------------------------

    std::ofstream fichier("historique.dat");

    if (!fichier)
    {
        throw std::runtime_error(
            "Impossible de créer historique.dat"
        );
    }

    for (std::size_t i = 0;
         i < historique.taille();
         ++i)
    {
        const Simplexe& s =
            historique.getSimplexe(i);

        // Un simplexe 2D possède 3 noeuds
        if (s.getDimension() != 2 ||
            s.nombreNoeuds() != 3)
        {
            continue;
        }

        // Triangle
        for (std::size_t j = 0;
             j < 3;
             ++j)
        {
            const std::vector<double>& p =
                s.getNoeud(j);

            fichier << p[0]
                    << " "
                    << p[1]
                    << '\n';
        }

        // Retour au premier point pour fermer
        // le triangle
        const std::vector<double>& p =
            s.getNoeud(0);

        fichier << p[0]
                << " "
                << p[1]
                << '\n';

        // Ligne vide entre deux triangles
        fichier << "\n\n";
    }

    fichier.close();


    // ------------------------------------
    // Création du script gnuplot
    // ------------------------------------

    std::ofstream script("trace.gnuplot");

    if (!script)
    {
        throw std::runtime_error(
            "Impossible de créer trace.gnuplot"
        );
    }

    script << "set terminal pngcairo size 1000,800\n";
    script << "set output '" << nomFichier << "'\n";

    script << "set title 'Evolution du simplexe - Nelder-Mead'\n";
    script << "set xlabel 'x'\n";
    script << "set ylabel 'y'\n";

    script << "set grid\n";
    script << "set key off\n";
    script << "set size ratio -1\n";

    script << "plot 'historique.dat' "
           << "using 1:2 "
           << "with lines "
           << "linewidth 2\n";

    script.close();


    // ------------------------------------
    // Exécution de gnuplot
    // ------------------------------------

    int resultat =
        std::system("gnuplot trace.gnuplot");

    if (resultat != 0)
    {
        std::cerr
            << "Erreur : gnuplot n'a pas pu "
            << "être exécuté."
            << std::endl;
    }
}"\n";
    }
}
