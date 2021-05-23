#include "InterfaceGraphique.hpp"
//#include "MaFenetre.hpp"
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

void InterfaceGraphique::buildElementsPosition() 
{       
        int nb_arcs = sizeof(M.F) / sizeof(M.F[0]);
        int matrice_arcs[M.S][M.T];
        for (int i=0;i<M.S;i++) {
            for (int y=0;y<M.T;y++) {
                matrice_arcs[i][y] = 0;
            }
        }

        for (int i=0;i<nb_arcs;i++) {
            matrice_arcs[M.F[i][1]][M.F[i][2]] = (M.F[i][0] ? -1 : 1);
        }
        //printf("Matrice créée!\n");

        /*for (int y=0;y<M.T;y++) {
            printf("[");
            for (int i=0;i+1<M.S;i++) {
                printf("%2d",matrice_arcs[i][y]);
            }
            printf("%2d]\n",matrice_arcs[M.S-1][y]);
        }*/

        Element **truc = (Element**)malloc(sizeof(Element*)*(M.S+M.T));
        std::vector<int> transition_enfants;

        for (int i=0;i<M.S+M.T;i++) {
            truc[i] = nullptr;
        }

        std::list<int*> a_traiter;
        int* tuple = (int*)malloc(sizeof(int)*2);
        int curr_size, i,j, curr_center, curr_y, parent_center = 0, parent_y = -1, decalage;
        tuple[0] = 0, tuple[1] = 1;

        a_traiter.push_front(tuple);

        while (!a_traiter.empty()) {
            //printf("Nouveau tour //////////////////////////////////////////////////\n");
            curr_size = a_traiter.size();
            decalage = curr_size/2;
            curr_center = 0;
            for (i=0;i<curr_size;i++) {
                if (i-decalage == 0 && curr_size%2 == 0) decalage--;

                if (a_traiter.back()[1]) {  //Si le dernier élménet à traiter est une place
                    //printf("Lélément est une place !\n");
                    for (j=0;j<M.T;j++) {                                                               //On ajoute toutes les transitions 
                        if (matrice_arcs[a_traiter.back()[0]][j] == 1 && truc[M.S+j] == nullptr ) {      //liées depuis cette place
                            tuple = (int*)malloc(sizeof(int)*2);                                        //
                            tuple[0] = j, tuple[1] = 0;                                                 //
                            if (isContainedBy(tuple, a_traiter)) {
                                free(tuple);
                            } else {
                                a_traiter.push_front(tuple); 
                            }
                        }
                    }

                    truc[a_traiter.back()[0]] = new Element(parent_center+i-decalage, parent_y+1, 1, M.M[a_traiter.back()[0]]);
                    if (i == 0 || i == curr_size-1) {                               //puis on crée et met l'élément correspondant à la place
                        if (i == curr_size-1) curr_y = truc[a_traiter.back()[0]]->getPosY();          //  //dans la liste des éléments visuels.
                        curr_center += truc[a_traiter.back()[0]]->getPosX();    //On récupère ici la position en y des éléments traités ce 
                        //printf("current center : %d\n",curr_center);
                    }                                                           //tour de boucle ci ainsi que le milieu de leurs x
                    free(a_traiter.back());                                         //
                    a_traiter.pop_back();                                           //enfin on supprime compléement le tuple de la liste
                                                                                    // a_traiter
                } else {                    //Si c'est une transition
                    //printf("Lélément est une transition !\n");
                    for (j=0;j<M.S;j++) {                                                                       //
                        if (matrice_arcs[j][a_traiter.back()[0]] == -1 && truc[j] == nullptr) {                 //
                            tuple = (int*)malloc(sizeof(int)*2);                                                //
                            tuple[0] = j, tuple[1] = 1;                                                         //
                            if (isContainedBy(tuple, a_traiter)) {
                                free(tuple);
                            } else {
                                a_traiter.push_front(tuple); 
                            }                                                     //mêmes opérations mais en
                        }                                                                                       //inversant place et transitions
                    }                                                                                           //
                    truc[a_traiter.back()[0]+M.S] = new Element(parent_center+i-decalage, parent_y+1, 0);      //
                    //printf("parent : %d, i : %d, dec : %d\n",parent_center, i, decalage);
                    if (i == 0 || i == curr_size-1) {                                                           //
                        if (i == curr_size-1) curr_y = truc[a_traiter.back()[0]+M.S]->getPosY();                                          //
                        curr_center += truc[a_traiter.back()[0]+M.S]->getPosX();
                        //printf("current center : %d\n",curr_center);                                  //
                    }
                    //free(a_traiter.back());
                    a_traiter.pop_back();
                }
            }
            //printf("current center : %d\n",curr_center);
            if (curr_size != 1) curr_center = curr_center / 2;
            parent_center = curr_center;
            parent_y = curr_y;

            //printf("Current data : %d, %d\n",parent_center, curr_y);


        }
        
        elements = truc;
    }

    bool InterfaceGraphique::isContainedBy(int* tuple, std::list<int*> liste)
    {
        std::vector<int*> vec{std::begin(liste), std::end(liste)};
        for (int i=0;i<vec.size();i++) {
            if (vec[i][0] == tuple[0] && vec[i][1] == tuple[1]) return true;
        }
        return false;
    }

    void InterfaceGraphique::dessinerElements(QGraphicsScene *scene)
    {
        for (int i=0;i<M.S+M.T;i++) {
            if (elements[i] != nullptr) elements[i]->dessiner(scene, parametres);
        }
    }

    void InterfaceGraphique::calculerArcs()
    {
        int x_dep, y_dep, x_fin, y_fin, nb_points = 4;
        int nb_arcs = sizeof(M.F) / sizeof(M.F[0]);
        int*** liste = (int***)malloc(sizeof(int*)*nb_arcs);
        int** un_arc, *un_point;
        for (int i=0;i<nb_arcs;i++) {
            if (M.F[i][0] == 0) {
                x_dep = elements[M.F[i][1]]->getPosX();
                y_dep = elements[M.F[i][1]]->getPosY();
                x_fin = elements[M.F[i][2]+M.S]->getPosX();
                y_fin = elements[M.F[i][2]+M.S]->getPosY();

                x_dep = x_dep*parametres.tailleElement+x_dep*parametres.elementsDistance+parametres.tailleElement/2;
                y_dep = y_dep*parametres.tailleElement+y_dep*parametres.elementsDistance+parametres.tailleElement;
                x_fin = x_fin*parametres.tailleElement+x_fin*parametres.elementsDistance+parametres.tailleElement/2;
                y_fin = y_fin*parametres.tailleElement+y_fin*parametres.elementsDistance+(3.0/8.0)*parametres.tailleElement;


            } else {
                x_fin = elements[M.F[i][1]]->getPosX();
                y_fin = elements[M.F[i][1]]->getPosY();
                x_dep = elements[M.F[i][2]+M.S]->getPosX();
                y_dep = elements[M.F[i][2]+M.S]->getPosY();

                x_dep = x_dep*parametres.tailleElement+x_dep*parametres.elementsDistance+parametres.tailleElement/2;
                y_dep = y_dep*parametres.tailleElement+y_dep*parametres.elementsDistance+(5.0/8.0)*parametres.tailleElement;
                x_fin = x_fin*parametres.tailleElement+x_fin*parametres.elementsDistance+parametres.tailleElement/2;
                y_fin = y_fin*parametres.tailleElement+y_fin*parametres.elementsDistance;
            }
            int **arcs_a_ajouter = eviterIntersection(x_dep, y_dep+parametres.elementsDistance/5+1, x_fin, y_fin-(parametres.elementsDistance/5)-1);
            int nb_a_ajouter;
            for (nb_a_ajouter=0;arcs_a_ajouter[nb_a_ajouter] != nullptr;nb_a_ajouter++) {}
            nb_points = nb_a_ajouter+2;
            
            un_arc = (int**)malloc(sizeof(int*)*(nb_points+1));

            un_point = (int*)malloc(sizeof(int)*2);
            un_point[0] = x_dep, un_point[1] = y_dep;
            un_arc[0] = un_point;

            for (int i=1;i<nb_a_ajouter+1;i++) {
                un_arc[i] = arcs_a_ajouter[i-1];
            }        
                        
            un_point = (int*)malloc(sizeof(int)*2);
            un_point[0] = x_fin, un_point[1] = y_fin;
            un_arc[nb_points-1] = un_point;

            un_arc[nb_points] = nullptr;
            liste[i] = un_arc;

            free(arcs_a_ajouter);
        }
        arcs = liste;
    }

    int **InterfaceGraphique::eviterIntersection(int x_depart, int y_depart, int x_arrivee, int y_arrivee)
    {   
        QGraphicsLineItem *arc = new QGraphicsLineItem(x_depart, y_depart, x_arrivee, y_arrivee);
        QGraphicsItem *sommet;
        std::vector<QGraphicsItem *> collides, no_collides;
        qreal pos_x, pos_y, t_dep_x, t_fin_x;
        int rep = 0;
        bool is_colliding = false, still_colide;

        for (int i=0;i<M.S+M.T;i++) {
            if (elements[i]->isPlace()) {
                pos_x = elements[i]->getPosX()*parametres.tailleElement+elements[i]->getPosX()*parametres.elementsDistance;
                pos_y = elements[i]->getPosY()*parametres.tailleElement+elements[i]->getPosY()*parametres.elementsDistance;
                sommet = new QGraphicsEllipseItem(pos_x, pos_y, parametres.tailleElement, parametres.tailleElement);
            } else {
                pos_x = elements[i]->getPosX()*parametres.tailleElement+elements[i]->getPosX()*parametres.elementsDistance;
                pos_y = elements[i]->getPosY()*parametres.tailleElement+elements[i]->getPosY()*parametres.elementsDistance+(3.0/8.0)*parametres.tailleElement;
                sommet = new QGraphicsRectItem(pos_x, pos_y, parametres.tailleElement, parametres.tailleElement*(2.0/8.0));
            }

            if (arc->collidesWithItem(sommet)) {
                collides.push_back(sommet);
            } else {
                no_collides.push_back(sommet);
            }
        }
        if (collides.empty()) {
            int **arc_points = (int**)malloc(sizeof(int*)*3);
            arc_points[0] = (int*)malloc(sizeof(int)*2);
            arc_points[0][0] = x_depart ,arc_points[0][1] = y_depart;

            arc_points[1] = (int*)malloc(sizeof(int)*2);
            arc_points[1][0] = x_arrivee, arc_points[1][1] = y_arrivee;

            arc_points[2] = nullptr;

            return arc_points;
        } else {
            is_colliding = true;
        }

        while (is_colliding) {
            t_dep_x = x_depart + ((rep/2)*parametres.elementsDistance+parametres.tailleElement*(rep?rep/2:1)) * (rep%2?1:-1);
            t_fin_x = x_arrivee + ((rep/2)*parametres.elementsDistance+parametres.tailleElement*(rep?rep/2:1)) * (rep%2?1:-1);
            arc->setLine(QLineF(QPointF(t_dep_x, y_depart), QPointF(t_fin_x, y_arrivee)));

            still_colide = false;

            for (size_t i=0;i<collides.size();i++) {
                if (arc->collidesWithItem(collides.at(i))) {
                    still_colide = true;
                    break;
                }
            }

            if (still_colide) {
                rep++;
            } else {
                for (size_t i=0;i<no_collides.size();i++) {
                    if (arc->collidesWithItem(no_collides.at(i))) {
                        still_colide = true;
                        break;
                    }
                }

                if (still_colide) {
                    rep++;
                } else {
                    is_colliding = false;
                }
            }
        }
        for (size_t i=0;i<collides.size();i++) {
            delete collides.back();
            collides.pop_back();
        }
        for (size_t i=0;i<no_collides.size();i++) {
            delete no_collides.back();
            no_collides.pop_back();
        }

        int **arc_points = (int**)malloc(sizeof(int*)*5);
        arc_points[0] = (int*)malloc(sizeof(int)*2);
        arc_points[0][0] = x_depart ,arc_points[0][1] = y_depart;

        arc_points[1] = (int*)malloc(sizeof(int)*2);
        arc_points[1][0] = t_dep_x, arc_points[1][1] = y_depart;

        arc_points[2] = (int*)malloc(sizeof(int)*2);
        arc_points[2][0] = t_fin_x, arc_points[2][1] = y_arrivee;

        arc_points[3] = (int*)malloc(sizeof(int)*2);
        arc_points[3][0] = x_arrivee, arc_points[3][1] = y_arrivee;

        arc_points[4] = nullptr;

        return arc_points;
    }

    void InterfaceGraphique::dessinerArcs(QGraphicsScene *scene)
    {
        int nb_sous_arc;
        int nb_arcs = sizeof(M.F) / sizeof(M.F[0]);
        double angle;
        QLineF ligne;
        QPolygonF arrow_head;
        for (int i=0;i<nb_arcs;i++) {
            for (nb_sous_arc = 0;arcs[i][nb_sous_arc] != nullptr; nb_sous_arc++) {}
            for (int j=1;j<nb_sous_arc;j++) {
                scene->addLine(arcs[i][j-1][0], arcs[i][j-1][1], arcs[i][j][0], arcs[i][j][1]);
                if (j == nb_sous_arc-2) {
                    ligne.setLine(arcs[i][j-1][0], arcs[i][j-1][1], arcs[i][j][0], arcs[i][j][1]);
                    angle = atan2(-ligne.dy(), ligne.dx());
                    printf("angle : %f\n",angle);
                    QLineF arrow_tip(ligne);
                    arrow_tip.setLength((19.0/20.0)*ligne.length());
                    arrow_head.clear();
                    arrow_head << arrow_tip.p2() << arrow_tip.p2() - QPointF(sin(angle + M_PI/2.7)*(parametres.tailleElement/7+1), cos(angle + M_PI/2.7)*(parametres.tailleElement/7+1))
                                                 << arrow_tip.p2() - QPointF(sin(angle + M_PI - M_PI/2.7)*(parametres.tailleElement/7+1), cos(angle + M_PI - M_PI/2.7)*(parametres.tailleElement/7+1));
                    scene->addPolygon(arrow_head,QPen(Qt::black),QBrush(Qt::black));
                }
            }
        }
        
    }
