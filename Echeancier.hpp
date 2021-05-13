// DIRECTIVES
#ifndef ECHEANCIER_HPP
#define ECHEANCIER_HPP

#define TAILLE_MAX 100

// LIBRAIRIES
#include "GestionnaireDeFichiers.hpp" // Pour utiliser la classe GestionnaireDeFichiers
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include <stdio.h> // Permettre principalement la manipulation des flux de caractères
#include <iostream>

// CLASSE
class Echeancier
{
    private:
    // VARIABLES
    int TempsCourant;
    FILE *fichier;
	FILE *temp;

    public:
    // CONSTRUCTEURS
    Echeancier(GestionnaireDeFichiers GDF)
    {
        this->fichier = GDF.getFichier();
	    this->temp = GDF.getTemp();
    }

    // DESTRUCTEUR
    ~Echeancier();

    // METHODES
    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type Moteur pour trouver les informations à enregistrer.
    La fonction enregistre un état du réseau de Petri.
    */
    void AjouterEtatReseau(Moteur M)
    {
	    StockerTempsCourant(M);
	    GDF.EcrireEtat(M, this->temp);

        return;
	}

    /*
    Fonction de type Moteur pour renvoyer un état du réseau selon le temps courant.
    Aucun argument n'est nécessaire.
    La fonction recherche le dernier état du réseau enregistré et le renvoie.
    */
    Moteur RenvoyerEtatReseauCourant()
    {
	    Moteur M = RenvoyerEtatReseauSelonTemps(TempsCourant);

	    return M;
    }

    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type moteur où chercher le temps courant du réseau.
    La fonction enregistre le temps courant du réseau.
    */
    void StockerTempsCourant(Moteur M)
    {
	    this->TempsCourant = M.getTemps();
        
        return;
	}

    /*
    Fonction de type Moteur pour renvoyer un état du réseau selon le temps cherché s'il existe ou le dernier temps stocké s'il n'existe
    pas.
    Argument de type int Te, le temps auquel on veut récupérer le réseau de Petri.
    La fonction recherche un état du réseau enregistré avec un temps donné et le renvoie.
    */
    Moteur RenvoyerEtatReseauSelonTemps(int Te)
    {
        char tableau[TAILLE_MAX];
        char ligne[TAILLE_MAX];

        char *chaine = "Te = ";
        char *te = (char)Te;
        char search[8];

        /* Concaténation de la chaine sous la forme de "Te = [Te en paramètre]" */
        int i, j;

        // Pour itérer la première chaîne du début à la fin
        for (i = 0; chaine[i] != '\0'; i++)
        {
            search[i] = chaine[i];
        }

        // Concaténer te dans search   
        for (j = 0; te[j]!='\0'; j++, i++)
        {
            search[i] = te[j];
        }

        search[i] = '\0';
        int max = i;	// Nombre de caractère dans la chaine search
        /* Fin de la concaténation */

        /* Recherche dans le fichier */
        while(fgets(ligne, TAILLE_MAX, fichier) != NULL)
        {
            for(i = 0; i != max; i++)
            {
                if(search[i] != ligne[i])
                {
                    ligne += 1;
                    i = 0;
                }
            }
        }

        // return ;
    }
};

#endif