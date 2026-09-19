#include "Rendu.hpp"

#include <fstream>
<<<<<<< HEAD
#include <iostream>
#include <stdexcept>
#include <cstdlib>

Rendu::Rendu()
{
}
=======
#include <limits>
#include <algorithm>
#include <vector>
#include <utility>
>>>>>>> c5d1116 (Ajout des rendus 1D et 2D et copie du simplexe)

void Rendu::afficher(
    const CollectionSimplexe& historique) const
{
<<<<<<< HEAD
    for (std::size_t i = 0;
         i < historique.taille();
         ++i)
=======
    std::cout << "Historique des simplexes :" << std::endl;

    for (size_t i = 0; i < historique.taille(); ++i)
>>>>>>> c5d1116 (Ajout des rendus 1D et 2D et copie du simplexe)
    {
        const Simplexe& s =
            historique.getSimplexe(i);

<<<<<<< HEAD
        std::cout << "\n===== ITERATION "
                  << i
                  << " =====\n";

        for (std::size_t j = 0;
             j < s.nombreNoeuds();
             ++j)
        {
            const std::vector<double>& p =
=======
        std::cout << "Simplexe " << i << " : ";

        for (int j = 0; j < s.nombreNoeuds(); ++j)
        {
            const std::vector<double>& point =
>>>>>>> c5d1116 (Ajout des rendus 1D et 2D et copie du simplexe)
                s.getNoeud(j);

            std::cout << "Noeud " << j << " : ";

<<<<<<< HEAD
            for (std::size_t k = 0;
                 k < p.size();
                 ++k)
=======
            for (size_t k = 0; k < point.size(); ++k)
>>>>>>> c5d1116 (Ajout des rendus 1D et 2D et copie du simplexe)
            {
                std::cout << p[k];

<<<<<<< HEAD
                if (k + 1 < p.size())
                    std::cout << ", ";
            }

            std::cout << '\n';
=======
                if (k < point.size() - 1)
                    std::cout << ", ";
            }

            std::cout << ") ";
>>>>>>> c5d1116 (Ajout des rendus 1D et 2D et copie du simplexe)
        }

        std::cout << std::endl;
    }
}

<<<<<<< HEAD

void Rendu::tracer2D(
=======
void Rendu::sauvegarder1D(
    const CollectionSimplexe& historique,
    const Fonction& fonction,
    const std::string& nomFichier) const
{
    if (historique.taille() == 0)
    {
        std::cerr << "Historique vide." << std::endl;
        return;
    }

    const Simplexe& premier =
        historique.getSimplexe(0);

    if (premier.getDimension() != 1)
    {
        std::cerr
            << "Le rendu 1D est disponible uniquement "
            << "pour un simplexe de dimension 1."
            << std::endl;

        return;
    }

    // --------------------------------------------------
    // Recherche des bornes en x
    // --------------------------------------------------

    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();

    for (size_t i = 0; i < historique.taille(); ++i)
    {
        const Simplexe& s =
            historique.getSimplexe(i);

        for (int j = 0; j < s.nombreNoeuds(); ++j)
        {
            double x = s.getNoeud(j)[0];

            minX = std::min(minX, x);
            maxX = std::max(maxX, x);
        }
    }

    if (minX == maxX)
    {
        minX -= 1.0;
        maxX += 1.0;
    }

    double margeX = 0.1 * (maxX - minX);

    minX -= margeX;
    maxX += margeX;

    // --------------------------------------------------
    // Recherche des bornes en y
    // --------------------------------------------------

    const int resolution = 400;

    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (int i = 0; i <= resolution; ++i)
    {
        double x =
            minX
            + i * (maxX - minX) / resolution;

        double y = fonction.evaluer({x});

        minY = std::min(minY, y);
        maxY = std::max(maxY, y);
    }

    if (minY == maxY)
    {
        minY -= 1.0;
        maxY += 1.0;
    }

    double margeY = 0.1 * (maxY - minY);

    minY -= margeY;
    maxY += margeY;

    // --------------------------------------------------
    // Dimensions SVG
    // --------------------------------------------------

    const int largeur = 800;
    const int hauteur = 600;
    const int marge = 60;

    std::ofstream fichier(nomFichier);

    if (!fichier)
    {
        std::cerr
            << "Impossible de creer le fichier "
            << nomFichier
            << std::endl;

        return;
    }

    // --------------------------------------------------
    // Conversion coordonnées mathématiques -> SVG
    // --------------------------------------------------

    auto convertirX =
        [&](double x)
        {
            return marge
                + (x - minX)
                / (maxX - minX)
                * (largeur - 2 * marge);
        };

    auto convertirY =
        [&](double y)
        {
            return hauteur - marge
                - (y - minY)
                / (maxY - minY)
                * (hauteur - 2 * marge);
        };

    // --------------------------------------------------
    // Début SVG
    // --------------------------------------------------

    fichier
        << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        << "width=\"" << largeur
        << "\" height=\"" << hauteur
        << "\" viewBox=\"0 0 "
        << largeur << " "
        << hauteur << "\">"
        << std::endl;

    fichier
        << "<rect width=\"100%\" height=\"100%\" "
        << "fill=\"white\"/>"
        << std::endl;

    // --------------------------------------------------
    // Axes
    // --------------------------------------------------

    double axeX = convertirY(0.0);

    if (axeX >= marge && axeX <= hauteur - marge)
    {
        fichier
            << "<line x1=\"" << marge
            << "\" y1=\"" << axeX
            << "\" x2=\"" << largeur - marge
            << "\" y2=\"" << axeX
            << "\" stroke=\"black\" "
            << "stroke-width=\"1\"/>"
            << std::endl;
    }

    double axeY = convertirX(0.0);

    if (axeY >= marge && axeY <= largeur - marge)
    {
        fichier
            << "<line x1=\"" << axeY
            << "\" y1=\"" << marge
            << "\" x2=\"" << axeY
            << "\" y2=\"" << hauteur - marge
            << "\" stroke=\"black\" "
            << "stroke-width=\"1\"/>"
            << std::endl;
    }

    // --------------------------------------------------
    // Courbe de la fonction
    // --------------------------------------------------

    fichier
        << "<polyline fill=\"none\" "
        << "stroke=\"black\" "
        << "stroke-width=\"2\" points=\"";

    for (int i = 0; i <= resolution; ++i)
    {
        double x =
            minX
            + i * (maxX - minX) / resolution;

        double y = fonction.evaluer({x});

        fichier
            << convertirX(x)
            << ","
            << convertirY(y)
            << " ";
    }

    fichier << "\"/>" << std::endl;

    // --------------------------------------------------
    // Simplexes successifs
    // En dimension 1 : un simplexe = deux points
    // --------------------------------------------------

    for (size_t i = 0; i < historique.taille(); ++i)
    {
        const Simplexe& s =
            historique.getSimplexe(i);

        double x1 = s.getNoeud(0)[0];
        double x2 = s.getNoeud(1)[0];

        double y1 = fonction.evaluer({x1});
        double y2 = fonction.evaluer({x2});

        double progression = 0.0;

        if (historique.taille() > 1)
        {
            progression =
                static_cast<double>(i)
                / (historique.taille() - 1);
        }

        double opacite =
            0.15 + 0.70 * progression;

        fichier
            << "<line x1=\"" << convertirX(x1)
            << "\" y1=\"" << convertirY(y1)
            << "\" x2=\"" << convertirX(x2)
            << "\" y2=\"" << convertirY(y2)
            << "\" stroke=\"blue\" "
            << "stroke-width=\"2\" "
            << "opacity=\"" << opacite
            << "\"/>"
            << std::endl;

        fichier
            << "<circle cx=\"" << convertirX(x1)
            << "\" cy=\"" << convertirY(y1)
            << "\" r=\"3\" "
            << "fill=\"blue\" "
            << "opacity=\"" << opacite
            << "\"/>"
            << std::endl;

        fichier
            << "<circle cx=\"" << convertirX(x2)
            << "\" cy=\"" << convertirY(y2)
            << "\" r=\"3\" "
            << "fill=\"blue\" "
            << "opacity=\"" << opacite
            << "\"/>"
            << std::endl;
    }

    // --------------------------------------------------
    // Dernier simplexe
    // --------------------------------------------------

    const Simplexe& dernier =
        historique.getSimplexe(
            historique.taille() - 1
        );

    for (int j = 0; j < dernier.nombreNoeuds(); ++j)
    {
        double x = dernier.getNoeud(j)[0];
        double y = fonction.evaluer({x});

        fichier
            << "<circle cx=\"" << convertirX(x)
            << "\" cy=\"" << convertirY(y)
            << "\" r=\"6\" "
            << "fill=\"red\"/>"
            << std::endl;
    }

    fichier << "</svg>" << std::endl;

    fichier.close();

    std::cout
        << "Rendu 1D sauvegarde dans : "
        << nomFichier
        << std::endl;
}
void Rendu::sauvegarder(
>>>>>>> c5d1116 (Ajout des rendus 1D et 2D et copie du simplexe)
    const CollectionSimplexe& historique,
    const Fonction& fonction,
    const std::string& nomFichier) const
{
    if (historique.taille() == 0)
    {
        std::cerr << "Historique vide." << std::endl;
        return;
    }

    const Simplexe& premier =
        historique.getSimplexe(0);

    if (premier.getDimension() != 2)
    {
        std::cerr << "Le rendu graphique est disponible "
                  << "uniquement en 2D."
                  << std::endl;
        return;
    }

    // --------------------------------------------------
    // Recherche des bornes
    // --------------------------------------------------

    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (size_t i = 0; i < historique.taille(); ++i)
    {
        const Simplexe& s =
            historique.getSimplexe(i);

        for (int j = 0; j < s.nombreNoeuds(); ++j)
        {
            const std::vector<double>& point =
                s.getNoeud(j);

            minX = std::min(minX, point[0]);
            maxX = std::max(maxX, point[0]);

            minY = std::min(minY, point[1]);
            maxY = std::max(maxY, point[1]);
        }
    }

    // Éviter une échelle nulle
    if (minX == maxX)
    {
        minX -= 1.0;
        maxX += 1.0;
    }

    if (minY == maxY)
    {
        minY -= 1.0;
        maxY += 1.0;
    }

    // Marge autour du graphique
    double margeX = 0.1 * (maxX - minX);
    double margeY = 0.1 * (maxY - minY);

    minX -= margeX;
    maxX += margeX;
    minY -= margeY;
    maxY += margeY;

    // --------------------------------------------------
    // Dimensions du dessin
    // --------------------------------------------------

    const int largeur = 800;
    const int hauteur = 600;
    const int marge = 50;

    std::ofstream fichier(nomFichier);

    if (!fichier)
    {
        std::cerr << "Impossible de creer le fichier "
                  << nomFichier
                  << std::endl;
        return;
    }

    // --------------------------------------------------
    // Transformation coordonnées -> écran
    // --------------------------------------------------

    auto convertirX =
        [&](double x)
        {
            return marge +
                   (x - minX)
                   / (maxX - minX)
                   * (largeur - 2 * marge);
        };

    auto convertirY =
        [&](double y)
        {
            // L'axe Y de SVG est inversé
            return hauteur - marge -
                   (y - minY)
                   / (maxY - minY)
                   * (hauteur - 2 * marge);
        };

    // --------------------------------------------------
    // Début SVG
    // --------------------------------------------------

    fichier << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
            << "width=\"" << largeur
            << "\" height=\"" << hauteur
            << "\" viewBox=\"0 0 "
            << largeur << " "
            << hauteur << "\">"
            << std::endl;

    fichier << "<rect width=\"100%\" height=\"100%\" "
            << "fill=\"white\"/>"
            << std::endl;

    

    
    
    // --------------------------------------------------
// Courbes de niveau de la fonction
// --------------------------------------------------

const int resolution = 80;

double pasX = (maxX - minX) / resolution;
double pasY = (maxY - minY) / resolution;

// Grille des valeurs de la fonction
std::vector<std::vector<double>> valeurs(
    resolution + 1,
    std::vector<double>(resolution + 1)
);

double minF = std::numeric_limits<double>::max();
double maxF = std::numeric_limits<double>::lowest();

// Calcul des valeurs de la fonction sur la grille
for (int i = 0; i <= resolution; ++i)
{
    for (int j = 0; j <= resolution; ++j)
    {
        double x = minX + i * pasX;
        double y = minY + j * pasY;

        valeurs[i][j] = fonction.evaluer({x, y});

        minF = std::min(minF, valeurs[i][j]);
        maxF = std::max(maxF, valeurs[i][j]);
    }
}

// Fonction auxiliaire pour interpoler un point
// d'intersection sur une arête
auto interpolation =
    [&](double x1, double y1, double v1,
        double x2, double y2, double v2,
        double niveau)
{
    double t = (niveau - v1) / (v2 - v1);
    return std::pair<double, double>(
        x1 + t * (x2 - x1),
        y1 + t * (y2 - y1)
    );
};

// Test de croisement du niveau entre deux valeurs
auto coupe =
    [&](double a, double b, double niveau)
{
    return (a < niveau && b >= niveau)
        || (a >= niveau && b < niveau);
};

// Nombre de courbes de niveau
const int nbNiveaux = 12;

// Dessin des courbes de niveau
for (int n = 1; n <= nbNiveaux; ++n)
{
    double niveau =
        minF + n * (maxF - minF) / (nbNiveaux + 1);

    fichier << "<g stroke=\"gray\" "
            << "stroke-width=\"1\" "
            << "fill=\"none\" "
            << "opacity=\"0.7\">"
            << std::endl;

    for (int i = 0; i < resolution; ++i)
    {
        for (int j = 0; j < resolution; ++j)
        {
            double x1 = minX + i * pasX;
            double y1 = minY + j * pasY;
            double x2 = x1 + pasX;
            double y2 = y1 + pasY;

            // Coins de la cellule
            double vBG = valeurs[i][j];         // bas-gauche
            double vBD = valeurs[i + 1][j];     // bas-droite
            double vHD = valeurs[i + 1][j + 1]; // haut-droite
            double vHG = valeurs[i][j + 1];     // haut-gauche

            std::vector<std::pair<double, double>> intersections;

            // Arête du bas
            if (coupe(vBG, vBD, niveau))
            {
                intersections.push_back(
                    interpolation(x1, y1, vBG,
                                  x2, y1, vBD,
                                  niveau)
                );
            }

            // Arête de droite
            if (coupe(vBD, vHD, niveau))
            {
                intersections.push_back(
                    interpolation(x2, y1, vBD,
                                  x2, y2, vHD,
                                  niveau)
                );
            }

            // Arête du haut
            if (coupe(vHD, vHG, niveau))
            {
                intersections.push_back(
                    interpolation(x2, y2, vHD,
                                  x1, y2, vHG,
                                  niveau)
                );
            }

            // Arête de gauche
            if (coupe(vHG, vBG, niveau))
            {
                intersections.push_back(
                    interpolation(x1, y2, vHG,
                                  x1, y1, vBG,
                                  niveau)
                );
            }

            if (intersections.size() == 2)
            {
                fichier << "<line x1=\""
                        << convertirX(intersections[0].first)
                        << "\" y1=\""
                        << convertirY(intersections[0].second)
                        << "\" x2=\""
                        << convertirX(intersections[1].first)
                        << "\" y2=\""
                        << convertirY(intersections[1].second)
                        << "\"/>"
                        << std::endl;
            }
            else if (intersections.size() == 4)
            {
                fichier << "<line x1=\""
                        << convertirX(intersections[0].first)
                        << "\" y1=\""
                        << convertirY(intersections[0].second)
                        << "\" x2=\""
                        << convertirX(intersections[1].first)
                        << "\" y2=\""
                        << convertirY(intersections[1].second)
                        << "\"/>"
                        << std::endl;

                fichier << "<line x1=\""
                        << convertirX(intersections[2].first)
                        << "\" y1=\""
                        << convertirY(intersections[2].second)
                        << "\" x2=\""
                        << convertirX(intersections[3].first)
                        << "\" y2=\""
                        << convertirY(intersections[3].second)
                        << "\"/>"
                        << std::endl;
            }
        }
    }

    fichier << "</g>" << std::endl;
}
            // --------------------------------------------------
    // Axes
    // --------------------------------------------------

    double x0 = convertirX(0.0);
    double y0 = convertirY(0.0);

    if (x0 >= marge && x0 <= largeur - marge)
    {
        fichier << "<line x1=\"" << x0
                << "\" y1=\"" << marge
                << "\" x2=\"" << x0
                << "\" y2=\"" << hauteur - marge
                << "\" stroke=\"black\" stroke-width=\"1\"/>"
                << std::endl;
    }

    if (y0 >= marge && y0 <= hauteur - marge)
    {
        fichier << "<line x1=\"" << marge
                << "\" y1=\"" << y0
                << "\" x2=\"" << largeur - marge
                << "\" y2=\"" << y0
                << "\" stroke=\"black\" stroke-width=\"1\"/>"
                << std::endl;
    }

    // --------------------------------------------------
    // Dessin de tous les simplexes
    // --------------------------------------------------

    for (size_t i = 0; i < historique.taille(); ++i)
    {
        const Simplexe& s =
            historique.getSimplexe(i);

        fichier << "<polygon points=\"";

        for (int j = 0; j < s.nombreNoeuds(); ++j)
        {
            const std::vector<double>& point =
                s.getNoeud(j);

            fichier << convertirX(point[0])
                    << ","
                    << convertirY(point[1]);

            if (j < s.nombreNoeuds() - 1)
                fichier << " ";
        }

        fichier << "\" "
                << "fill=\"none\" "
                << "stroke=\"blue\" "
                << "stroke-width=\"1\" "
                << "opacity=\"0.35\"/>"
                << std::endl;
    }

    // --------------------------------------------------
    // Dessin du dernier simplexe
    // --------------------------------------------------

    const Simplexe& dernier =
        historique.getSimplexe(
            historique.taille() - 1
        );

    fichier << "<polygon points=\"";

    for (int j = 0; j < dernier.nombreNoeuds(); ++j)
    {
        const std::vector<double>& point =
            dernier.getNoeud(j);

        fichier << convertirX(point[0])
                << ","
                << convertirY(point[1]);

        if (j < dernier.nombreNoeuds() - 1)
            fichier << " ";
    }

    fichier << "\" "
            << "fill=\"none\" "
            << "stroke=\"red\" "
            << "stroke-width=\"3\"/>"
            << std::endl;

    // --------------------------------------------------
    // Fin SVG
    // --------------------------------------------------

    fichier << "</svg>" << std::endl;

    fichier.close();

    std::cout << "Rendu graphique sauvegarde dans : "
              << nomFichier
              << std::endl;
}


void Rendu::exporterGnuplot(
    const CollectionSimplexe& historique,
    const std::string& nomFichier) const
{
    // ------------------------------------
    // Création du fichier de données
    // ------------------------------------

    std::ofstream fichier("historique.dat");

    if (!fichier)
    {
<<<<<<< HEAD
        throw std::runtime_error(
            "Impossible de créer historique.dat"
        );
=======
        std::cerr << "Impossible de creer le fichier "
                  << nomFichier
                  << std::endl;
        return;
>>>>>>> c5d1116 (Ajout des rendus 1D et 2D et copie du simplexe)
    }

    // Un bloc par simplexe (itération), séparé par une
    // ligne vide : c'est le format "index" de gnuplot.
    // Chaque colonne : x  y  iteration
    // On referme le triangle en répétant le premier point.

    for (size_t i = 0; i < historique.taille(); ++i)
    {
        const Simplexe& s =
            historique.getSimplexe(i);

<<<<<<< HEAD
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
=======
        for (int j = 0; j <= s.nombreNoeuds(); ++j)
        {
            const std::vector<double>& point =
                s.getNoeud(j % s.nombreNoeuds());

            fichier << point[0] << " "
                    << point[1] << " "
                    << i
                    << std::endl;
        }

        // ligne vide = séparateur de bloc pour gnuplot
        fichier << std::endl;
>>>>>>> c5d1116 (Ajout des rendus 1D et 2D et copie du simplexe)
    }

    fichier.close();

    std::cout << "Donnees gnuplot sauvegardees dans : "
              << nomFichier
              << std::endl;
}