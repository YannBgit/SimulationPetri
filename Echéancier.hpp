// DIRECTIVES
#ifndef ECHEANCIER_HPP
#define ECHEANCIER_HPP

// LIBRAIRIES

// CLASSE
class Echéancier
{
    private:
    // VARIABLES

    public:
    // CONSTRUCTEURS
    Echéancier()
    {}

    // DESTRUCTEUR
    ~Echéancier()
    {}

    // METHODES
    // Fonction qui enregistre les différents états du réseau à chaque tour
    void StockeurReseau(int S, int T, float *P, int **F, int *M, int **W, int *K)
    {}

    // Fonction qui étiquette chaque état du réseau enregistré avec un temps arbitraire
    void StockeurTemps()
    {}

    // Fonction qui recherche un état du réseau enregistré avec un temps donné et le renvoie
    int RechercheTemps(int Te)
    {}
}

#endif