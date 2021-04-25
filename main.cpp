// LIBRAIRIES
#include "Echeancier.hpp" // Pour utiliser la classe Echeancier
#include "GestionnaireDeFichiers.hpp" // Pour utiliser la classe GestionnaireDeFichiers
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include "InterfaceGraphique.hpp" // Pour utiliser la classe InterfaceGraphique

// FONCTIONS

// MAIN
int main()
{
    FILE *RdP;

    GestionnaireDeFichiers GDF(RdP);
    Echeancier E(GDF);
    Moteur M(E.RenvoyerEtatReseauCourant());
    InterfaceGraphique IG();

    return 0;
}