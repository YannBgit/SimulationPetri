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
        FILE *fichier = NULL;
        char c;
        fichier= fopen ("rdp.txt","r");
       if (fichier != NULL)
    {
		// on affiche le contenu du fichier 
		    while((c=fgetc(fichier))!=EOF){
				printf("%c",c);
			}
		
        
        fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier rdp.txt");
    }
    
}
        
    }

    /*
    Fonction de type void pour ne rien renvoyer.
    Aucun argument n'est nécessaire à cette fonction.
    La fonction crée un fichier temporaire vide pour l'échéancier.
    */
    void CreerFichierTemporaire(); 
    {
        
        FILE *fichier ;
        
        
        fichier = fopen("fichier.txt", "r");
        
        if (fichier == NULL)	// Erreur dans l'ouverture
            cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
        else
        {
            fclose (fichier);
        }
        
        Echeancier.AjouterEtatReseau(M);
    }
            
       
        

    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type Moteur pour avoir les informations à écrire et FILE * pour spécifier le fichier dans lequel écrire.
    La fonction sert à écrire un état du réseau de Petri dans un fichier.
    */
    void EcrireEtat(Moteur M, FILE *fichier)
    {
        FILE *fichier;
        Moteur M;
        
            
        fichier = fopen(GestionnaireDeFichiers, "r+");	// Ouvre le fichier en lecture et écriture
            
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
            
            
        

    /*
    Fonction de type void pour ne rien renvoyer.
    Arguments de type FILE * pour avoir la source et la destination des informations à enregistrer.
    La fonction permet d'enregistrer un échéancier en faisant passer les informations du fichier temporaire dans lequel ses données
    sont conservées vers le fichier principal d'enregistrement.
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
