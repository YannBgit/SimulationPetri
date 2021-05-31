// DIRECTIVES
#ifndef GESTIONNAIREDEFICHIERS_HPP
#define GESTIONNAIREDEFICHIERS_HPP

// LIBRAIRIES
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h> // Permettre principalement la manipulation des flux de caractères
#include <iostream> // Contrôler la lecture et l'écriture des flux standard

class Moteur; // Pour utiliser la classe Moteur

// CLASSE
class GestionnaireDeFichiers
{
    private:
    // VARIABLES
    FILE *fichier;
    FILE *temp;
    char* nom_fichier;
    int arc;

    public:
    // CONSTRUCTEURS
    GestionnaireDeFichiers(FILE *fichier);

    // DESTRUCTEUR
    ~GestionnaireDeFichiers();

    // METHODES

    /*
    Fonction de type void pour ne rien renvoyer.
    Aucun argument n'est nécessaire à cette fonction.
    La fonction crée un fichier temporaire vide pour l'échéancier.
    */
    FILE *CreerFichierTemporaire();

    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type Moteur pour avoir les informations à écrire et FILE * pour spécifier le fichier dans lequel écrire.
    La fonction sert à écrire un état du réseau de Petri dans un fichier.
    */
    void EcrireEtat(Moteur M, FILE *fichier);

    /*
    Fonction de type void pour ne rien renvoyer.
    Arguments de type FILE * pour avoir la source et la destination des informations à enregistrer.
    La fonction permet d'enregistrer un échéancier en faisant passer les informations du fichier temporaire dans lequel ses données
    sont conservées vers le fichier principal d'enregistrement.
    */
    void EnregistrerEcheancier(FILE *temp, FILE *fichier);
  
    /*
    Fonction de type void pour ne rien renvoyer.
	Argument de type FILE* pour permettre de charger un fichier.
	La fonction charge un fichier et l'enregistre dans le GestionnaireDeFichiers.
	*/
    void Charger(char* nom_fichier);

    Moteur rechercheEtat(int Te, char* nom_fichier);
	
    FILE *getFichier();

    FILE *getTemp();
	
    int getarc();

    char* getNom() {
        return this->nom_fichier;
    }

    void afficher(Moteur M, GestionnaireDeFichiers GDF);
};

#endif