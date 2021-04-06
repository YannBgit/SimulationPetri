// DIRECTIVES
#ifndef ECHEANCIER_HPP
#define ECHEANCIER_HPP

// LIBRAIRIES
/* Permettre principalement la manipulation des flux de caractères. */
#include <cstdio>
/* Contrôlent la lecture et l'écriture des flux standard. */
#include <iostream>
/* Définit plusieurs classes qui prennent en charge les opérations iostreams sur des séquences stockées dans des fichiers externes. */
#include <fstream>
/* Pour utiliser la classe string (les chaînes de caractères) avec une gestion de la mémoire et des méthodes de gestion intégrés. */
#include <string>

/* Pour utiliser la classe Moteur */
#include "Moteur.hpp"
/* Pour utiliser la classe Gestionnairefichiers */
#include "Gestionnairefichiers.hpp"

// CLASSE
class Echéancier
{
    private:
    // VARIABLES

    public:
    // CONSTRUCTEURS
    Echéancier()
    {}

    // DESTRUCTEUR
    ~Echéancier()
    {}

    // METHODES
    /*
    Fonction de type void pour ne rien renvoyer.
    Argument de type des variables d'un réseau de Petri du Moteur.
    La fonction enregistre les différents états du réseau à chaque tour.
    */
    void StockeurReseau(int S, int T, float *P, int **F, int *M, int **W, int *K)
    {}

    /*
    Fonction de type void pour ne rien renvoyer.
    Aucun argument nécessaire.
    La fonction étiquette chaque état du réseau enregistré avec un temps arbitraire.
    */
    void StockeurTemps()
    {}

    /*
    Fonction de type int pour renvoyer le temps s'il existe ou le dernier temps stocké s'il n'existe pas.
    Argument de type int Te, le temps auquel on veut récupérer le réseau de Petri.
    La fonction recherche un état du réseau enregistré avec un temps donné et le renvoie.
    */
    int RechercheTemps(int Te)
    {}

    /*
    Fonction de type Moteur pour renvoyer le réseau de Petri stocké.
    Argument de type int Te, le temps auquel on veut récupérer le réseau de Petri.
    La fonction renvoie au Moteur et/ou l'InterfaceGraphique un état du réseau enregistré à l'état demandé.
    */
    Moteur RenvoiEtatResau(int Te)
    {}

}

#endif
