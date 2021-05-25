// LIBRAIRIES
#include "Echeancier.hpp" // Pour utiliser la classe Echeancier
#include "GestionnaireDeFichiers.hpp" // Pour utiliser la classe GestionnaireDeFichiers
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include "InterfaceGraphique.hpp" // Pour utiliser la classe InterfaceGraphique

// FONCTIONS

// MAIN
int main()
{
	// Utilisation de l'interface graphique
	QApplication app(argc, argv);

    InterfaceGraphique fenetre;
    fenetre.setMoteur(M);
    
    fenetre.show();
    
    return app.exec();
}