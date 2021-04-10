// DIRECTIVES
#ifndef GESTIONNAIREDEFICHIERS_HPP
#define GESTIONNAIREDEFICHIERS_HPP

// LIBRAIRIES
#include "Echeancier.hpp" // Pour utiliser la classe Echeancier
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
    {}

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
    {}

    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type Echéancier pour avoir la source des informations à enregistrer.
    La fonction permet d'enregistrer un échéancier.
    */
    void Enregistrer(Echeancier E)
    {}

    /*
    Fonction de type void pour ne rien renvoyer.
    Aucun argument n'est nécessaire à cette fonction.
    La fonction crée un fichier temporaire vide pour l'échéancier.
    */
    void CreerFichierTemporaire()
    {}
}

#endif