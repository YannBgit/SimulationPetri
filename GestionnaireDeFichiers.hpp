// DIRECTIVES
#ifndef GESTIONNAIREDEFICHIERS_HPP
#define GESTIONNAIREDEFICHIERS_HPP

// LIBRAIRIES

// CLASSE
class GestionnaireDeFichiers
{
    private:
    // VARIABLES

    public:
    // CONSTRUCTEURS
    GestionnaireDeFichiers()
    {}

    // DESTRUCTEUR
    ~GestionnaireDeFichiers()
    {}

    // METHODES
    // Fonction qui charge un fichier et qui le renvoie
    void Chargeur(int NewRDP)
    {}
    
    // Fonction qui stock les résultats obtenus à chaque temps Te
    void Result (int *Te)
    {}
    
     // Fonction qui permet la création d'un nouveau réseau
    Moteur NewRDP(int S, int T, float *P, int **F, int *M, int **W, int *K)
    {}

}

#endif
