// DIRECTIVES
#ifndef ECHEANCIER_HPP
#define ECHEANCIER_HPP

// LIBRAIRIES
#include "GestionnaireDeFichiers.hpp" // Pour utiliser la classe GestionnaireDeFichiers
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include <stdio.h> // Permettre principalement la manipulation des flux de caractères

// CLASSE
class Echeancier
{
    private:
    // VARIABLES
    int TempsCourant;

    public:
    // CONSTRUCTEURS
    Echeancier(GestionnaireDeFichiers GDF)
    {
        
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
	    FILE *fichier = GestionnaireDeFichiers->temp;

	    StockerTempsCourant(M);
	    GestionnaireDeFichiers.EcrireEtat(M, fichier);
	}

    /*
    Fonction de type Moteur pour renvoyer un état du réseau selon le temps courant.
    Aucun argument n'est nécessaire.
    La fonction recherche le dernier état du réseau enregistré et le renvoie.
    */
    Moteur RenvoyerEtatReseauCourant()
    {

    }

    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type moteur où chercher le temps courant du réseau.
    La fonction enregistre le temps courant du réseau.
    */
    void StockerTempsCourant(Moteur M)
    {
	    this.TempsCourant = M.Te;
	    FILE *fichier;
	    char *c = "Te = ";

	    fichier = fopen(GestionnaireDeFichiers->temp, "r+");	// Ouvre le fichier en lecture et écriture

	    /* Vérification d'ouverture */
        if(f == NULL)	// Erreur dans l'ouverture
            cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
        else
        {	// Ouverture réussie
            fprintf (f, "%s", c[0]);
            fprintf (f, "%d \n", this.TempsCourant);
            fclose (fichier);
        }
	}

    /*
    Fonction de type Moteur pour renvoyer un état du réseau selon le temps cherché s'il existe ou le dernier temps stocké s'il n'existe pas.
    Argument de type int Te, le temps auquel on veut récupérer le réseau de Petri.
    La fonction recherche un état du réseau enregistré avec un temps donné et le renvoie.
    */
    Moteur RenvoyerEtatReseauSelonTemps(int Te)
    {

    }
}

#endif
