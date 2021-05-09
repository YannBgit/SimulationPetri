// DIRECTIVES
#ifndef INTERFACEGRAPHIQUE_HPP
#define INTERFACEGRAPHIQUE_HPP

// LIBRAIRIES
#include <QApplication> // QApplication est l'include de base de tout programme Qt
#include <QObject> // QObject est la classe de base de tous les objets sous Qt. La méthode connect() nous sera particulièrement utile
// pour les signaux et les slots.
#include <QWidget> // QWidgets est un module qui nous permettera d'afficher nos fenêtres
#include <QPushButton> // QPushButton nous permet de créer des objets QPushButton qui sont tout simplement des boutons
#include <QLabel> // QLabel est utilisé pour afficher du texte ou une image. Cette classe nous sera utile pour l'affichage de
// l'échéancier.
#include <QLayout> // QLayout nous permet de postionner des widgets, comme par exemple, nos boutons
#include <QGraphicsView> // Permet d'afficher une scène avec beaucoup d'options
#include <QGraphicsScene> // Permet de dessinner le réseau de Pétri sur une scène
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include "Echancier.hpp" // Pour utiliser la classe Echancier
#include "GestionnaireDeFichiers.hpp" // Pour utiliser la classe GestionnaireDeFichiers

// CLASSE
class InterfaceGraphique
{
    private:
    // VARIABLES
    QPushButton *reculer; // Associé à la méthode "fct_reculer()"
    QPushButton *avancer; // Associé à la méthode "fct_avancer()"
    QPushButton *enregistrer; // Associé à la méthode "fct_enregistrer()"
    QPushButton *charger; // Associé à la méthode "fct_charger()"
    QPushButton *etatInitial; // Associé à la méthode "fct_etatInitial()"
    
    QVBoxLayout *vlayout; // Layout vertical
    QHBoxLayout *hlayout; // Layout horizontal
    QGridLayout *glayout; // Layout sous forme de tableau

    /*
    Variables qui définisent l'aspect du réseau (espace entre deux élément, taille d'une place, couleur, etc...).
    */
    struct Params
    {
        float tailleElement; // Taille d'un element (multiplicateur)
        float elementsDistance; // Distance minimale séparant deux éléments graphiques
        float largeurTrait;
        QColor couleurTrait;
        QColor couleurRemplissage;
    };
    Params parametres;

    public:
    // CONSTRUCTEURS
    InterfaceGraphique()
    {

    }

    // DESTRUCTEUR
    ~InterfaceGraphique();

    // METHODES

    // Les fonctions situées ici indiquent à QT qu'elles peuvent être utilisées pour recevoir les signaux envoyés par les boutons
    private slots :
    /*
    Cette fonction servira pour passer de l'affichage d'un temps quelconque au temps 0 (etat initial). Si le bouton "etatInitial" est
    cliqué, la fonction affichera le Rdp et l'échéancier au temps 0.
    Ceci sera notamment possible grâce à la fonction "E.RenvoyerEtatReseauSelonTemps(0)".
    */
    void fct_etatInitial()
    {

    }

    /*
    Cette fonction servira pour passer de l'affichage d'un temps Te à un temps Te+1. Si le bouton "avancer" est cliqué, la fonction
    affichera le Rdp et l'échéancier au temps Te+1.
    Ceci sera notamment possible grâce à la fonction "E.RenvoyerEtatReseauSelonTemps(M.Te+1)".
    */
    void fct_avancer()
    {

    }

    /*
    Cette fonction servira pour passer de l'affichage d'un temps Te à un temps Te-1. Si le bouton "reculer" est cliqué, la fonction
    affichera le Rdp et l'échéancier au temps Te-1.
    Ceci sera notamment possible grâce à la fonction "E.RenvoyerEtatReseauSelonTemps(M.Te-1)".
    */
    void fct_reculer()
    {

    }

    /*
    Cette fonction permettera à l'utilisateur de charger des paramètre du réseau de Pétri à l'aide du gestionnaire de fichiers si le
    bouton est cliqué.
    Ceci sera notamment possible grâce à la fonction "EnregisterEcheancier(FILE *temp, FILE *fichier)".
    */
    void fct_charger()
    {

    }

    /*
    Cette fonction servira à l'utilisateur pour enregistrer l'état du Rdp à l'aide du gestionnaire de fichiers, si le bouton
    "enregister" est cliqué.
    Ceci sera notamment possible grâce à la fonction "Charger(FILE *fichier)".
    */
    void fct_enregistrer()
    {

    }

    // Affichage echeancier
    /*
    Cette fonction servira à l'affichage de l'échéancier sous forme de texte.
    Nous avons comme argument un Moteur, qui nous est envoyé par l'Echéancier, comportant toutes les infos nécessaires à l'affichage
    de ce dernier.
    */
    void affichage_echeancier(Moteur M)
    {

    }

    /*
    Donne sa valeur à la variable M, fournie par l'échéancier.
    */
    void setMoteur(Moteur new_moteur)
    {

    }

    // Affichage reseau
    /*
    Crée un Element pour chaque place et chaque transitions, avec son nombre de jetons, son type (place ou transition) et une position
    {x, y} définit par rapport au premier qui est rencontré (position (0,0)) et par ses liaisons et renvoie la liste de ces éléments.
    La liste contient les places puis les transitions dans l'ordre. Appellée lors du chargement d'un réseau.
    */
    Element* buildElementsPosition(Moteur M)
    {

    }

    /*
    Dessine les places et les transitions contenues dans elements.
    */
    void dessinerElements(Element *elements)
    {

    }

    /*
    Définit pour chaque arc une liste de positions contenant au moins celles d'une place et d'une transition pour les relier, en
    évitant de passer sur d'autres places et transitions.
    */
    int ***calculerArcs(Element *elements, Moteur M, [params])
    {

    }

    /*
    Dessine les arcs entre les places et les transitions.
    */
    void dessinerArcs(int ***arcs)
    {

    }

    /*
    Récupère le nouvel état du réseau et modifie le nombre de jetons pour chaque élément graphique où c'est nécessaire. Appellée lors
    d'un déplacement dans le réseau.
    */
    void miseAJourReseau(Element *elements, Moteur M)
    {

    }
        
    /*
    Utilisée par calculerArcs(). Renvoie des points de passage (x, y) permettant à l'arc en cours de calcul de ne pas intersecter avec
    une place ou une transition.
    */
    int **eviterIntersection(Element *elments, int x_depart, int y_depart, int x_arrivee, int y_arrivee, Params params)
    {

    }

    /*
    On stock les positions d'affichage des places, transitions et arcs pour ne pas les recalculer à chaque changement d'état du réseau
    avec l'évolution de la position des jetons mais seulement en cas de modification de la structure du réseau.
    */
    /*
    Stock les places et les transitions (dans cette ordre).
    */
    Element *elements;
        
    /*
    Stock les transitions, chacune correspondant à une liste de couples d'entiers x, y.
    */
    int ***arcs;
};

/*
Stock et dessine une place ou une transition avec ses données d'affichage
*/
// CLASSE
class Element
{
    private :
    int pos_x; // Position x relative au 1er élément
    int pos_y; // Position y relative au 1er élément
    int nb_jetons; // Nb de jetons actuellement contenus dans l'élément si c'est une place
    bool type; // Définit s'il s'agit d'une place (1) ou d'une transition (0)

    public :
    // CONSTRUCTEURS
    /*
    Constructeur de base
    */
    Element(int x, int y, bool type)
    {

    }

    /*
    Constructeur (si c'est une place)
    */
    Element(int x, int y, bool type, int nb_jetons)
    {

    }

    // DESTRUCTEUR
    ~Element();

    // METHODES

    /*
    Dessine l'élément selon sa position et son type d'élément ainsi que les jetons qu'il contient et les paramètres.
    */
    void dessiner(Params params)
    {

    }

    /*
    Utilisé par miseAJourReseau() pour changer le nombre de jetons si l'élément est une place.
    */
    void setNbJetons(int n)
    {

    }

    /*
    Renvoie la valeur de type.
    */
    bool isPlace()
    {

    }

    /*
    Accesseurs pour les variables.
    */
    int getPosX();

    int getPosY();

    int getNbJetons();
};

#endif