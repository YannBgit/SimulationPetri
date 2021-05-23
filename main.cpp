/*// LIBRAIRIES
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
}*/

#include "InterfaceGraphique.hpp"

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow *w = new QMainWindow();
    QGraphicsScene *s = new QGraphicsScene();
    QGraphicsView *v = new QGraphicsView();
    v->setScene(s);


    Element *truc = new Element(0,0,1);
    Element *machin = new Element(0,1,0);
    InterfaceGraphique::Params params;
    params.elementsDistance = 25;
    params.tailleElement = 50;

    InterfaceGraphique::Moteur M = {4,2,{{0,0,0},{1,1,0},{1,2,0},{0,1,1},{0,2,1},{1,3,1},{1,0,1}},{2,1,0,1},7};
    

    printf("taille : %d\n",sizeof(M.F) / sizeof(M.F[0]));

    InterfaceGraphique test;
    test.parametres = params;

    test.setMoteur(M);

    test.buildElementsPosition();

    test.dessinerElements(s);
    printf("là ?\n");

    test.calculerArcs();

    test.dessinerArcs(s);

    //truc->dessiner(s, params);
    //machin->dessiner(s, params);

    w->setCentralWidget(v);
    w->show();

    return a.exec();
}