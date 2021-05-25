#include "InterfaceGraphique.hpp"

QLabel *tabproba;
QLabel *tabarcs;
QLabel *tabjetcontenu;
QLabel *tabjetcg;
QLabel *tabjetmax;

FILE *fichier;
GestionnaireDeFichiers GDF(fichier);
FILE *temp = GDF.CreerFichierTemporaire();
Echeancier E(GDF.rechercheEtat(0, fichier));
Moteur M(GDF.rechercheEtat(0, fichier).getTe(),  GDF.rechercheEtat(0, fichier).getS(), GDF.rechercheEtat(0, fichier).getT(), GDF.rechercheEtat(0, fichier).getP(),
GDF.rechercheEtat(0, fichier).getF(), GDF.rechercheEtat(0, fichier).getM(), GDF.rechercheEtat(0, fichier).getW(), GDF.rechercheEtat(0, fichier).getK());

InterfaceGraphique::InterfaceGraphique()
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
    
 
	// Affichage de Te, S, T
	echeancierintro = new QLabel("", this);
	echeancierintro->setText(QString("Te = %1 <br/>").arg(M.getTe())+QString("S = %1 <br/>").arg(M.getS())+QString("T = %1 <br/>").arg(M.getT()));
	
	
	
	// Affichage de P
	QString proba[M.getT()];
	QString resproba;
	
	for(int i = 0; i<M.getT(); i++)
	{
		proba[i] = QString::number(M.getP()[i]);
	}
	
	resproba = "P = { ";
	
	for(int i = 0; i<M.getT(); i++)
	{
		if(i == M.getT()-1)
		{
			resproba = resproba + proba[i] + " }";
		}
		else
		{
			resproba = resproba + proba[i] + " , ";
		}
	}
	tabproba = new QLabel(resproba, this);



	// Affichage de F (arcs)
	int sa = sizeof(M.getF());
	QString arcs[sa][3];
	QString resarcs;
	
	for(int i = 0; i<sa; i++)
	{
		for(int j = 0; j<3; j++)
		{
			arcs[i][j] = QString::number(M.getF()[i][j]);
		}
	}
	
	
	resarcs = "F = { ";
	
	
	for(int i = 0; i<sa; i++)
	{
		resarcs = resarcs + "{ ";
		for(int j = 0; j<3; j++)
		{
			if(j == 2)
			{
				resarcs = resarcs + arcs[i][j] + " }";
			}
			else
			{
				resarcs = resarcs + arcs[i][j] + " , ";
			}
		}
		if(i == sa-1)
		{
			resarcs = resarcs + " }";
		}
		else
		{
			resarcs = resarcs + " , ";
			if(i%5 ==  0 && i != 0)
			{
				resarcs = resarcs + "<br/>";
			}
		}
	}
	tabarcs = new QLabel(resarcs, this);



		// Affichage de M
	QString jetcontenu[M.getS()];
	QString resjetcontenu;
	
	for(int i = 0; i<M.getS(); i++)
	{
		jetcontenu[i] = QString::number(M.getM()[i]);
	}
	
	resjetcontenu = "M = { ";
	for(int i = 0; i<M.getS(); i++)
	{
		if(i == M.getS()-1)
		{
			resjetcontenu = resjetcontenu + jetcontenu[i] + " }";
		}
		else
		{
			resjetcontenu = resjetcontenu + jetcontenu[i] + " , ";
		}
	}
	tabjetcontenu = new QLabel(resjetcontenu,this);



		// Affichage de W
	
	QString jetcg[M.getT()][2];
	QString resjetcg;
	
	for(int i = 0; i<M.getT(); i++)
	{
		for(int j = 0; j<2; j++)
		{
			jetcg[i][j] = QString::number(M.getW()[i][j]);
		}
	}
	
	
	resjetcg = "W = { ";
	
	
	for(int i = 0; i<M.getT(); i++)
	{
		resjetcg = resjetcg + "{ ";
		for(int j = 0; j<2; j++)
		{
			if(j == 1)
			{
				resjetcg = resjetcg + jetcg[i][j] + " }";
			}
			else
			{
				resjetcg = resjetcg + jetcg[i][j] + " , ";
			}
		}
		if(i == M.getT()-1)
		{
			resjetcg = resjetcg + " }";
		}
		else
		{
			resjetcg = resjetcg + " , ";
			if(i%5 ==  0 && i != 0)
			{
				resjetcg = resjetcg + "<br/>";
			}
		}
	}
	tabjetcg = new QLabel(resjetcg, this);


		// Affichage de K
	QString jetmax[M.getS()];
	QString resjetmax;
	
	for(int i = 0; i<M.getS(); i++)
	{
		jetmax[i] = QString::number(M.getK()[i]);
	}
	
	resjetmax = "K = { ";
	for(int i = 0; i<M.getS(); i++)
	{
		if(i == M.getS()-1)
		{
			resjetmax = resjetmax + jetmax[i] + " }";
		}
		else
		{
			resjetmax = resjetmax + jetmax[i] + " , ";
		}
	}
	tabjetmax = new QLabel(resjetmax,this);
	
	
	
	//echeancierintro->setText(QString::number(Te));
	echeancierintro->setFont(QFont("Lato Light", 15));
	echeancierintro->setMaximumWidth(500);
	tabproba->setFont(QFont("Lato Light", 12));
	tabproba->setMaximumWidth(500);
	tabarcs->setFont(QFont("Lato Light", 12));
	tabarcs->setMaximumWidth(500);
	tabjetcontenu->setFont(QFont("Lato Light", 12));
	tabjetcontenu->setMaximumWidth(500);
	tabjetmax->setFont(QFont("Lato Light", 12));
	tabjetmax->setMaximumWidth(500);


    // CREATION DU LAYOUT POUR L'AFFICHAGE DE L'ÉCHEANCIER ET AJOUT DU WIDGET TEXTE
    QVBoxLayout *vlayout = new QVBoxLayout;

    vlayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    vlayout->addWidget(echeancierintro);
    vlayout->addWidget(tabproba);
    vlayout->addWidget(tabarcs);
    vlayout->addWidget(tabjetcontenu);
    vlayout->addWidget(tabjetmax);

    // CREATION DES LAYOUT PRINCIPAL
    QGridLayout *layoutPrincipal = new QGridLayout();

	//Création du widget de l'afficheu de réseau
	QGraphicsView *view_afficheur_reseau = new QGraphicsView(this);
	afficheur_reseau = new QGraphicsScene(view_afficheur_reseau);
	view_afficheur_reseau->setScene(afficheur_reseau);




    // AJOUT DES LAYOUTS DANS LE LAYOUT PRINCIPAL
    layoutPrincipal->addLayout(vlayout, 0, 0, 8, 2); //Ajout du Layout Vertical "vlayout"
    layoutPrincipal->addLayout(glayout, 8, 4, 4, 2); //Ajout du Layout Grid "glayout"
	layoutPrincipal->addWidget(view_afficheur_reseau, 0, 2, 12, 3);//Ajout de la vue du diagramme du réseau

    setLayout(layoutPrincipal);

    QObject::connect(etatInitial, SIGNAL(clicked()), this, SLOT(fct_etatInitial()));
    QObject::connect(enregistrer, SIGNAL(clicked()), this, SLOT(fct_enregistrer));
    QObject::connect(charger, SIGNAL(clicked()), this, SLOT(fct_charger()));
    QObject::connect(avancer, SIGNAL(clicked()), this, SLOT(fct_avancer()));
    QObject::connect(reculer, SIGNAL(clicked()), this, SLOT(fct_reculer()));

}



// CREATION DES SLOTS

void InterfaceGraphique::fct_etatInitial()
{
    M = E.RenvoyerEtatReseauSelonTemps(0, GDF);
    echeancierintro->setText(QString("Te = %1 <br/>").arg(M.getTe())+QString("S = %1 <br/>").arg(M.getS()));
	
	// RAFRAICHIR PROBA P
	QString resproba2;
	QString proba2[2];
	
	QString proba[M.getT()];
	QString resproba;
	
	for(int i = 0; i<M.getT(); i++)
	{
		proba[i] = QString::number(M.getP()[i]);
	}
	
	resproba = "P = { ";
	
	for(int i = 0; i<M.getT(); i++)
	{
		if(i == M.getT()-1)
		{
			resproba = resproba + proba[i] + " }";
		}
		else
		{
			resproba = resproba + proba[i] + " , ";
		}
	}
	tabproba->setText(resproba2);
	
	
	
	// RAFRAICHIR ARCS F
	int sa = sizeof(M.getF());
	QString arcs[sa][3];
	QString resarcs;
	
	for(int i = 0; i<sa; i++)
	{
		for(int j = 0; j<3; j++)
		{
			arcs[i][j] = QString::number(M.getF()[i][j]);
		}
	}
	
	
	resarcs = "F = { ";
	
	
	for(int i = 0; i<sa; i++)
	{
		resarcs = resarcs + "{ ";
		for(int j = 0; j<3; j++)
		{
			if(j == 2)
			{
				resarcs = resarcs + arcs[i][j] + " }";
			}
			else
			{
				resarcs = resarcs + arcs[i][j] + " , ";
			}
		}
		if(i == sa-1)
		{
			resarcs = resarcs + " }";
		}
		else
		{
			resarcs = resarcs + " , ";
			if(i%5 ==  0 && i != 0)
			{
				resarcs = resarcs + "<br/>";
			}
		}
	}
	tabarcs->setText(resarcs);
	
	// RAFRAICHIR M (JETONS CONTENUS)
	QString jetcontenu[M.getS()];
	QString resjetcontenu;
	
	for(int i = 0; i<M.getS(); i++)
	{
		jetcontenu[i] = QString::number(M.getM()[i]);
	}
	
	resjetcontenu = "M = { ";
	for(int i = 0; i<M.getS(); i++)
	{
		if(i == M.getS()-1)
		{
			resjetcontenu = resjetcontenu + jetcontenu[i] + " }";
		}
		else
		{
			resjetcontenu = resjetcontenu + jetcontenu[i] + " , ";
		}
	}
	tabjetcontenu->setText(resjetcontenu);
	
	// RAFRAICHIR W (JETMAX)
	
	QString jetcg[M.getT()][2];
	QString resjetcg;
	
	for(int i = 0; i<M.getT(); i++)
	{
		for(int j = 0; j<2; j++)
		{
			jetcg[i][j] = QString::number(M.getW()[i][j]);
		}
	}
	
	
	resjetcg = "W = { ";
	
	
	for(int i = 0; i<M.getT(); i++)
	{
		resjetcg = resjetcg + "{ ";
		for(int j = 0; j<2; j++)
		{
			if(j == 1)
			{
				resjetcg = resjetcg + jetcg[i][j] + " }";
			}
			else
			{
				resjetcg = resjetcg + jetcg[i][j] + " , ";
			}
		}
		if(i == M.getT()-1)
		{
			resjetcg = resjetcg + " }";
		}
		else
		{
			resjetcg = resjetcg + " , ";
			if(i%5 ==  0 && i != 0)
			{
				resjetcg = resjetcg + "<br/>";
			}
		}
	}
	tabjetcg->setText(resjetcg);
	
	// RAFRAICHIR K
	
	QString jetmax[M.getS()];
	QString resjetmax;
	
	for(int i = 0; i<M.getS(); i++)
	{
		jetmax[i] = QString::number(M.getK()[i]);
	}
	
	resjetmax = "K = { ";
	for(int i = 0; i<M.getS(); i++)
	{
		if(i == M.getS()-1)
		{
			resjetmax = resjetmax + jetmax[i] + " }";
		}
		else
		{
			resjetmax = resjetmax + jetmax[i] + " , ";
		}
	}
	tabjetmax->setText(resjetmax);

	miseAJourReseau();
}

void InterfaceGraphique::fct_avancer()
{
	M = E.RenvoyerEtatReseauSelonTemps(M.getTe()+1, GDF);
	echeancierintro->setText(QString("Te = %1 <br/>").arg(M.getTe())+QString("S = %1 <br/>").arg(M.getS()));
	
	// RAFRAICHIR PROBA P
	QString resproba2;
	QString proba2[2];
	
	QString proba[M.getT()];
	QString resproba;
	
	for(int i = 0; i<M.getT(); i++)
	{
		proba[i] = QString::number(M.getP()[i]);
	}
	
	resproba = "P = { ";
	
	for(int i = 0; i<M.getT(); i++)
	{
		if(i == M.getT()-1)
		{
			resproba = resproba + proba[i] + " }";
		}
		else
		{
			resproba = resproba + proba[i] + " , ";
		}
	}
	tabproba->setText(resproba2);
	
	
	
	// RAFRAICHIR ARCS F
	int sa = sizeof(M.getF());
	QString arcs[sa][3];
	QString resarcs;
	
	for(int i = 0; i<sa; i++)
	{
		for(int j = 0; j<3; j++)
		{
			arcs[i][j] = QString::number(M.getF()[i][j]);
		}
	}
	
	
	resarcs = "F = { ";
	
	
	for(int i = 0; i<sa; i++)
	{
		resarcs = resarcs + "{ ";
		for(int j = 0; j<3; j++)
		{
			if(j == 2)
			{
				resarcs = resarcs + arcs[i][j] + " }";
			}
			else
			{
				resarcs = resarcs + arcs[i][j] + " , ";
			}
		}
		if(i == sa-1)
		{
			resarcs = resarcs + " }";
		}
		else
		{
			resarcs = resarcs + " , ";
			if(i%5 ==  0 && i != 0)
			{
				resarcs = resarcs + "<br/>";
			}
		}
	}
	tabarcs->setText(resarcs);
	
	// RAFRAICHIR M (JETONS CONTENUS)
	QString jetcontenu[M.getS()];
	QString resjetcontenu;
	
	for(int i = 0; i<M.getS(); i++)
	{
		jetcontenu[i] = QString::number(M.getM()[i]);
	}
	
	resjetcontenu = "M = { ";
	for(int i = 0; i<M.getS(); i++)
	{
		if(i == M.getS()-1)
		{
			resjetcontenu = resjetcontenu + jetcontenu[i] + " }";
		}
		else
		{
			resjetcontenu = resjetcontenu + jetcontenu[i] + " , ";
		}
	}
	tabjetcontenu->setText(resjetcontenu);
	
	// RAFRAICHIR W (JETMAX)
	
	QString jetcg[M.getT()][2];
	QString resjetcg;
	
	for(int i = 0; i<M.getT(); i++)
	{
		for(int j = 0; j<2; j++)
		{
			jetcg[i][j] = QString::number(M.getW()[i][j]);
		}
	}
	
	
	resjetcg = "W = { ";
	
	
	for(int i = 0; i<M.getT(); i++)
	{
		resjetcg = resjetcg + "{ ";
		for(int j = 0; j<2; j++)
		{
			if(j == 1)
			{
				resjetcg = resjetcg + jetcg[i][j] + " }";
			}
			else
			{
				resjetcg = resjetcg + jetcg[i][j] + " , ";
			}
		}
		if(i == M.getT()-1)
		{
			resjetcg = resjetcg + " }";
		}
		else
		{
			resjetcg = resjetcg + " , ";
			if(i%5 ==  0 && i != 0)
			{
				resjetcg = resjetcg + "<br/>";
			}
		}
	}
	tabjetcg->setText(resjetcg);
	
	// RAFRAICHIR K
	
	QString jetmax[M.getS()];
	QString resjetmax;
	
	for(int i = 0; i<M.getS(); i++)
	{
		jetmax[i] = QString::number(M.getK()[i]);
	}
	
	resjetmax = "K = { ";
	for(int i = 0; i<M.getS(); i++)
	{
		if(i == M.getS()-1)
		{
			resjetmax = resjetmax + jetmax[i] + " }";
		}
		else
		{
			resjetmax = resjetmax + jetmax[i] + " , ";
		}
	}
	tabjetmax->setText(resjetmax);

	miseAJourReseau();
	
}

void InterfaceGraphique::fct_reculer()
{
    M = E.RenvoyerEtatReseauSelonTemps(M.getTe()-1, GDF);
    echeancierintro->setText(QString("Te = %1 <br/>").arg(M.getTe())+QString("S = %1 <br/>").arg(M.getS()));
	
	// RAFRAICHIR PROBA P
	QString resproba2;
	QString proba2[2];
	
	QString proba[M.getT()];
	QString resproba;
	
	for(int i = 0; i<M.getT(); i++)
	{
		proba[i] = QString::number(M.getP()[i]);
	}
	
	resproba = "P = { ";
	
	for(int i = 0; i<M.getT(); i++)
	{
		if(i == M.getT()-1)
		{
			resproba = resproba + proba[i] + " }";
		}
		else
		{
			resproba = resproba + proba[i] + " , ";
		}
	}
	tabproba->setText(resproba2);
	
	
	
	// RAFRAICHIR ARCS F
	int sa = sizeof(M.getF());
	QString arcs[sa][3];
	QString resarcs;
	
	for(int i = 0; i<sa; i++)
	{
		for(int j = 0; j<3; j++)
		{
			arcs[i][j] = QString::number(M.getF()[i][j]);
		}
	}
	
	
	resarcs = "F = { ";
	
	
	for(int i = 0; i<sa; i++)
	{
		resarcs = resarcs + "{ ";
		for(int j = 0; j<3; j++)
		{
			if(j == 2)
			{
				resarcs = resarcs + arcs[i][j] + " }";
			}
			else
			{
				resarcs = resarcs + arcs[i][j] + " , ";
			}
		}
		if(i == sa-1)
		{
			resarcs = resarcs + " }";
		}
		else
		{
			resarcs = resarcs + " , ";
			if(i%5 ==  0 && i != 0)
			{
				resarcs = resarcs + "<br/>";
			}
		}
	}
	tabarcs->setText(resarcs);
	
	// RAFRAICHIR M (JETONS CONTENUS)
	QString jetcontenu[M.getS()];
	QString resjetcontenu;
	
	for(int i = 0; i<M.getS(); i++)
	{
		jetcontenu[i] = QString::number(M.getM()[i]);
	}
	
	resjetcontenu = "M = { ";
	for(int i = 0; i<M.getS(); i++)
	{
		if(i == M.getS()-1)
		{
			resjetcontenu = resjetcontenu + jetcontenu[i] + " }";
		}
		else
		{
			resjetcontenu = resjetcontenu + jetcontenu[i] + " , ";
		}
	}
	tabjetcontenu->setText(resjetcontenu);
	
	// RAFRAICHIR W (JETMAX)
	
	QString jetcg[M.getT()][2];
	QString resjetcg;
	
	for(int i = 0; i<M.getT(); i++)
	{
		for(int j = 0; j<2; j++)
		{
			jetcg[i][j] = QString::number(M.getW()[i][j]);
		}
	}
	
	
	resjetcg = "W = { ";
	
	
	for(int i = 0; i<M.getT(); i++)
	{
		resjetcg = resjetcg + "{ ";
		for(int j = 0; j<2; j++)
		{
			if(j == 1)
			{
				resjetcg = resjetcg + jetcg[i][j] + " }";
			}
			else
			{
				resjetcg = resjetcg + jetcg[i][j] + " , ";
			}
		}
		if(i == M.getT()-1)
		{
			resjetcg = resjetcg + " }";
		}
		else
		{
			resjetcg = resjetcg + " , ";
			if(i%5 ==  0 && i != 0)
			{
				resjetcg = resjetcg + "<br/>";
			}
		}
	}
	tabjetcg->setText(resjetcg);
	
	// RAFRAICHIR K
	
	QString jetmax[M.getS()];
	QString resjetmax;
	
	for(int i = 0; i<M.getS(); i++)
	{
		jetmax[i] = QString::number(M.getK()[i]);
	}
	
	resjetmax = "K = { ";
	for(int i = 0; i<M.getS(); i++)
	{
		if(i == M.getS()-1)
		{
			resjetmax = resjetmax + jetmax[i] + " }";
		}
		else
		{
			resjetmax = resjetmax + jetmax[i] + " , ";
		}
	}
	tabjetmax->setText(resjetmax);

	miseAJourReseau();
}

void InterfaceGraphique::fct_enregistrer()
{
    GDF.EnregistrerEcheancier(temp, fichier);
}

void InterfaceGraphique::fct_charger()
{
    GDF.Charger(fichier);
}

//Afficheur de Reseau

void InterfaceGraphique::buildElementsPosition() 
{       
        int nb_arcs = sizeof(M.getF()) / sizeof(M.getF()[0]);
        int matrice_arcs[M.getS()][M.getT()];
        for (int i=0;i<M.getS();i++) {           //On génère une matrice avec en abscisse
            for (int y=0;y<M.getT();y++) {       //les places et en ordonnée les transitions
                matrice_arcs[i][y] = 0;     //pour faciliter la création des éléments
            }
        }

        for (int i=0;i<nb_arcs;i++) {                                   //On indue les couples place transition qui sont liés dans la matrice
            matrice_arcs[M.getF()[i][1]][M.getF()[i][2]] = (M.getF()[i][0] ? -1 : 1);  //la valeur est à 1 si on part de la place vers la transition et -1 inversement
        }

        Element **elements_traite = (Element**)malloc(sizeof(Element*)*(M.getS()+M.getT()));  //On crée la liste qui contiendra toutes les places et transitions une fois celles-ci definies

        for (int i=0;i<M.getS()+M.getT();i++) {
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
                    for (j=0;j<M.getT();j++) {                                                               //On ajoute toutes les transitions qui sont liées par un arc partant de cette place.
                        if (matrice_arcs[a_traiter.back()[0]][j] == 1 && elements_traite[M.getS()+j] == nullptr ) {     //et qui n'ont pas été déja placé dans elements_traite
                            tuple = (int*)malloc(sizeof(int)*2);                                        // 
                            tuple[0] = j, tuple[1] = 0;              //On assigne la transition au tuple
                            if (isContainedBy(tuple, a_traiter)) {      //si le tuple est déjà dans la liste a_traiter, on ignore et on libère la mémoire
                                free(tuple);                            //(arrive quand deux éléments traités dans le même tour sont liée par un arc vers le même élément)
                            } else {
                                a_traiter.push_front(tuple); 
                            }
                        }
                    }

                    elements_traite[a_traiter.back()[0]] = new Element(parent_center+i-decalage, parent_y+1, 1, M.getM()[a_traiter.back()[0]]); //On crée l'élément que l'on viens de traiter et on le met dans la liste
                    if (i == 0 || i == curr_size-1) { 
                        if (i == curr_size-1) curr_y = elements_traite[a_traiter.back()[0]]->getPosY();    //On récupère ici la position en y des éléments traités ce 
                        curr_center += elements_traite[a_traiter.back()[0]]->getPosX();                    //tour de boucle ci ainsi que le milieu de leurs x
                    }                                                           
                    free(a_traiter.back());                                         //
                    a_traiter.pop_back();                                           //enfin on supprime complétement le tuple de l'élément que l'on vient de traiter de la liste a_traiter

                } else {                    //Si c'est une transition
                    for (j=0;j<M.getS();j++) {                                                                           //
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
                    elements_traite[a_traiter.back()[0]+M.getS()] = new Element(parent_center+i-decalage, parent_y+1, 0);      
                    if (i == 0 || i == curr_size-1) {                                                           
                        if (i == curr_size-1) curr_y = elements_traite[a_traiter.back()[0]+M.getS()]->getPosY();               
                        curr_center += elements_traite[a_traiter.back()[0]+M.getS()]->getPosX();     //
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

    void InterfaceGraphique::dessinerElements()
    {
        for (int i=0;i<M.getS()+M.getT();i++) {                                               //On parcour simplement tous les éléments
            if (elements[i] != nullptr) elements[i]->dessiner(parametres);   //et appelle leur méthode dessine(parametres)
        }
    }

    void InterfaceGraphique::calculerArcs()
    {
        int x_dep, y_dep, x_fin, y_fin, nb_points = 4;
        int nb_arcs = sizeof(M.getF()) / sizeof(M.getF()[0]);             //On récupère le nb_d'arcs grâce à la liste F du moteur
        int*** liste = (int***)malloc(sizeof(int*)*nb_arcs);
        int** un_arc, *un_point;

        for (int i=0;i<nb_arcs;i++) {                                    //On parcours tous les arcs

            if (M.getF()[i][0] == 0) {                               //Si le premier membre est à 0, ça signifie que l'on vas d'une place  à une transition
                x_dep = elements[M.getF()[i][1]]->getPosX();
                y_dep = elements[M.getF()[i][1]]->getPosY();         //On récupère donc les position des éléments concernés avec celle de la place comme départ 
                x_fin = elements[M.getF()[i][2]+M.getS()]->getPosX();     //comme départ et celle de la tranbsition comme fin.
                y_fin = elements[M.getF()[i][2]+M.getS()]->getPosY();     //c'est positions ne représente que celle des éléments par rapport au premier

                x_dep = x_dep*parametres.tailleElement+x_dep*parametres.elementsDistance+parametres.tailleElement/2;    
                y_dep = y_dep*parametres.tailleElement+y_dep*parametres.elementsDistance+parametres.tailleElement;          //on calcule donc ici la position graphique des éléments sur
                x_fin = x_fin*parametres.tailleElement+x_fin*parametres.elementsDistance+parametres.tailleElement/2;        //la scène, selon la taille et la distance entre deux éléments définits
                y_fin = y_fin*parametres.tailleElement+y_fin*parametres.elementsDistance+(3.0/8.0)*parametres.tailleElement;


            } else {
                x_fin = elements[M.getF()[i][1]]->getPosX();
                y_fin = elements[M.getF()[i][1]]->getPosY();                         //On fait dans ce else les mêms opérations, mais en inversant le départ et la fin,
                x_dep = elements[M.getF()[i][2]+M.getS()]->getPosX();                     //puisque cet arc part de la transition vers la place
                y_dep = elements[M.getF()[i][2]+M.getS()]->getPosY();

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

        for (int i=0;i<M.getS()+M.getT();i++) {   //On parcours tous les élémenrs du réseau 

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

    void InterfaceGraphique::dessinerArcs()
    {
        int nb_segments;
        int nb_arcs = sizeof(M.getF()) / sizeof(M.getF()[0]);     //on récupère la taille de la liste contenant tout les arcs
        double angle;
        QLineF ligne;
        QPolygonF arrow_head;

        for (int i=0;i<nb_arcs;i++) {                                           //On parcours chque arc de le liste

            for (nb_segments = 0;arcs[i][nb_segments] != nullptr; nb_segments++) {}   //On récupère le nombre de segments de l'arc

            for (int j=1;j<nb_segments;j++) {

                afficheur_reseau->addLine(arcs[i][j-1][0], arcs[i][j-1][1], arcs[i][j][0], arcs[i][j][1]);     //On dessinne chque segment

                if (j == nb_segments-2) {                                                           //Sur l'avant dernier segment, on ajoute une tête de flèche
                    ligne.setLine(arcs[i][j-1][0], arcs[i][j-1][1], arcs[i][j][0], arcs[i][j][1]);
                    angle = atan2(-ligne.dy(), ligne.dx());
                    QLineF arrow_tip(ligne);                           //
                    arrow_tip.setLength((19.0/20.0)*ligne.length());   //On place la pointe de la fclèche à 19/20 du segment, et ci-dessous on calcul ses deux autres points                           
                    arrow_head.clear();
                    arrow_head << arrow_tip.p2() << arrow_tip.p2() - QPointF(sin(angle + M_PI/2.7)*(parametres.tailleElement/7+1), cos(angle + M_PI/2.7)*(parametres.tailleElement/7+1))
                                                 << arrow_tip.p2() - QPointF(sin(angle + M_PI - M_PI/2.7)*(parametres.tailleElement/7+1), cos(angle + M_PI - M_PI/2.7)*(parametres.tailleElement/7+1));

                    afficheur_reseau->addPolygon(arrow_head,QPen(Qt::black),QBrush(Qt::black));    //La tête de flèche est ajouté à lz afficheur_reseau comme polygone des 3 points ci-dessus
                }
            }
        }
    }

    void InterfaceGraphique::miseAJourReseau()
    {
        for (int i=0;i<M.getS();i++) {                           //
            if (M.getM()[i] != elements[i]->getNbJetons()) {     //Pour chaque place dont le nombre de jetons à changé
                elements[i]->setNbJetons(M.getM()[i]);           //on met à jour son nombre de jetons
            }                                               //
        }
        afficheur_reseau->clear();                         //
        dessinerElements();                //On vide la scène et on re-dessine les places, transitions et arcs
        dessinerArcs();                    //
    }
