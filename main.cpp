// LIBRAIRIES
#include "Echeancier.hpp" // Pour utiliser la classe Echeancier
#include "GestionnaireDeFichiers.hpp" // Pour utiliser la classe GestionnaireDeFichiers
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include "InterfaceGraphique.hpp" // Pour utiliser la classe InterfaceGraphique

// FONCTIONS

// MAIN
int main()
{
    // Initialisation du gestionnaire de fichiers et de l'échéancier
    FILE *RdP;
    GestionnaireDeFichiers GDF(RdP);
    Echeancier E(GDF);

    // Initialisation du moteur et de l'interface graphique
    Moteur EtatInitial = E.E.RenvoyerEtatReseauCourant();
    Moteur M(EtatInitial.S, EtatInitial.T, EtatInitial.P, EtatInitial.F, EtatInitial.M, EtatInitial.W, EtatInitial.K);
    InterfaceGraphique IG();

    return 0;
}