// DIRECTIVES
#ifndef INTERFACEGRAPHIQUE_HPP
#define INTERFACEGRAPHIQUE_HPP

// LIBRAIRIES
#include <QApplication> // QApplication est l'include de base de tout programme Qt
#include <QObject> // QObject est la classe de base de tous les objets sous Qt. La méthode connect() nous sera particulièrement utile pour les signaux et les slots
#include <QtWidgets> // QtWidgets est un module qui nous permettera d'afficher nos fenêtres
#include <QPushButton> // QPushButton nous permet de créer des objets QPushButton étant tout simplement des boutons
#include <QLabel> // QLabel est utilisé pour afficher du texte ou une image. Cette classe nous sera utile pour l'affichage de l'échéancier.
#include <QLayout> // QLayout nous permet de postionner nos widgets, comme par exemple, nos boutons.
#include <QGroupBox> //QGroupBox fournit une "box" correspondant à un groupe avec un titre.
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include "Echancier.hpp" // Pour utiliser la classe Echancier
#include "GestionnaireDeFichiers.hpp" // Pour utiliser la classe GestionnaireDeFichiers

// CLASSE
class InterfaceGraphique
{
    private:
    // VARIABLES
    QPushButton *reculer; //associé à la méthode "fct_reculer();"
	QPushButton *avancer; //associé à la méthode "fct_avancer();"
	QPushButton *enregistrer; //associé à la méthode "fct_enregistrer();"
    QPushButton *charger; //associé à la méthode "fct_charger();"
    
    QVBoxLayout *vlayout; //Layout vertical
    QHBoxLayout *hlayout; //Layout horizontal

    public:
    // CONSTRUCTEURS
    InterfaceGraphique();

    // DESTRUCTEUR
    ~InterfaceGraphique();

    // METHODES
    /*
    Cette fonction servira à l'affichage de l'échéancier sous forme de texte.
    Nous avons comme argument un Moteur, qui nous est envoyé par l'Echéancier, comportant toutes les infos nécéssaires à l'affichage de ce dernier.
    */
    void affichage_echeancier(Moteur M)
    {}

	/*
	Cette fonction servira pour passer de l'affichage d'un temps Te à un temps Te-1. Si le bouton "reculer" est cliqué, la fonction affichera le Rdp et l'échéancier au temps Te-1.
	Ceci sera notamment possible grâce à la fonction "E.RenvoyerEtatReseauSelonTemps(M.Te-1);".
	*/
	void fct_reculer();
	
	/*
	Cette fonction servira pour passer de l'affichage d'un temps Te à un temps Te-1. Si le bouton "avancer" est cliqué, la fonction affichera le Rdp et l'échéancier au temps Te+1.
	Ceci sera notamment possible grâce à la fonction "E.RenvoyerEtatReseauSelonTemps(M.Te+1);".
	*/
    void fct_avancer();
    
    /*
    Cette fonction servira à l'utilisateur d'enregistrer l'état du Rdp à l'aide du gestionnaire de fichiers, si le bouton "enregister" est cliqué.
    Ceci sera notamment possible grâce à la fonction "Charger(FILE *fichier);"
    */
    void fct_enregistrer();
    
    /*
    Cette fonction permettera à l'utilisateur de charger des paramètre du réseau de Pétri à l'aide du gestionnaire de fichiers, si le bouton est cliqué.
    Ceci sera notamment possible grâce à la fonction "EnregisterEcheancier(FILE *temp, FILE *fichier);
    */
    void fct_charger();

    /*
    Crée un Element pour chaque place et chaque transitions, avec son nombre de jeton, son type (place ou transition) et une position {x, y} définit par
    rapport au premier qui est rencontré (position (0,0)) et par ses liaisons et renvoie la liste de ces éléments.
    La liste contient les places puis les transitions dans l'ordre.
    */
    Element* buildElementsPosition(int S, int T, int **F, int *M, [params]);

    /*
    Dessine les places et les transitions.
    */
    void dessinerElements(Element *elements, int *M);

    /*
    Dessine les arcs entre les places et les transitions.
    */
    void dessinerArcs(int ***arcs);

    /*
    Définit pour chaque arc une liste de positions contenant au moins celles d'une place et d'une transition pour les relier, en évitant de passer sur
    d'autres places et transitions.
    */
    int*** calculerArcs(Element *elements, int **F, [params]);

    /*
    Récupère le nouvel état du réseau et modifie le nombre de jetons pour chaque élément graphique où c'est nécessaire.
    */
    void miseAJourReseau(Element *elements, int *M);
    
    /*
    Utilisée par calculerArcs(). Renvoie des points de passages (x, y) permettant à l'arc en cours de calcul de ne pas intersecter avec une place ou une transition.
    */
    int** eviterIntersection(Element *elments, int x_depart, int y_depart, int x_arrivee, int y_arrive);

    /*
    On stocke les positions d'affichage des places, transitions et arcs pour ne pas les recalculer à chaque changement du réseau tel que l'évolution de la
    positions des jetons mais seulement en cas de modification de la structure du réseau.
    */

    /*
    Stocke les places et les transitions (dans cette ordre).
    */
    Element *elements;
    
    /*
    Stocke les transitions, chacune correspondant à une liste de couples d'entiers x, y.
    */
    int*** arcs;

    /*
    Variables encore non définies qui définiront l'aspect du réseau (espace entre deux élément, taille d'une place, couleur, etc...).
    */
    //[params]
}

class Element
{
    private :
    typedef enum
    {
        Transition,
        Place
    }TypeElement;

    int pos_x;
    int pos_y;
    int nb_jetons;

    public :
    // Constructeur
    Element();
    // Destructeur
    ~Element();

    /*
    Dessine l'élément selon sa positon et son type d'élement ainsi que les jetons qu'il contient.
    */
    void dessiner();

    void setNbJetons(int n);
}

#endif
