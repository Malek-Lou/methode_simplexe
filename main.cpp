#include <iostream>
#include <vector>
#include "Simplexe.hpp"

int main()
{
    // Création d'un simplexe en dimension 2
    // 3 points = triangle
   
    std::vector<std::vector<double>> points =
    {
        {0.0, 0.0},
        {1.0, 0.0},
        {0.0, 1.0}
    };

    Simplexe s1(2, points);

// Utilisation du constructeur par copie
    Simplexe s2(s1);

    std::cout << "Dimension : "
              << s2.getDimension() << std::endl;

    std::cout << "Nombre de noeuds : "
              << s2.nombreNoeuds() << std::endl;

    for (int i = 0; i < s2.nombreNoeuds(); i++)
    {
        const auto& noeud = s2.getNoeud(i);

        std::cout << "Noeud " << i << " : ";

        for (double coord : noeud)
        {
            std::cout << coord << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}