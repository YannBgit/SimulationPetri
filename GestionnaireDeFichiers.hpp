// DIRECTIVES
#ifndef GESTIONNAIREDEFICHIERS_HPP
#define GESTIONNAIREDEFICHIERS_HPP

// LIBRAIRIES
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include <stdio.h> // Permettre principalement la manipulation des flux de caractères
#include <iostream.h> // Contrôler la lecture et l'écriture des flux standard

// CLASSE
class GestionnaireDeFichiers
{
    private:
    // VARIABLES
    FILE *fichier;
    FILE *temp;
    

    public:
    // CONSTRUCTEURS
    GestionnaireDeFichiers(FILE *fichier);

    // DESTRUCTEUR
    ~GestionnaireDeFichiers();

    // METHODES
    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type FILE* pour permettre de charger un fichier.
    La fonction charge un fichier et l'enregistre dans le GestionnaireDeFichiers.
    */
    void Charger(FILE *fichier);

    /*
    Fonction de type void pour ne rien renvoyer.
    Aucun argument n'est nécessaire à cette fonction.
    La fonction crée un fichier temporaire vide pour l'échéancier.
    */
    void CreerFichierTemporaire(); 
    {
        
        FILE *fichier ;
        
        
        fichier = fopen(GestionnaireDeFichiers, "r");
        
        if (fichier == NULL)	// Erreur dans l'ouverture
            cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
        else{
            fclose (fichier);
        }
        
        Echeancier.AjouterEtatReseau(M);
    }
            
       
        

    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type Moteur pour avoir les informations à écrire et FILE * pour spécifier le fichier dans lequel écrire.
    La fonction sert à écrire un état du réseau de Petri dans un fichier.
    */
    void EcrireEtat(Moteur M, FILE *fichier);
        {
            FILE *fichier;
            Moteur M;
            char*c;
            
            fichier = fopen(GestionnaireDeFichiers, "r+");	// Ouvre le fichier en lecture et écriture
            
            if (fichier == NULL)	// Erreur dans l'ouverture
            cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
        else{	// Ouverture réussie
            fprintf (f, "%s", c[0]);
            fprintf (f, "%d \n", M.Te);
            fprintf (f, "%d \n", M.S);
            fprintf (f, "%d \n", M.T);
            fprintf (f, "%d \n", M.P);
            fprintf (f, "%d \n", M.M);
            fprintf (f, "%d \n", M.W);
            fprintf (f, "%d \n", M.K);
            fclose (fichier);
        }
        }
            
            
        

    /*
    Fonction de type void pour ne rien renvoyer.
    Arguments de type FILE * pour avoir la source et la destination des informations à enregistrer.
    La fonction permet d'enregistrer un échéancier en faisant passer les informations du fichier temporaire dans lequel ses données sont conservées
    vers le fichier principal d'enregistrement.
    */
    void EnregistrerEcheancier(FILE *temp, FILE *fichier);
    {
        string const nomFichier("C:/.../???.txt");
        ofstream monFlux(nomFichier.c_str()); //Déclaration d'un flux permettant d'écrire dans un fichier.
        ofstream monFlux("C:/.../???.txt");  //On essaye d'ouvrir le fichier
        if(nomFichier)  // si l'ouverture a réussi
    }
}

#endif
