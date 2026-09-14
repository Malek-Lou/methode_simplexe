class NelderMead
{
private:
    double alpha;
    double gamma;
    double rho;
    double sigma;

    CollectionSimplexe historique;

public:
    NelderMead();

    std::vector<double> minimiser(
        const Fonction& fonction,
        Simplexe simplexe,
        int maxIterations = 1000,
        double tolerance = 1e-8
    );

    const CollectionSimplexe& getHistorique() const;
};
