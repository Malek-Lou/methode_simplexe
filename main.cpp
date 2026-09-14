#include <iostream>

#include "Polynome.hpp"
#include "Simplexe.hpp"
#include "NelderMead.hpp"
#include "CollectionSimplexe.hpp"
#include "Rendu.hpp"


void afficherResultat(
    const std::string& nomFonction,
    const std::string& expression,
    const std::vector<double>& minimum,
    const std::vector<double>& minimumTheorique,
    const Polynome& fonction)
{
    std::cout << "Polynome : "
              << expression
              << std::endl;

    std::cout << "Minimum trouve : ";

    if (minimum.size() == 1)
    {
        std::cout << "x = "
                  << minimum[0];
    }
    else
    {
        std::cout << "(";

        for (size_t i = 0;
             i < minimum.size();
             ++i)
        {
            std::cout << minimum[i];

            if (i < minimum.size() - 1)
            {
                std::cout << ", ";
            }
        }

        std::cout << ")";
    }

    std::cout << std::endl;

    std::cout << "Minimum theorique : ";

    if (minimumTheorique.size() == 1)
    {
        std::cout << "x = "
                  << minimumTheorique[0];
    }
    else
    {
        std::cout << "(";

        for (size_t i = 0;
             i < minimumTheorique.size();
             ++i)
        {
            std::cout << minimumTheorique[i];

            if (i < minimumTheorique.size() - 1)
            {
                std::cout << ", ";
            }
        }

        std::cout << ")";
    }

    std::cout << std::endl;

    std::cout << nomFonction << "(";

    for (size_t i = 0;
         i < minimum.size();
         ++i)
    {
        std::cout << minimum[i];

        if (i < minimum.size() - 1)
        {
            std::cout << ", ";
        }
    }

    std::cout << ") = "
              << fonction.evaluer(minimum)
              << std::endl;

    std::cout << "------------------------"
              << std::endl;
}


int main()
{
    NelderMead nm;

    Rendu rendu;


    // ==================================================
    // TEST 1D
    // f(x) = 4 - 4x + x^2
    // ==================================================

    Polynome f1(
        {4, -4, 1},
        {
            {0},
            {1},
            {2}
        }
    );

    Simplexe s1(
        1,
        {
            {0},
            {5}
        }
    );

    std::vector<double> minimum1 =
        nm.minimiser(
            f1,
            s1,
            1000,
            0.000001
        );

    std::cout << "TEST 1D"
              << std::endl;

    afficherResultat(
        "f",
        "f(x) = 4 - 4x + x^2",
        minimum1,
        {2},
        f1
    );


    // ==================================================
    // TEST 2D
    // f(x,y) = 13 - 4x - 6y + x^2 + y^2
    // ==================================================

    Polynome f2(
        {13, -4, -6, 1, 1},
        {
            {0, 0},
            {1, 0},
            {0, 1},
            {2, 0},
            {0, 2}
        }
    );

    Simplexe s2(
        2,
        {
            {0, 0},
            {4, 0},
            {0, 6}
        }
    );

    std::vector<double> minimum2 =
        nm.minimiser(
            f2,
            s2,
            1000,
            0.000001
        );

    std::cout << "TEST 2D"
              << std::endl;

    afficherResultat(
        "f",
        "f(x,y) = 13 - 4x - 6y + x^2 + y^2",
        minimum2,
        {2, 3},
        f2
    );


    // ==================================================
    // HISTORIQUE DU TEST 2D
    // ==================================================

    const CollectionSimplexe& historique =
        nm.getHistorique();

    std::cout << std::endl;

    std::cout << "Nombre de simplexes dans "
              << "l'historique : "
              << historique.taille()
              << std::endl;

    // Affichage dans le terminal
    rendu.afficher(historique);

    // Sauvegarde dans un fichier
    rendu.sauvegarder(
        historique,
        "historique2D.txt"
    );


    // ==================================================
    // TEST 3D
    // ==================================================

    Polynome f3(
        {14, -2, -4, -6, 1, 1, 1},
        {
            {0, 0, 0},
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1},
            {2, 0, 0},
            {0, 2, 0},
            {0, 0, 2}
        }
    );

    Simplexe s3(
        3,
        {
            {0, 0, 0},
            {2, 0, 0},
            {0, 4, 0},
            {0, 0, 6}
        }
    );

    std::vector<double> minimum3 =
        nm.minimiser(
            f3,
            s3,
            1000,
            0.000001
        );

    std::cout << "TEST 3D"
              << std::endl;

    afficherResultat(
        "f",
        "f(x,y,z) = 14 - 2x - 4y - 6z + x^2 + y^2 + z^2",
        minimum3,
        {1, 2, 3},
        f3
    );


    return 0;
}
}
