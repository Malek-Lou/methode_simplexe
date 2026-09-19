#ifndef SIMPLEXE_HPP
#define SIMPLEXE_HPP

#include <vector>

class Simplexe
{
private:
    int dimension;
    std::vector<std::vector<double>> noeuds;

public:
    Simplexe(int dim, const std::vector<std::vector<double>>& points);
    // Constructeur par copie
    Simplexe(const Simplexe& autre);
    Simplexe& operator=(const Simplexe& autre);

    int getDimension() const;
    int nombreNoeuds() const;

    const std::vector<double>& getNoeud(int i) const;

    void setNoeud(
        int i,
        const std::vector<double>& point
    );
};

#endif
