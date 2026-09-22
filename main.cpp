#include <iostream>

#include "Polynome.hpp"
#include "Simplexe.hpp"
#include "NelderMead.hpp"
#include "CollectionSimplexe.hpp"
#include "Rendu.hpp"
#include "FonctionSurHyperplan.hpp"


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
    // f(x) = 4 - 4x + x^2 = (x - 2)^2
    // Minimum theorique : x = 2
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

    std::cout << std::endl;
    std::cout << "========== TEST 1D =========="
              << std::endl;

    afficherResultat(
        "f",
        "f(x) = 4 - 4x + x^2",
        minimum1,
        {2},
        f1
    );


    // --------------------------------------------------
    // Rendu du test 1D
    // IMPORTANT : on le sauvegarde avant de lancer
    // le test 2D car NelderMead efface son historique
    // au debut de chaque minimisation.
    // --------------------------------------------------

    const CollectionSimplexe& historique1D =
        nm.getHistorique();

    std::cout
        << "Nombre de simplexes 1D : "
        << historique1D.taille()
        << std::endl;

    rendu.sauvegarder1D(
        historique1D,
        f1,
        "historique1D.svg"
    );


    // ==================================================
    // TEST 2D
    //
    // f(x,y)
    // = 13 - 4x - 6y + x^2 + y^2
    // = (x - 2)^2 + (y - 3)^2
    //
    // Minimum theorique : (2,3)
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

    // Demonstration explicite du constructeur par copie
    // et de l'operateur d'affectation.
    Simplexe copieS2(s2);

    Simplexe affectationS2(
        2,
        {
            {0, 0},
            {1, 0},
            {0, 1}
        }
    );

    affectationS2 = copieS2;

    std::vector<double> minimum2 =
        nm.minimiser(
            f2,
            s2,
            1000,
            0.000001
        );

    std::cout << std::endl;
    std::cout << "========== TEST 2D =========="
              << std::endl;

    afficherResultat(
        "f",
        "f(x,y) = 13 - 4x - 6y + x^2 + y^2",
        minimum2,
        {2, 3},
        f2
    );


    // --------------------------------------------------
    // Rendu du test 2D
    // --------------------------------------------------

    const CollectionSimplexe& historique2D =
        nm.getHistorique();

    std::cout
        << "Nombre de simplexes 2D : "
        << historique2D.taille()
        << std::endl;

    // Affichage des simplexes dans le terminal
   

    // Courbes de niveau + triangles successifs
    rendu.sauvegarder(
        historique2D,
        f2,
        "historique2D.svg"
    );

    // Fichier utilisable avec gnuplot
    rendu.exporterGnuplot(
        historique2D,
        "historique2D.dat"
    );


    // ==================================================
    // TEST 3D
    //
    // f(x,y,z)
    // = 14 - 2x - 4y - 6z
    //   + x^2 + y^2 + z^2
    //
    // = (x-1)^2 + (y-2)^2 + (z-3)^2
    //
    // Minimum theorique : (1,2,3)
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

    std::cout << std::endl;
    std::cout << "========== TEST 3D =========="
              << std::endl;

    afficherResultat(
        "f",
        "f(x,y,z) = 14 - 2x - 4y - 6z + x^2 + y^2 + z^2",
        minimum3,
        {1, 2, 3},
        f3
    );


    // ==================================================
    // EXTENSION : MINIMUM SOUS CONTRAINTE
    //
    // Meme fonction que le test 2D :
    // f(x,y) = (x - 2)^2 + (y - 3)^2
    //
    // Contrainte (hyperplan en dimension 2) :
    // x + y = 3
    //
    // Sur cette droite, le minimum theorique est (1,2).
    // ==================================================

    FonctionSurHyperplan f2SousContrainte(
        f2,
        {1.0, 1.0},
        3.0
    );

    // La contrainte retire un degre de liberte :
    // on optimise donc une fonction de dimension 1.
    Simplexe sContrainte(
        f2SousContrainte.getDimensionReduite(),
        {
            {0.0},
            {4.0}
        }
    );

    std::vector<double> minimumParametres =
        nm.minimiser(
            f2SousContrainte,
            sContrainte,
            1000,
            0.000001
        );

    std::vector<double> minimumContraint =
        f2SousContrainte.reconstruire(minimumParametres);

    std::cout << std::endl;
    std::cout << "===== TEST SOUS CONTRAINTE ====="
              << std::endl;
    std::cout << "Contrainte : x + y = 3"
              << std::endl;

    afficherResultat(
        "f",
        "f(x,y) = 13 - 4x - 6y + x^2 + y^2",
        minimumContraint,
        {1, 2},
        f2
    );

    std::cout << "Verification contrainte : x + y = "
              << minimumContraint[0] + minimumContraint[1]
              << std::endl;

    // Le probleme contraint est ramene a une dimension.
    // On peut donc aussi visualiser sa convergence.
    rendu.sauvegarder1D(
        nm.getHistorique(),
        f2SousContrainte,
        "historiqueContrainte.svg"
    );


    return 0;
}