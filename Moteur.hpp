// DIRECTIVES
#ifndef MOTEUR_HPP
#define MOTEUR_HPP

// LIBRAIRIES

// CLASSE
class Moteur
{
    private:
    // VARIABLES
    int S; // nombre de sommets
    int T; // nombre de transitions
    float *P; // probabilité de tir pour chaque transition, 0<P[n]<1
    int **F; // matrice des arcs
    int *M; // nombre de jetons contenu dans chaque sommet
    int **W; // nombre de jetons consommés et générés par chaque transition
    int *K; // nombre de jetons maximum pour chaque sommet
    sint Te; // temps

    public:
    // CONSTRUCTEURS
    Moteur(int S, int T, float *P, int **F, int *M, int **W, int *K, int Te)
    {}

    // DESTRUCTEUR
    ~Moteur()
    {}

    // METHODES
    // Renvoie si une transition doit être tirée selon sa probabilité de tirage
    bool Tirage(float P)
    {}

    // Renvoie un numéro de transition pseudo-aléatoirement parmi un nombre T de transitions
    int RésoutConflit(int T)
    {}
}

#endif