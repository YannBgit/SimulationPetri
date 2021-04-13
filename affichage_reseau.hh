#ifndef AFFICHAGE_RESEAU.HH
#define AFFICHAGE_RESEAU.HH

/* Classe s'occupant de la représentation graphique de l'état d'un réseau à un instant T*/
class AfficheurDeReseau {

    public :
        //Constructeur
        AfficheurDeReseau();
        //Destructeur
        ~AfficheurDeReseau();

        /*  Crée un Element pour chaque place et chaque transitions, avec son nombre de jeton, son type (place ou transition) et 
            une position x-y définit par rapport au premier qui est rencontré (position (0,0)) et parts ses liaisons et renvoie 
            la liste de ces éléments.
            La liste contient les places puis les transitions dans l'ordre  */
        Element* buildElementsPosition(int S, int T, int **F, int *M), [params];

        /*  Dessine les places et les transitions */
        void dessinerElements(Element *elements, int *M);

        /*  Dessine les arcs entre les places et les transitions*/
        void dessinerArcs(int ***arcs);

        /*  Définit pour chaque arc une liste de position contenant au moins celles d'une place et d'une transition pour les relier, 
            en évitant  de passer sur d'autres places et transitions */
        int*** calculerArcs(Element *elements, int **F, [params]);

        /*  Récupère le nouvel état du réseau et modifie le nombre de jeton pour chaque élément graphique où c'est nécessaire*/
        void miseAJourReseau(Element *elements, int *M)
    
    private :

        /*  Utilisée par calculerArcs(). Renvoie des points de passages (x,y) permettant à l'arc en cours de calcul de ne pas intersecter avec une 
            place ou une transition */
        int** eviterIntersection(Element *elments, int x_depart, int y_depart, int x_arrivee, int y_arrive);

        /*  On stocke les positions d'affichage des places, transitions et arcs pour ne pas les recalculer à chaque changement du réseau
            tel que l'évolution de la positions des jetons mais seuelemnt en cas de modification d ela structure du réseau */

        /*  Stocke les places et les transitions (dans cette ordre) */
        Element *elements;
        /*  Stocke les transitions, chacune correspondant à une liste de couple d'entier x,y */
        int*** arcs;

        /*  Variables encore non définit qui définirontl'aspect du réseau (espace entre deux élément, taille d'une place, couleur, etc...) */
        //[params]
};

class Element {
    public :
        //Constructeur
        Element();
        //Destructeur
        ~Element();

        /*Dessine l'élément selon sa positon et son type d'élement ainsi que les jetons qu'il contient*/
        void dessiner();

        void setNbJetons(int n);

    private :
        typedef enum
        {
            Transition,
            Place
        }TypeElement;

        int pos_x;
        int pos_y;
        int nb_jetons;

};

#endif // MAFFICHAGE_RESEAU.HH
