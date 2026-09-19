#include "NelderMead.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>


NelderMead::NelderMead()
    : alpha(1.0),
      gamma(2.0),
      rho(0.5),
      sigma(0.5)
{
}


// ==========================================================
// Calcul du centroide
// ==========================================================

std::vector<double> NelderMead::calculerCentroide(
    const Simplexe& simplexe,
    std::size_t pire) const
{
    std::size_t dimension =
        simplexe.getDimension();

    std::size_t nombreNoeuds =
        simplexe.nombreNoeuds();

    std::vector<double> centroide(
        dimension,
        0.0
    );

    // On additionne tous les points
    // sauf le pire
    for (std::size_t i = 0;
         i < nombreNoeuds;
         ++i)
    {
        if (i == pire)
            continue;

        const std::vector<double>& point =
            simplexe.getNoeud(i);

        for (std::size_t j = 0;
             j < dimension;
             ++j)
        {
            centroide[j] += point[j];
        }
    }

    // Dans un simplexe de dimension n,
    // il y a n points utilisés pour le centroide
    double nombrePoints =
        static_cast<double>(nombreNoeuds - 1);

    for (std::size_t j = 0;
         j < dimension;
         ++j)
    {
        centroide[j] /= nombrePoints;
    }

    return centroide;
}


// ==========================================================
// Classement des noeuds
// ==========================================================

std::vector<std::size_t> NelderMead::classerNoeuds(
    const Simplexe& simplexe,
    const Fonction& fonction
) const
{
    std::size_t nombreNoeuds =
        simplexe.nombreNoeuds();

    std::vector<std::size_t> indices(
        nombreNoeuds
    );

    for (std::size_t i = 0;
         i < nombreNoeuds;
         ++i)
    {
        indices[i] = i;
    }

    std::sort(
        indices.begin(),
        indices.end(),
        [&](std::size_t a, std::size_t b)
        {
            return fonction.evaluer(
                simplexe.getNoeud(a)
            )
            <
            fonction.evaluer(
                simplexe.getNoeud(b)
            );
        }
    );

    return indices;
}


// ==========================================================
// Ecart meilleur / pire
// ==========================================================

double NelderMead::calculerEcart(
    const Simplexe& simplexe,
    const Fonction& fonction
) const
{
    std::vector<std::size_t> indices =
        classerNoeuds(simplexe, fonction);

    double meilleur =
        fonction.evaluer(
            simplexe.getNoeud(indices.front())
        );

    double pire =
        fonction.evaluer(
            simplexe.getNoeud(indices.back())
        );

    return std::abs(pire - meilleur);
}


// ==========================================================
// Remplacer un noeud
// ==========================================================

void NelderMead::remplacerNoeud(
    Simplexe& simplexe,
    std::size_t indice,
    const std::vector<double>& point
) const
{
    simplexe.setNoeud(
        indice,
        point
    );
}


// ==========================================================
// ALGORITHME NELDER-MEAD
// ==========================================================

std::vector<double> NelderMead::minimiser(
    const Fonction& fonction,
    Simplexe simplexe,
    int maxIterations,
    double tolerance
)
{
    if (simplexe.getDimension() < 1)
    {
        throw std::invalid_argument(
            "La dimension doit etre positive."
        );
    }

    // Un simplexe de dimension n
    // doit avoir n + 1 noeuds
    if (simplexe.nombreNoeuds()
        != simplexe.getDimension() + 1)
    {
        throw std::invalid_argument(
            "Un simplexe de dimension n doit "
            "avoir n + 1 noeuds."
        );
    }


    // ------------------------------------------
    // Nouveau calcul -> nouvel historique
    // ------------------------------------------

    historique.vider();

    // On sauvegarde le simplexe initial
    historique.ajouter(simplexe);


    // ------------------------------------------
    // Boucle principale
    // ------------------------------------------

    for (int iteration = 0;
         iteration < maxIterations;
         ++iteration)
    {
        // Classement des points
        //
        // indices[0] = meilleur
        // indices[... ] = intermediaires
        // indices[n] = pire

        std::vector<std::size_t> indices =
            classerNoeuds(
                simplexe,
                fonction
            );

        std::size_t meilleur =
            indices.front();

        std::size_t pire =
            indices.back();


        // --------------------------------------
        // Critere d'arret
        // --------------------------------------

        if (calculerEcart(
                simplexe,
                fonction
            ) < tolerance)
        {
            break;
        }


        // --------------------------------------
        // Centroide
        // --------------------------------------

        std::vector<double> centroide =
            calculerCentroide(
                simplexe,
                pire
            );


        // --------------------------------------
        // REFLEXION
        //
        // xr = c + alpha(c - xw)
        // --------------------------------------

        const std::vector<double>& xPire =
            simplexe.getNoeud(pire);

        std::vector<double> reflexion(
            simplexe.getDimension()
        );

        for (std::size_t j = 0;
             j < simplexe.getDimension();
             ++j)
        {
            reflexion[j] =
                centroide[j]
                + alpha *
                (centroide[j] - xPire[j]);
        }

        double fReflexion =
            fonction.evaluer(reflexion);


        // Valeur du meilleur
        double fMeilleur =
            fonction.evaluer(
                simplexe.getNoeud(meilleur)
            );


        // Deuxieme pire
        std::size_t deuxiemePire =
            indices[indices.size() - 2];

        double fDeuxiemePire =
            fonction.evaluer(
                simplexe.getNoeud(deuxiemePire)
            );

        double fPire =
            fonction.evaluer(xPire);


        // ==================================================
        // CAS 1 : REFLEXION
        // ==================================================

        if (fMeilleur <= fReflexion &&
            fReflexion < fDeuxiemePire)
        {
            remplacerNoeud(
                simplexe,
                pire,
                reflexion
            );
        }


        // ==================================================
        // CAS 2 : EXPANSION
        // ==================================================

        else if (fReflexion < fMeilleur)
        {
            // xe = c + gamma(xr - c)

            std::vector<double> expansion(
                simplexe.getDimension()
            );

            for (std::size_t j = 0;
                 j < simplexe.getDimension();
                 ++j)
            {
                expansion[j] =
                    centroide[j]
                    + gamma *
                    (reflexion[j] - centroide[j]);
            }

            double fExpansion =
                fonction.evaluer(expansion);

            if (fExpansion < fReflexion)
            {
                remplacerNoeud(
                    simplexe,
                    pire,
                    expansion
                );
            }
            else
            {
                remplacerNoeud(
                    simplexe,
                    pire,
                    reflexion
                );
            }
        }


        // ==================================================
        // CAS 3 : CONTRACTION
        // ==================================================

        else
        {
            // Contraction externe :
            //
            // xc = c + rho(xr - c)

            std::vector<double> contraction(
                simplexe.getDimension()
            );

            if (fReflexion < fPire)
            {
                for (std::size_t j = 0;
                     j < simplexe.getDimension();
                     ++j)
                {
                    contraction[j] =
                        centroide[j]
                        + rho *
                        (reflexion[j]
                         - centroide[j]);
                }
            }

            // Contraction interne :
            //
            // xc = c + rho(xw - c)

            else
            {
                for (std::size_t j = 0;
                     j < simplexe.getDimension();
                     ++j)
                {
                    contraction[j] =
                        centroide[j]
                        + rho *
                        (xPire[j]
                         - centroide[j]);
                }
            }


            double fContraction =
                fonction.evaluer(
                    contraction
                );


            // La contraction fonctionne
            if (fContraction < fPire)
            {
                remplacerNoeud(
                    simplexe,
                    pire,
                    contraction
                );
            }


            // ==================================================
            // REDUCTION
            // ==================================================

            else
            {
                const std::vector<double>& xMeilleur =
                    simplexe.getNoeud(meilleur);

                for (std::size_t i = 0;
                     i < simplexe.nombreNoeuds();
                     ++i)
                {
                    if (i == meilleur)
                        continue;

                    std::vector<double> reduction(
                        simplexe.getDimension()
                    );

                    const std::vector<double>& point =
                        simplexe.getNoeud(i);

                    for (std::size_t j = 0;
                         j < simplexe.getDimension();
                         ++j)
                    {
                        reduction[j] =
                            xMeilleur[j]
                            + sigma *
                            (point[j]
                             - xMeilleur[j]);
                    }

                    remplacerNoeud(
                        simplexe,
                        i,
                        reduction
                    );
                }
            }
        }

<<<<<<< HEAD

        // ------------------------------------------
        // On sauvegarde le nouveau simplexe
        // ------------------------------------------

=======
        // Sauvegarde du simplexe courant, quelle que
        // soit l'opération effectuée (réflexion,
        // expansion, contraction ou réduction)
>>>>>>> c5d1116 (Ajout des rendus 1D et 2D et copie du simplexe)
        historique.ajouter(simplexe);
    }


    // ------------------------------------------
    // Recherche du meilleur point final
    // ------------------------------------------

    std::vector<std::size_t> indicesFinal =
        classerNoeuds(
            simplexe,
            fonction
        );

    return simplexe.getNoeud(
        indicesFinal.front()
    );
}


// ==========================================================
// Historique
// ==========================================================

const CollectionSimplexe&
NelderMead::getHistorique() const
{
    return historique;
}