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
        this->fichier = fichier;
    }

    // DESTRUCTEUR
    ~GestionnaireDeFichiers();

    // METHODES
    /*
    Fonction de type void pour ne rien renvoyer.
    La fonction charge un fichier et l'enregistre dans le GestionnaireDeFichiers.
    */
    void Charger(Moteur M)
    {
	    //Pour chaque temps Te
    	for (int i = 0; i < M.getNbTransitions(); i++)
        {
            FILE *fichier ;
            
            fichier = fopen("rdpv.txt", "r");
            
            if (fichier == NULL)	// Erreur dans l'ouverture
                std::cout << "Impossible d'ouvrir le fichier en écriture !" << std::endl;
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
    void CreerFichierTemporaire(Moteur M)
    {
        
        FILE *fichier;
        
        //Pour chaque temps Te
    	for (int i = 0; i < M.getTemps(); i++)
        {
            fichier = fopen("rdpv.txt", "r+");	// Ouvre le fichier vide en lecture et écriture
                
            if (fichier == NULL)	// Erreur dans l'ouverture
                std::cout << "Impossible d'ouvrir le fichier en écriture !" << std::endl;
            else
            {	// Ouverture réussie et on ecrit dans le fichier
                
                    
                fprintf (fichier, "Te=%d \n", M.getTemps());
                fprintf (fichier, "S=%d \n", M.getNbSommets());
                fprintf (fichier, "T=%d \n", M.getNbTransitions());
                fprintf (fichier, "P=%d \n", M.getProbabiliteTirParTransition());
                fprintf (fichier, "F=%d \n", M.getMatricesArcs());
                fprintf (fichier, "M=%d \n", M.getNbJetonsParSommet());
                fprintf (fichier, "W=%d \n", M.getEvolutionNbJetonPourChaqueTransition());
                fprintf (fichier, "K=%d \n", M.getNbMaxJetonsParSommet());
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
    void EnregistrerEcheancier(FILE *temp, FILE *fichier)
    {
        FILE *temp;
	    
        temp = fopen("rdvp.txt","r");
        
        FILE *fichier;
        
        fichier = fopen("rdp.txt", "r++");
            
        if (temp != NULL) //si le fichier existe bien
		{
        /*string ligne;*/
 
            while(getline(temp, ligne)) // On le lis ligne par ligne
            {
                if(fichier) // Si le lieu de destination existe ( j'entend par la le dossier )
                {
                    fichier << ligne << std::endl; // On ecrit dans le fichier de destination
                }                          // Et au passage on le créer si il n'existe pas
                else
                {
                    std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
                }
            }
        }
        else
        {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
        }
    }

    FILE *getFichier() {
    	return this->fichier;
    }

    FILE *getTemp() {
    	return this->temp;
    }

};

#endif