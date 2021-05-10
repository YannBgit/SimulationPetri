#include "MaFenetre.hpp"
/*
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include "Echancier.hpp" // Pour utiliser la classe Echancier
#include "GestionnaireDeFichiers.hpp" // Pour utiliser la classe GestionnaireDeFichiers
*/



// CREATION DES SLOTS
void InterfaceGraphique::fct_etatInitial(/*QPushButton etatInitial, Moteur M, Echeancier E*/)
{
    /*QObject::connect(enregistrer, SIGNAL(clicked()), qApp, SLOT(EnregisterEcheancier(FILE *temp, FILE *fichier)));
    affichage_echeancier(M);*/
    exit(1);
}

void InterfaceGraphique::fct_enregistrer(/*QPushButton enregistrer, Moteur M, FILE *temp, FILE *fichier*/)
{
    /*QObject::connect(enregistrer, SIGNAL(clicked()), qApp, SLOT(EnregisterEcheancier(FILE *temp, FILE *fichier)));
    affichage_echeancier(M);*/
    exit(0);
}

void InterfaceGraphique::fct_charger(/*QPushButton charger, Moteur M, FILE *fichier*/)
{
    /*QObject::connect(charger, SIGNAL(clicked()), qApp, SLOT(Charger(FILE*)));
    affichage_echeancier(M);*/
    exit(1);
}

void InterfaceGraphique::fct_avancer(/*QPushButton avancer, Moteur M, Echeancier E*/)
{
    /*QObject::connect(avancer, SIGNAL(clicked()), qApp, SLOT(E.RenvoyerEtatReseauSelonTemps(M.Te+1)));
    affichage_echeancier(M);*/
    exit(1);
}

void InterfaceGraphique::fct_reculer(/*QPushButton reculer, Moteur M, Echeancier E*/)
{
    /*QObject::connect(reculer, SIGNAL(clicked()), qApp, SLOT(E.RenvoyerEtatReseauSelonTemps(M.Te-1)));
    affichage_echeancier(M);*/
    exit(1);
}




InterfaceGraphique::InterfaceGraphique() : QWidget()
{
    setFixedSize(1500, 800);
    setWindowTitle("Simulateur de Rdp");



    // CONSTRUCTION DES BOUTONS
    etatInitial = new QPushButton("ETAT INITIAL", this);
    enregistrer = new QPushButton("ENREGISTRER", this);
    charger = new QPushButton("CHARGER", this);
    avancer = new QPushButton("AVANCER", this);
    reculer = new QPushButton("RECULER", this);



    // PERSONNALISATION DES BOUTONS

            // Changement de la largeur minimale des boutons
    enregistrer->setMinimumWidth(240);
    charger->setMinimumWidth(240); //On assigne cette largeur minimale seulement à ces 2 boutons car c'est suffisant pour que les autres soit aussi modifiés

            // Changement de la hauteur des boutons
    enregistrer->setMinimumHeight(90);
    charger->setMinimumHeight(90);
    avancer->setMinimumHeight(90);
    reculer->setMinimumHeight(90);
    etatInitial->setMinimumHeight(90);

        // Changement de police et de taille
    etatInitial->setFont(QFont("Lato Light",17));
    enregistrer->setFont(QFont("Lato Light",17));
    charger->setFont(QFont("Lato Light",17));
    avancer->setFont(QFont("Lato Light",17));
    reculer->setFont(QFont("Lato Light",17));



    // CREATION DU LAYOUT GRID POUR LES BOUTONS ET AJOUT DES WIDGETS BOUTONS
    QGridLayout *glayout = new QGridLayout;

    glayout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    glayout->addWidget(enregistrer,2,0);
    glayout->addWidget(charger,2,1);
    glayout->addWidget(avancer,1,0);
    glayout->addWidget(reculer,1,1);
    glayout->addWidget(etatInitial,0,0,1,2);



    // AFFICHAGE DE L'ECHEANCIER
    QLabel *echeancier = new QLabel("Affichage de l'échéancier au temps Te = a :", this);

    echeancier->setFont(QFont("Lato Light", 15));
    echeancier->setMaximumWidth(500);



    // CREATION DU LAYOUT POUR L'AFFICHAGE DE L'ÉCHEANCIER ET AJOUT DU WIDGET TEXTE
    QVBoxLayout *vlayout = new QVBoxLayout;

    vlayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    vlayout->addWidget(echeancier);



    // CREATION DES LAYOUT PRINCIPAL
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;



    // AJOUT DES LAYOUTS DANS LE LAYOUT PRINCIPAL
    layoutPrincipal->addLayout(vlayout,50); //Ajout du Layout Vertical "vlayout"
    layoutPrincipal->addLayout(glayout); //Ajout du Layout Grid "glayout"

    setLayout(layoutPrincipal);

    QObject::connect(etatInitial, SIGNAL(clicked()), this, SLOT(fct_etatInitial()));
    QObject::connect(enregistrer, SIGNAL(clicked()), this, SLOT(fct_enregistrer));
    QObject::connect(charger, SIGNAL(clicked()), this, SLOT(fct_charger()));
    QObject::connect(avancer, SIGNAL(clicked()), this, SLOT(fct_avancer()));
    QObject::connect(reculer, SIGNAL(clicked()), this, SLOT(fct_reculer()));
}
