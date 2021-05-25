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
#include <QGraphicsItem>    //Permet de gérer les collisions entre éléments graphiques
#include "Moteur.hpp" // Pour utiliser la classe Moteur
#include "Echeancier.hpp" // Pour utiliser la classe Echancier
#include "GestionnaireDeFichiers.hpp" // Pour utiliser la classe GestionnaireDeFichiers

#include <stdio.h>
#include <cmath>

class Element;

// CLASSE
class InterfaceGraphique : public QWidget //On hérite de QWidget
{
	Q_OBJECT

    private:
    // VARIABLES
    QPushButton *reculer; // Associé à la méthode "fct_reculer()"
    QPushButton *avancer; // Associé à la méthode "fct_avancer()"
    QPushButton *enregistrer; // Associé à la méthode "fct_enregistrer()"
    QPushButton *charger; // Associé à la méthode "fct_charger()"
    QPushButton *etatInitial; // Associé à la méthode "fct_etatInitial()"
    
    QVBoxLayout *vlayout; // Layout vertical
    QVBoxLayout *layoutSecondaire;
    QHBoxLayout *layoutPrincipal; // Layout horizontal
    QGridLayout *glayout; // Layout sous forme de tableau
    
    QLabel *echeancierintro;
    QLabel *tabproba;
	QLabel *tabarcs;
	QLabel *tabjetcontenu;
	QLabel *tabjetcg;
	QLabel *tabjetmax;

    QGraphicsScene *afficheur_reseau;

    // Les fonctions situées ici indiquent à QT qu'elles peuvent être utilisées pour recevoir les signaux envoyés par les boutons

    private slots :
    /*
    Cette fonction servira pour passer de l'affichage d'un temps quelconque au temps 0 (etat initial). Si le bouton "etatInitial" est
    cliqué, la fonction affichera le Rdp et l'échéancier au temps 0.
    Ceci sera notamment possible grâce à la fonction "E.RenvoyerEtatReseauSelonTemps(0)".
    */
    void fct_etatInitial();
    /*
    Cette fonction servira pour passer de l'affichage d'un temps Te à un temps Te+1. Si le bouton "avancer" est cliqué, la fonction
    affichera le Rdp et l'échéancier au temps Te+1.
    Ceci sera notamment possible grâce à la fonction "E.RenvoyerEtatReseauSelonTemps(M.Te+1)".
    */
    void fct_avancer();

    /*
    Cette fonction servira pour passer de l'affichage d'un temps Te à un temps Te-1. Si le bouton "reculer" est cliqué, la fonction
    affichera le Rdp et l'échéancier au temps Te-1.
    Ceci sera notamment possible grâce à la fonction "E.RenvoyerEtatReseauSelonTemps(M.Te-1)".
    */
    void fct_reculer();

    /*
    Cette fonction permettera à l'utilisateur de charger des paramètre du réseau de Pétri à l'aide du gestionnaire de fichiers si le
    bouton est cliqué.
    Ceci sera notamment possible grâce à la fonction "EnregisterEcheancier(FILE *temp, FILE *fichier)".
    */
    void fct_charger();

    /*
    Cette fonction servira à l'utilisateur pour enregistrer l'état du Rdp à l'aide du gestionnaire de fichiers, si le bouton
    "enregister" est cliqué.
    Ceci sera notamment possible grâce à la fonction "Charger(FILE *fichier)".
    */
    void fct_enregistrer();

    public:
    // CONSTRUCTEURS
    InterfaceGraphique();

    // DESTRUCTEUR
    ~InterfaceGraphique()
    {
        free(elements);
    }

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

    // METHODES  

    // Affichage echeancier
    /*
    Cette fonction servira à l'affichage de l'échéancier sous forme de texte.
    */
    void affichage_echeancier();

    // Affichage reseau
    /*
    Crée un Element pour chaque place et chaque transitions, avec son nombre de jetons, son type (place ou transition) et une position
    {x, y} définit par rapport au premier qui est rencontré (position (0,0)) et par ses liaisons et renvoie la liste de ces éléments.
    La liste contient les places puis les transitions dans l'ordre. Appellée lors du chargement d'un réseau.
    */
    void buildElementsPosition();

     /*
    Utiliser par buildElementsPosition(). Permet de vérifier si une place ou transition est déjà dans a_traiter
    */
    bool isContainedBy(int* tuple, std::list<int*>);

    /*
    Dessine les places et les transitions contenues dans elements.
    */
    void dessinerElements();

    /*
    Définit pour chaque arc une liste de positions contenant au moins celles d'une place et d'une transition pour les relier, en
    évitant de passer sur d'autres places et transitions.
    */
    void calculerArcs();  

   /*
    Dessine les arcs entre les places et les transitions.
    */
    void dessinerArcs();

    /*
    Récupère le nouvel état du réseau et modifie le nombre de jetons pour chaque élément graphique où c'est nécessaire. Appellée lors
    d'un déplacement dans le réseau.
    */
    void miseAJourReseau();
        
     /*
    Utilisée par calculerArcs(). Renvoie des points de passage (x, y) permettant à l'arc en cours de calcul de ne pas intersecter avec
    une place ou une transition.
    */
    int **eviterIntersection(int x_depart, int y_depart, int x_arrivee, int y_arrivee);

    /*
    On stock les positions d'affichage des places, transitions et arcs pour ne pas les recalculer à chaque changement d'état du réseau
    avec l'évolution de la position des jetons mais seulement en cas de modification de la structure du réseau.
    */
    /*
    Stock les places et les transitions (dans cette ordre).
    */
    Element **elements;
        
    /*
    Liste stockant les arcs, un arcs (int**) correspondant à la liste des points formant ses segments, et se terminant par nullptr.
    Un point (int*) contient les coordonnées x et y dans cet ordre d'une extrémitée d'un segment.
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
        pos_x = x;
        pos_y = y;
        this->type = type;
    }

    /*
    Constructeur (si c'est une place)
    */
    Element(int x, int y, bool type, int nb_jetons)
    {
        pos_x = x;
        pos_y = y;
        this->type = type;
        this->nb_jetons = nb_jetons;
    }

    // DESTRUCTEUR
    ~Element();

    // METHODES

    /*
    Dessine l'élément selon sa position et son type d'élément ainsi que les jetons qu'il contient et les paramètres.
    */
    void dessiner(InterfaceGraphique::Params params)
    {   
        QGraphicsScene *afficheur_reseau;
        float pos_x_scene, pos_y_scene, size;
        size = params.tailleElement;    //stocke le diamètre de la place
        if (type) {
            pos_x_scene = pos_x*size+pos_x*params.elementsDistance; //Position en x de la place sur la scene (l'écran)
            pos_y_scene = pos_y*size+pos_y*params.elementsDistance; //Position en y de la place sur la scene (l'écran)
            afficheur_reseau->addEllipse(pos_x_scene, pos_y_scene,
                size, size,
                QPen(Qt::black,2)
            );

            if (nb_jetons) {
                if (nb_jetons == 1) {                              
                    afficheur_reseau->addEllipse(pos_x_scene+size/4, pos_y_scene+size/4,
                    params.tailleElement/2, params.tailleElement/2,                     //si on essayait de répartir un ou deux jetons on aurait
                    QPen(Qt::black,2), QBrush(Qt::SolidPattern)                         //des erreurs avec les fonctions cosinus et sinus etc...
                );                                                                      //car 
                }else if (nb_jetons == 2 && size > 6) {
                    afficheur_reseau->addEllipse(pos_x_scene+3, pos_y_scene+params.tailleElement/4+3,
                    size/2-6, size/2-6,
                    QPen(Qt::black,2), QBrush(Qt::SolidPattern)
                    );
                    afficheur_reseau->addEllipse(pos_x_scene+params.tailleElement/2+3, pos_y_scene+params.tailleElement/4+3,
                    params.tailleElement/2-6, params.tailleElement/2-6,
                    QPen(Qt::black,2), QBrush(Qt::SolidPattern)
                    );
                } else {
                    double r_token, ln_base, ln_cote, angle, d_token, x_token, y_token;//On dessine les tokens présents dans la place en les répartissants comme cercles inscrits dans nb_jetons triangles isocèles
                    angle = (2*M_PI)/nb_jetons, ln_cote = size/2;   //Angle du haut des triangles et longeur des cotés (rayon de la place)
                    ln_base = (ln_cote * sin(angle) / sin((M_PI-angle) /2));        //Longeur de la base des tiangles
                    r_token = (ln_base/2) * sqrt((2*ln_cote-ln_base) / (2*ln_cote+ln_base));  //rayon d'un token
                    d_token = sqrt( abs(ln_cote*ln_cote - pow(ln_base/2,2))) - r_token;      //distance du centre du token au centre de la place (h_triangle-r_token)

                    r_token *= 1 + 5/(pow(nb_jetons,2.0));
                    d_token *= 1 + 20/(pow(nb_jetons,2.9));

                    for(int i=0;i<nb_jetons;i++) {
                        x_token = pos_x_scene+size/2-r_token + d_token*cos(angle*i) +2;
                        y_token = pos_y_scene+size/2-r_token + d_token*sin(angle*i) +2;
                        afficheur_reseau->addEllipse(x_token, y_token,
                            (r_token-2)*2, (r_token-2)*2,
                            QPen(Qt::black,2), QBrush(Qt::SolidPattern)
                        );
                    }
                }
            }


        } else {
            afficheur_reseau->addRect(pos_x*size+pos_x*params.elementsDistance,
                pos_y*size+pos_y*params.elementsDistance+(3.0/8.0)*size,
                size, size/4.0,
                QPen(), QBrush(Qt::SolidPattern)
            );
        }
    }

    /*
    Utilisé par miseAJourReseau() pour changer le nombre de jetons si l'élément est une place.
    */
    void setNbJetons(int n)
    {
        nb_jetons = n;
    }

    /*
    Renvoie la valeur de type.
    */
    bool isPlace()
    {
        return type;
    }

    /*
    Accesseurs pour les variables.
    */
    int getPosX()
    {
        return pos_x;
    }

    int getPosY()
    {
        return pos_y;
    }

    int getNbJetons()
    {
        return nb_jetons;
    }
};

#endif
