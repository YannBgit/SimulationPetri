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
        for (int i=0;i<M.S;i++) {           //On génère une matrice avec en abscisse
            for (int y=0;y<M.T;y++) {       //les places et en ordonnée les transitions
                matrice_arcs[i][y] = 0;     //pour faciliter la création des éléments
            }
        }

        for (int i=0;i<nb_arcs;i++) {                                   //On indue les couples place transition qui sont liés dans la matrice
            matrice_arcs[M.F[i][1]][M.F[i][2]] = (M.F[i][0] ? -1 : 1);  //la valeur est à 1 si on part de la place vers la transition et -1 inversement
        }

        Element **elements_traite = (Element**)malloc(sizeof(Element*)*(M.S+M.T));  //On crée la liste qui contiendra toutes les places et transitions une fois celles-ci definies

        for (int i=0;i<M.S+M.T;i++) {
            elements_traite[i] = nullptr;       //On initialise cette liste à nullptr
        }

        std::list<int*> a_traiter;
        int* tuple = (int*)malloc(sizeof(int)*2);       //tuple stocke tempoprairement le couple entre le numero de la place/transition et si c'est une place (1) ou une transition (0)
        int curr_size, i,j, curr_center, curr_y=0, parent_center = 0, parent_y = -1, decalage;
        tuple[0] = 0, tuple[1] = 1;                    
                                        //On initialise la liste d'élément à traiter avec la place 0
        a_traiter.push_front(tuple);

        while (!a_traiter.empty()) {        //Tant qu'il y'a des élémnets à traiter
            curr_size = a_traiter.size();       //on récupère le nombre d'élémnts à traiter à chaque début de boucle car on vas ajouter de nouveau éléments à la liste pendant la boucle
            decalage = curr_size/2;
            curr_center = 0;
            for (i=0;i<curr_size;i++) {                                     //on parcours tous les éléments dans la liste a_traiter
                if (i-decalage == 0 && curr_size%2 == 0) decalage--;

                if (a_traiter.back()[1]) {  //Si le dernier élémnet à traiter est une place
                    for (j=0;j<M.T;j++) {                                                               //On ajoute toutes les transitions qui sont liées par un arc partant de cette place.
                        if (matrice_arcs[a_traiter.back()[0]][j] == 1 && elements_traite[M.S+j] == nullptr ) {     //et qui n'ont pas été déja placé dans elements_traite
                            tuple = (int*)malloc(sizeof(int)*2);                                        // 
                            tuple[0] = j, tuple[1] = 0;              //On assigne la transition au tuple
                            if (isContainedBy(tuple, a_traiter)) {      //si le tuple est déjà dans la liste a_traiter, on ignore et on libère la mémoire
                                free(tuple);                            //(arrive quand deux éléments traités dans le même tour sont liée par un arc vers le même élément)
                            } else {
                                a_traiter.push_front(tuple); 
                            }
                        }
                    }

                    elements_traite[a_traiter.back()[0]] = new Element(parent_center+i-decalage, parent_y+1, 1, M.M[a_traiter.back()[0]]); //On crée l'élément que l'on viens de traiter et on le met dans la liste
                    if (i == 0 || i == curr_size-1) { 
                        if (i == curr_size-1) curr_y = elements_traite[a_traiter.back()[0]]->getPosY();    //On récupère ici la position en y des éléments traités ce 
                        curr_center += elements_traite[a_traiter.back()[0]]->getPosX();                    //tour de boucle ci ainsi que le milieu de leurs x
                    }                                                           
                    free(a_traiter.back());                                         //
                    a_traiter.pop_back();                                           //enfin on supprime complétement le tuple de l'élément que l'on vient de traiter de la liste a_traiter

                } else {                    //Si c'est une transition
                    for (j=0;j<M.S;j++) {                                                                           //
                        if (matrice_arcs[j][a_traiter.back()[0]] == -1 && elements_traite[j] == nullptr) {          //
                            tuple = (int*)malloc(sizeof(int)*2);                                                    //
                            tuple[0] = j, tuple[1] = 1;                                                             //mêmes opérations mais en
                            if (isContainedBy(tuple, a_traiter)) {                                                  //
                                free(tuple);                                                                        //
                            } else {                                                                                //
                                a_traiter.push_front(tuple);                                                        //inversant place et transitions
                            }                                                                                       //
                        }                                                                                           //
                    }                                                                                               //
                    elements_traite[a_traiter.back()[0]+M.S] = new Element(parent_center+i-decalage, parent_y+1, 0);      
                    if (i == 0 || i == curr_size-1) {                                                           
                        if (i == curr_size-1) curr_y = elements_traite[a_traiter.back()[0]+M.S]->getPosY();               
                        curr_center += elements_traite[a_traiter.back()[0]+M.S]->getPosX();     //
                    }
                    free(a_traiter.back());
                    a_traiter.pop_back();
                }
            }
            if (curr_size != 1) curr_center = curr_center / 2;  //s'il y avait plus de 1 élément à traiter aors on cherche leur milieu en x, qui est la postion x des extrémités divisées par 2
            parent_center = curr_center;    //Parent_center et parent_y sont utilisés pour la postion ds prochain éléments traités,
            parent_y = curr_y;              //qui sont les éléments ayants été ajoutés à a_traiter durant ce tour de boucle
        }
        
        elements = elements_traite;
    }

    bool InterfaceGraphique::isContainedBy(int* tuple, std::list<int*> liste)
    {
        std::vector<int*> vec{std::begin(liste), std::end(liste)};
        for (size_t i=0;i<vec.size();i++) {                                     //On parcours tous les éléments déjà ,dans la liste
            if (vec[i][0] == tuple[0] && vec[i][1] == tuple[1]) return true;    //Si le tuple y figure déjà on retourne vrai, sinon faux
        }
        return false;
    }

    void InterfaceGraphique::dessinerElements(QGraphicsScene *scene)
    {
        for (int i=0;i<M.S+M.T;i++) {                                               //On parcour simplement tous les éléments
            if (elements[i] != nullptr) elements[i]->dessiner(scene, parametres);   //et appelle leur méthode dessine(scene)
        }
    }

    void InterfaceGraphique::calculerArcs()
    {
        int x_dep, y_dep, x_fin, y_fin, nb_points = 4;
        int nb_arcs = sizeof(M.F) / sizeof(M.F[0]);             //On récupère le nb_d'arcs grâce à la liste F du moteur
        int*** liste = (int***)malloc(sizeof(int*)*nb_arcs);
        int** un_arc, *un_point;

        for (int i=0;i<nb_arcs;i++) {                                    //On parcours tous les arcs

            if (M.F[i][0] == 0) {                               //Si le premier membre est à 0, ça signifie que l'on vas d'une place  à une transition
                x_dep = elements[M.F[i][1]]->getPosX();
                y_dep = elements[M.F[i][1]]->getPosY();         //On récupère donc les position des éléments concernés avec celle de la place comme départ 
                x_fin = elements[M.F[i][2]+M.S]->getPosX();     //comme départ et celle de la tranbsition comme fin.
                y_fin = elements[M.F[i][2]+M.S]->getPosY();     //c'est positions ne représente que celle des éléments par rapport au premier

                x_dep = x_dep*parametres.tailleElement+x_dep*parametres.elementsDistance+parametres.tailleElement/2;    
                y_dep = y_dep*parametres.tailleElement+y_dep*parametres.elementsDistance+parametres.tailleElement;          //on calcule donc ici la position graphique des éléments sur
                x_fin = x_fin*parametres.tailleElement+x_fin*parametres.elementsDistance+parametres.tailleElement/2;        //la scène, selon la taille et la distance entre deux éléments définits
                y_fin = y_fin*parametres.tailleElement+y_fin*parametres.elementsDistance+(3.0/8.0)*parametres.tailleElement;


            } else {
                x_fin = elements[M.F[i][1]]->getPosX();
                y_fin = elements[M.F[i][1]]->getPosY();                         //On fait dans ce else les mêms opérations, mais en inversant le départ et la fin,
                x_dep = elements[M.F[i][2]+M.S]->getPosX();                     //puisque cet arc part de la transition vers la place
                y_dep = elements[M.F[i][2]+M.S]->getPosY();

                x_dep = x_dep*parametres.tailleElement+x_dep*parametres.elementsDistance+parametres.tailleElement/2;
                y_dep = y_dep*parametres.tailleElement+y_dep*parametres.elementsDistance+(5.0/8.0)*parametres.tailleElement;
                x_fin = x_fin*parametres.tailleElement+x_fin*parametres.elementsDistance+parametres.tailleElement/2;
                y_fin = y_fin*parametres.tailleElement+y_fin*parametres.elementsDistance;
            }
                                                                                                                //On appelle eviterIntersection pour obtenir les points de passage du segments principale de 
            int **segments_a_ajouter = eviterIntersection(x_dep, y_dep+parametres.elementsDistance/5+1, x_fin, y_fin-(parametres.elementsDistance/5)-1); //l'arc en évitant les collisions avec les éléments
            int nb_a_ajouter;
            for (nb_a_ajouter=0;segments_a_ajouter[nb_a_ajouter] != nullptr;nb_a_ajouter++) {}  //On récupère le nobres de segments a ajouter pour faire l'arc
            nb_points = nb_a_ajouter+2;     //chaque arc part d'un court segment verticale sous un élément pour arriver à un court segment verticale au-dessus de l'élément d'arrivé par son segment principale,
                                                                                                                     //donc on ajoute les vrai points de départ et d'arrivée de l'arc, +2
            un_arc = (int**)malloc(sizeof(int*)*(nb_points+1));

            un_point = (int*)malloc(sizeof(int)*2);
            un_point[0] = x_dep, un_point[1] = y_dep;       //On définit le point de départ de l'arc
            un_arc[0] = un_point;
    
            for (int i=1;i<nb_a_ajouter+1;i++) {
                un_arc[i] = segments_a_ajouter[i-1];       //On insert les segments qui évitent les éléménts
            }        
                        
            un_point = (int*)malloc(sizeof(int)*2);
            un_point[0] = x_fin, un_point[1] = y_fin;       //on ajoute le point d'arrivé de l'arc
            un_arc[nb_points-1] = un_point;

            un_arc[nb_points] = nullptr;                //on termine par le pointeur de fin de liste
            liste[i] = un_arc;  

            free(segments_a_ajouter);       //On libère alors la mémoire de laliste des sgements, inutile
        }
        arcs = liste;
    }

    int **InterfaceGraphique::eviterIntersection(int x_depart, int y_depart, int x_arrivee, int y_arrivee)
    {   
        QGraphicsLineItem *arc = new QGraphicsLineItem(x_depart, y_depart, x_arrivee, y_arrivee);   //Pour tester les collisions on fait du segment un QGraphicsLineItem qui hérite de QGraphicsItem
        QGraphicsItem *sommet;                                                 //qui posséde une fonction prédéfinit pour le calcul de collision. Sommet sera utiliser pour les places ou transition
        std::vector<QGraphicsItem *> collides, no_collides;     //Liste qui contiendrons les élément qui entrent/n'entrent pas en collisions avec le segment
        qreal pos_x, pos_y, t_dep_x, t_fin_x;      //pos_x/y sont utilisés pour le points d'origine des éléments. t_dep_x/y vont stocké les positions décalès du segment pour éviter les collisions
        int rep = 0;                            // nombre de tour dans le while ci-dessous. multiplicateur du décalage
        bool is_colliding = false, still_colide;    //pour faire tourner le while si il y'a collision; et pour savoir s'il ya toujours collisions aorès décalage pendant le tour de boucle courant

        for (int i=0;i<M.S+M.T;i++) {   //On parcours tous les élémenrs du réseau 

            if (elements[i]->isPlace()) {                                                                                       // 
                pos_x = elements[i]->getPosX()*parametres.tailleElement+elements[i]->getPosX()*parametres.elementsDistance;     //On crée un objet de type ellipse car l'élément est une place
                pos_y = elements[i]->getPosY()*parametres.tailleElement+elements[i]->getPosY()*parametres.elementsDistance;     //et on l'assigne à sommet
                sommet = new QGraphicsEllipseItem(pos_x, pos_y, parametres.tailleElement, parametres.tailleElement);            //

            } else {                                                                                                            //idem mais c'est une transition donc sa forme est un rectangle
                pos_x = elements[i]->getPosX()*parametres.tailleElement+elements[i]->getPosX()*parametres.elementsDistance;     //
                pos_y = elements[i]->getPosY()*parametres.tailleElement+elements[i]->getPosY()*parametres.elementsDistance+(3.0/8.0)*parametres.tailleElement;
                sommet = new QGraphicsRectItem(pos_x, pos_y, parametres.tailleElement, parametres.tailleElement*(2.0/8.0));     //
            }

            if (arc->collidesWithItem(sommet)) {           //
                collides.push_back(sommet);                //On répartit l'élément actuel dans collides ou no_collides selon s'il entre
            } else {                                       //en collsion avec le segment ou non
                no_collides.push_back(sommet);             //
            }
        }
        if (collides.empty()) {                                         //Si le segment n'intersect aucun élément du réseau

            int **arc_points = (int**)malloc(sizeof(int*)*3);
            arc_points[0] = (int*)malloc(sizeof(int)*2);                
            arc_points[0][0] = x_depart ,arc_points[0][1] = y_depart;
                                                                            //Alors il reste le même que donné en entrée, en allant directement du depart à l'arrivée
            arc_points[1] = (int*)malloc(sizeof(int)*2);
            arc_points[1][0] = x_arrivee, arc_points[1][1] = y_arrivee;

            arc_points[2] = nullptr;    //Indique la fin de la liste de points de l'arc

            return arc_points;                                              // et on retourne ce segment

        } else {
            is_colliding = true;        //Si une collision a été détectée, alors on vas éssayer de décaler le segment pour ne plus intersecter
        }

        while (is_colliding) {                                                                                                  //Tant que le segment entre en collision avec un élement,
            t_dep_x = x_depart + ((rep/2)*parametres.elementsDistance+parametres.tailleElement*(rep?rep/2:1)) * (rep%2?1:-1);   //on décale de plus en plus sur l'axe x, en testant la collision
            t_fin_x = x_arrivee + ((rep/2)*parametres.elementsDistance+parametres.tailleElement*(rep?rep/2:1)) * (rep%2?1:-1);  //en alternant ce décalage vers la gauche puis vers la droite

            arc->setLine(QLineF(QPointF(t_dep_x, y_depart), QPointF(t_fin_x, y_arrivee)));  //On change les ccordonnés du segments testé avec le décalage calculé au-dessus 
                                                                                            
            still_colide = false;

            for (size_t i=0;i<collides.size();i++) {
                if (arc->collidesWithItem(collides.at(i))) {        //On teste d'abord si le segment intersect toujours les éléments avec lesquels il entrait en collisions
                    still_colide = true;
                    break;
                }
            }

            if (still_colide) {                                     //si oui on repart pour un tour pour tester un plus grand décalage en incrémentant le facteur de décalage rep
                rep++;
            } else {
                for (size_t i=0;i<no_collides.size();i++) {            //sinon on vérifie qu'il n'entre pas en collision avec de nouveaux éléménts
                    if (arc->collidesWithItem(no_collides.at(i))) {
                        still_colide = true;
                        break;
                    }
                }

                if (still_colide) {                         //si il intersecte de nouveaux éléments on incrémente le facteur de décalage et on repart pour un tour
                    rep++;
                } else {
                    is_colliding = false;           //sinon c'est que le décalage est bon on peut arréter de chercher
                }
            }
        }
        for (size_t i=0;i<collides.size();i++) {
            delete collides.back();                     
            collides.pop_back();
        }                                               //On se débarrasse des objets représentants les élements, devenus inutiles
        for (size_t i=0;i<no_collides.size();i++) {
            delete no_collides.back();
            no_collides.pop_back();
        }

        int **arc_points = (int**)malloc(sizeof(int*)*5);           //cette fois le segment est découpé en 3 segments : (soit 4 points + l'emplacement pour le nullptr de fin de liste)
        arc_points[0] = (int*)malloc(sizeof(int)*2);                
        arc_points[0][0] = x_depart ,arc_points[0][1] = y_depart;
                                                                    //le premier relie le points de départ au début du segment principale
        arc_points[1] = (int*)malloc(sizeof(int)*2);
        arc_points[1][0] = t_dep_x, arc_points[1][1] = y_depart;
                                                                    //le second est le segment principale, qui a été décalé pour éviter les collisions
        arc_points[2] = (int*)malloc(sizeof(int)*2);
        arc_points[2][0] = t_fin_x, arc_points[2][1] = y_arrivee;
                                                                    //le troisième, relie la fin du segment principale au point d'arrivée
        arc_points[3] = (int*)malloc(sizeof(int)*2);
        arc_points[3][0] = x_arrivee, arc_points[3][1] = y_arrivee;

        arc_points[4] = nullptr;                                    //le pointeur de fin de liste

        return arc_points;
    }

    void InterfaceGraphique::dessinerArcs(QGraphicsScene *scene)
    {
        int nb_segments;
        int nb_arcs = sizeof(M.F) / sizeof(M.F[0]);     //on récupère la taille de la liste contenant tout les arcs
        double angle;
        QLineF ligne;
        QPolygonF arrow_head;

        for (int i=0;i<nb_arcs;i++) {                                           //On parcours chque arc de le liste

            for (nb_segments = 0;arcs[i][nb_segments] != nullptr; nb_segments++) {}   //On récupère le nombre de segments de l'arc

            for (int j=1;j<nb_segments;j++) {

                scene->addLine(arcs[i][j-1][0], arcs[i][j-1][1], arcs[i][j][0], arcs[i][j][1]);     //On dessinne chque segment

                if (j == nb_segments-2) {                                                           //Sur l'avant dernier segment, on ajoute une tête de flèche
                    ligne.setLine(arcs[i][j-1][0], arcs[i][j-1][1], arcs[i][j][0], arcs[i][j][1]);
                    angle = atan2(-ligne.dy(), ligne.dx());
                    QLineF arrow_tip(ligne);                           //
                    arrow_tip.setLength((19.0/20.0)*ligne.length());   //On place la pointe de la fclèche à 19/20 du segment, et ci-dessous on calcul ses deux autres points                           
                    arrow_head.clear();
                    arrow_head << arrow_tip.p2() << arrow_tip.p2() - QPointF(sin(angle + M_PI/2.7)*(parametres.tailleElement/7+1), cos(angle + M_PI/2.7)*(parametres.tailleElement/7+1))
                                                 << arrow_tip.p2() - QPointF(sin(angle + M_PI - M_PI/2.7)*(parametres.tailleElement/7+1), cos(angle + M_PI - M_PI/2.7)*(parametres.tailleElement/7+1));

                    scene->addPolygon(arrow_head,QPen(Qt::black),QBrush(Qt::black));    //La tête de flèche est ajouté à lz scene comme polygone des 3 points ci-dessus
                }
            }
        }
    }

    void InterfaceGraphique::miseAJourReseau(QGraphicsScene *scene)
    {
        for (int i=0;i<M.S;i++) {                           //
            if (M.M[i] != elements[i]->getNbJetons()) {     //Pour chaque place dont le nombre de jetons à changé
                elements[i]->setNbJetons(M.M[i]);           //on met à jour son nombre de jetons
            }                                               //
        }
        scene->clear();                         //
        dessinerElements(scene);                //On vide la scène et on re-dessine les places, transitions et arcs
        dessinerArcs(scene);                    //
    }
