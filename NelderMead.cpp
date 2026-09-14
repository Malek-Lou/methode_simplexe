#include "NelderMead.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>

NelderMead::NelderMead()
    : alpha(1.0),
      gamma(2.0),
      rho(0.5),
      sigma(0.5)
{
}

std::vector<double> NelderMead::minimiser(
    const Fonction& fonction,
    Simplexe simplexe,
    int maxIterations,
    double tolerance)
{
    int dimension = simplexe.getDimension();
    int nombrePoints = simplexe.nombreNoeuds();

    std::vector<double> valeurs(nombrePoints);

    for (int iteration = 0;
         iteration < maxIterations;
         ++iteration)
    {
        // ==========================================
        // 1. Évaluer tous les points
        // ==========================================

        for (int i = 0; i < nombrePoints; ++i)
        {
            valeurs[i] =
                fonction.evaluer(simplexe.getNoeud(i));
        }

        // ==========================================
        // 2. Trier les points selon f(x)
        // ==========================================

        std::vector<int> indices(nombrePoints);

        std::iota(indices.begin(), indices.end(), 0);

        std::sort(
            indices.begin(),
            indices.end(),
            [&](int a, int b)
            {
                return valeurs[a] < valeurs[b];
            }
        );

        // meilleur : plus petite valeur
        int meilleur = indices[0];

        // pire : plus grande valeur
        int pire = indices[nombrePoints - 1];

        // deuxième pire
        int deuxiemePire = indices[nombrePoints - 2];

        // ==========================================
        // 3. Test de convergence
        // ==========================================

        double ecart =
            valeurs[pire] - valeurs[meilleur];

        // On vérifie aussi la dispersion spatiale du
        // simplexe : deux points peuvent avoir la même
        // valeur de f sans être proches l'un de l'autre
        // (cas d'un simplexe initial "dégénéré").

        const std::vector<double>& pointMeilleurConv =
            simplexe.getNoeud(meilleur);

        double tailleSimplexe = 0.0;

        for (int i = 0; i < nombrePoints; ++i)
        {
            if (i == meilleur)
                continue;

            const std::vector<double>& point =
                simplexe.getNoeud(i);

            double dist2 = 0.0;

            for (int j = 0; j < dimension; ++j)
            {
                double diff = point[j] - pointMeilleurConv[j];
                dist2 += diff * diff;
            }

            tailleSimplexe =
                std::max(tailleSimplexe, std::sqrt(dist2));
        }

        if (ecart < tolerance && tailleSimplexe < tolerance)
        {
            return simplexe.getNoeud(meilleur);
        }

        // ==========================================
        // 4. Calcul du centre G
        //    sans le pire point
        // ==========================================

        std::vector<double> centre(
            dimension,
            0.0
        );

        for (int i = 0; i < nombrePoints; ++i)
        {
            if (i == pire)
                continue;

            const std::vector<double>& point =
                simplexe.getNoeud(i);

            for (int j = 0; j < dimension; ++j)
            {
                centre[j] += point[j];
            }
        }

        // Il y a exactement 'dimension'
        // points dans le centre
        for (int j = 0; j < dimension; ++j)
        {
            centre[j] /= dimension;
        }

        // ==========================================
        // 5. RÉFLEXION
        //
        // R = G + alpha(G - W)
        // ==========================================

        const std::vector<double>& pointPire =
            simplexe.getNoeud(pire);

        std::vector<double> reflexion(dimension);

        for (int j = 0; j < dimension; ++j)
        {
            reflexion[j] =
                centre[j]
                + alpha *
                (centre[j] - pointPire[j]);
        }

        double valeurReflexion =
            fonction.evaluer(reflexion);

        // ==========================================
        // 6. Cas où la réflexion est intéressante
        // ==========================================

        if (valeurReflexion < valeurs[meilleur])
        {
            // ======================================
            // EXPANSION
            //
            // E = G + gamma(R - G)
            // ======================================

            std::vector<double> expansion(dimension);

            for (int j = 0; j < dimension; ++j)
            {
                expansion[j] =
                    centre[j]
                    + gamma *
                    (reflexion[j] - centre[j]);
            }

            double valeurExpansion =
                fonction.evaluer(expansion);

            if (valeurExpansion < valeurReflexion)
            {
                // Expansion meilleure
                simplexe.setNoeud(
                    pire,
                    expansion
                );
            }
            else
            {
                // Réflexion meilleure
                simplexe.setNoeud(
                    pire,
                    reflexion
                );
            }
        }

        // ==========================================
        // 7. Réflexion meilleure que le pire,
        //    mais pas meilleure que le meilleur
        // ==========================================

        else if (valeurReflexion < valeurs[deuxiemePire])
        {
            // On accepte simplement la réflexion

            simplexe.setNoeud(
                pire,
                reflexion
            );
        }

        // ==========================================
        // 8. CONTRACTION
        //
        // C = G + rho(W - G)
        // ==========================================

        else
        {
            std::vector<double> contraction(dimension);

            for (int j = 0; j < dimension; ++j)
            {
                contraction[j] =
                    centre[j]
                    + rho *
                    (pointPire[j] - centre[j]);
            }

            double valeurContraction =
                fonction.evaluer(contraction);

            if (valeurContraction < valeurs[pire])
            {
                // La contraction fonctionne

                simplexe.setNoeud(
                    pire,
                    contraction
                );
            }

            // ======================================
            // 9. RÉDUCTION
            // ======================================

            else
            {
                const std::vector<double>& pointMeilleur =
                    simplexe.getNoeud(meilleur);

                for (int i = 0;
                     i < nombrePoints;
                     ++i)
                {
                    if (i == meilleur)
                        continue;

                    const std::vector<double>& point =
                        simplexe.getNoeud(i);

                    std::vector<double> nouveauPoint(
                        dimension
                    );

                    // X' = B + sigma(X - B)

                    for (int j = 0;
                         j < dimension;
                         ++j)
                    {
                        nouveauPoint[j] =
                            pointMeilleur[j]
                            + sigma *
                            (point[j] - pointMeilleur[j]);
                    }

                    simplexe.setNoeud(
                        i,
                        nouveauPoint
                    );
                }
            }
        }
    }

    // ==========================================
    // Nombre maximum d'itérations atteint
    // ==========================================

    for (int i = 0; i < nombrePoints; ++i)
    {
        valeurs[i] =
            fonction.evaluer(
                simplexe.getNoeud(i)
            );
    }

    int meilleur = 0;

    for (int i = 1; i < nombrePoints; ++i)
    {
        if (valeurs[i] < valeurs[meilleur])
        {
            meilleur = i;
        }
    }

    return simplexe.getNoeud(meilleur);
}