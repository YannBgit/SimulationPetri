// DIRECTIVES
#ifndef GESTIONNAIREDEFICHIERS_HPP
#define GESTIONNAIREDEFICHIERS_HPP

// LIBRAIRIES
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include <stdio.h> // Permettre principalement la manipulation des flux de caractères
#include <iostream> // Contrôler la lecture et l'écriture des flux standard

// CLASSE
class GestionnaireDeFichiers
{
    private:
    // VARIABLES
    FILE *fichier;
    FILE *temp;

    public:
    // CONSTRUCTEURS
    GestionnaireDeFichiers(FILE *fichier)
    {
        FILE *fichier = GDF->fichier;
    }

    // DESTRUCTEUR
    ~GestionnaireDeFichiers();

    // METHODES
    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type FILE* pour permettre de charger un fichier.
    La fonction charge un fichier et l'enregistre dans le GestionnaireDeFichiers.
    */
    void Charger(FILE *fichier)
    {
	    //Pour chaque temps Te
    	for (int i = 0; i < this->T; i++)
        {
            FILE *fichier ;
            
            fichier = fopen("rdpv.txt", "r");
            
            if (fichier == NULL)	// Erreur dans l'ouverture
                cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
            else
            {
                fclose (fichier);
            }
            
            Echeancier.AjouterEtatReseau(M);
        }
    }

    /*
    Fonction de type void pour ne rien renvoyer.
    Aucun argument n'est nécessaire à cette fonction.
    La fonction crée un fichier temporaire vide pour l'échéancier.
    */
    void CreerFichierTemporaire(); 
    {
        
        FILE *fichier;
        
        //Pour chaque temps Te
    	for (int i = 0; i < this->Te; i++)
        {
            fichier = fopen("rdpv.txt", "r+");	// Ouvre le fichier vide en lecture et écriture
                
            if (fichier == NULL)	// Erreur dans l'ouverture
                cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
            else
            {	// Ouverture réussie et on ecrit dans le fichier
                
                    
                fprintf (fichier, "Te=%d \n", M.Te);
                fprintf (fichier, "S=%d \n", this->S);
                fprintf (fichier, "T=%d \n", this->T);
                fprintf (fichier, "P=%d \n", this->P);
                fprintf (fichier, "F=%d \n", this->F);
                fprintf (fichier, "M=%d \n", this->M);
                fprintf (fichier, "W=%d \n", this->W);
                fprintf (fichier, "K=%d \n", this->K);
                fclose (fichier);
            }
        }
    } 

    /*
    Fonction de type void pour ne rien renvoyer.
    Arguments de type FILE * pour avoir la source et la destination des informations à enregistrer.
    La fonction permet d'enregistrer un échéancier en faisant passer les informations du fichier temporaire dans lequel ses données
    sont conservées vers le fichier principal d'enregistrement.
    */
    void EnregistrerEcheancier(FILE *temp, FILE *fichier);
    {
        FILE *temp;
	    
        temp = fopen("rdvp.txt","r");
        
        FILE *fichier;
        
        fichier = fopen("rdp.txt", "r++");
            
        if (temp); //si le fichier existe bien
		{
        /*string ligne;*/
 
            while(getline(temp, ligne)) // On le lis ligne par ligne
            {
                if(fichier) // Si le lieu de destination existe ( j'entend par la le dossier )
                {
                    fichier << ligne << endl; // On ecrit dans le fichier de destination
                }                          // Et au passage on le créer si il n'existe pas
                else
                {
                    cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
                }
            }
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        }
    }
}

#endif