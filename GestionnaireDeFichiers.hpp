// DIRECTIVES
#ifndef GESTIONNAIREDEFICHIERS_HPP
#define GESTIONNAIREDEFICHIERS_HPP

// LIBRAIRIES
#include <stdio> // Permettre principalement la manipulation des flux de caractères
#include <iostream> // Contrôler la lecture et l'écriture des flux standard
#include "Echéancier.hpp" // Pour utiliser la classe Echéancier

// CLASSE
class GestionnaireDeFichiers
{
    private:
    // VARIABLES
    FILE *fichier;

    public:
    // CONSTRUCTEURS
    GestionnaireDeFichiers(FILE *fichier)
    {
        this->fichier=fichier;
    }

    // DESTRUCTEUR
    ~GestionnaireDeFichiers()
    {}

    // METHODES
    /*
        Fonction de type void pour ne rien renvoyer.
        Argument de type FILE* pour permettre de charger un fichier.
        La fonction charge un fichier et l'enregistre dans le GestionnaireDeFichiers.
    */
    void *Charger(FILE *fichier)
    {
        this->fichier=fichier;
    }

    /*
        Fonction de type void pour ne rien renvoyer.
        Argument de type Echéancier pour avoir la source des informations à enregistrer.
        La fonction permet d'enregistrer un échéancier.
    */
    void enregistrer(Echéancier E)
    {

    }

    /*
        Fonction de type FILE* pour renvoyer un fichier.
        Aucun argument n'est nécessaire à cette fonction.
        La fonction retourne la variable privée fichier.
    */
   FILE *GetFichier()
   {
       return fichier;
   }
}

#endif