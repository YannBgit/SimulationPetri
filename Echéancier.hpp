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
    void StockeurReseau(int S, int T, float *P, int **F, int *M, int **W, int *K){
        StockeurTemps; // Ecrit dans le fichier le dernier temps pour l'affecter à cet état du réseau

        string const nomFichier("C:/.../???.txt");

        ofstream monFlux(nomFichier.c_str()); // Déclaration d'un flux permettant d'écrire dans un fichier.
        ofstream monFlux("C:/.../???.txt");  // On essaye d'ouvrir le fichier

        if(monFlux)  // On teste si tout est OK
        {
            // Tout est OK, on peut utiliser le fichier
            // Stockage de l'état du réseau
            monFlux << "{" << endl;
            monFlux << "int S=" << S << ";" << endl;
            monFlux << "int T=" << T << ";" << endl;
            // faire une boucle pour stocker tout les P mais c'est l'idée
            monFlux << "float *P={" << P[0] << "};" << endl;
            // idem
            monFlux << "int **F={" << F[0][0] << "};" << endl;
            // idem
            monFlux << "float *M={" << P[0] << "};" << endl;
            // idem
            monFlux << "int **W={" << W[0][0] << ";" << endl;
            // idem
            monFlux << "int *K={" << K[0] << "};" << endl;
            monFlux << "}" << endl;
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
        }		

    };


    // Fonction qui étiquette chaque état du réseau enregistré avec un temps arbitraire
    void StockeurTemps(){
        string const nomFichier("C:/.../???.txt");

        ofstream monFlux(nomFichier.c_str()); // Déclaration d'un flux permettant d'écrire dans un fichier.
        ofstream monFlux("C:/.../???.txt");  // On essaye d'ouvrir le fichier

        if(monFlux)  //On teste si tout est OK
        {
            // Tout est OK, on peut utiliser le fichier
            int Te;
            // Lire le dernier Te + l'affecter à Te (avec getline() : ligne par ligne);
            Te += 1;
            monFlux << endl;
            monFlux << "int Te=" << Te << ";" << endl;
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
        }
    };


    // Fonction qui recherche un état du réseau enregistré avec un temps donné et le renvoie
    int RechercheTemps(int Te){
        string const nomFichier("C:/.../???.txt");

        ofstream monFlux(nomFichier.c_str()); // Déclaration d'un flux permettant d'écrire dans un fichier.
        ofstream monFlux("C:/.../???.txt");  // On essaye d'ouvrir le fichier

        if(monFlux)  // On teste si tout est OK
        {
            // Tout est OK, on peut utiliser le fichier

            int T = Te;
            Chercher Te (avec getline() : ligne par ligne);
            Renvoyer l'état du réseau stocker en dessous;
        }
        else
        {
            // cout << "ERREUR: Impossible d'ouvrir le fichier" << endl;
        }
    };
}

#endif