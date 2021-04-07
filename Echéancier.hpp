// DIRECTIVES
#ifndef ECHEANCIER_HPP
#define ECHEANCIER_HPP

// LIBRAIRIES
#include "GestionnaireDeFichiers.hpp" // Pour utiliser la classe GestionnaireDeFichiers
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include <stdio.h> // Permettre principalement la manipulation des flux de caractères
#include <iostream.h> // Contrôler la lecture et l'écriture des flux standard

// CLASSE
class Echéancier
{
    private:
    // VARIABLES
    FILE *fichier;
    int TempsCourant;

    public:
    // CONSTRUCTEURS
    Echéancier(GestionnaireDeFichiers GDF)
    {
        this->fichier=GDF.GetFichier();
        TempsCourant=0;
    }

    // DESTRUCTEUR
    ~Echéancier()
    {}

    // METHODES
    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type Moteur pour trouver les informations à enregistrer.
    La fonction enregistre les différents états du réseau à chaque tour.
    */
    void AjouterEtatRéseau(Moteur M)
    {}
    
    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type moteur où chercher le temps courant du réseau.
    La fonction enregistre le temps courant du réseau.
    */
    void StockerTempsCourant(Moteur M)
    {
        this->TempsCourant=M.Te;
    }

    /*
    Fonction de type Moteur pour renvoyer un état du réseau selon le temps courant.
    Aucun argument n'est nécessaire.
    La fonction recherche le dernier état du réseau enregistré et le renvoie.
    */
    Moteur RenvoyerEtatRéseauCourant()
    {}

    /*
    Fonction de type Moteur pour renvoyer un état du réseau selon le temps cherché s'il existe ou le dernier temps stocké s'il n'existe pas.
    Argument de type int Te, le temps auquel on veut récupérer le réseau de Petri.
    La fonction recherche un état du réseau enregistré avec un temps donné et le renvoie.
    */
    Moteur RenvoyerEtatRéseau(int Te)
    {}
}

#endif