#include "InterfaceGraphique.hpp"
#include "Moteur.hpp"

Moteur M = new Moteur();

QLabel *tabproba;
QLabel *tabarcs;
QLabel *tabjetcontenu;
QLabel *tabjetcg;
QLabel *tabjetmax;

InterfaceGraphique()::InterfaceGraphique()
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
	echeancierintro->setText(QString("Te = %1 <br/>").arg(M.Te)+QString("S = %1 <br/>").arg(M.S)+QString("T = %1 <br/>").arg(M.T));
	
	
	
		// Affichage de P
	QString proba[M.T];
	QString resproba;
	
	for(int i = 0; i<M.T; i++)
	{
		proba[i] = QString::number(M.P[i]);
	}
	
	resproba = "P = { ";
	
	for(int i = 0; i<M.T; i++)
	{
		if(i == M.T-1)
		{
			resproba = resproba + proba[i] + " }";
		}
		else
		{
			resproba = resproba + proba[i] + " , ";
		}
	}
	tabproba = new QLabel(resproba,this);



	// Affichage de F (arcs)
	int sa = sizeof(this->M.F);
	QString arcs[sa][3];
	QString resarcs;
	
	for(int i = 0; i<sa; i++)
	{
		for(int j = 0; j<3; j++)
		{
			arcs[i][j] = QString::number(F[i][j]);
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
	QString jetcontenu[M.S];
	QString resjetcontenu;
	
	for(int i = 0; i<M.S; i++)
	{
		jetcontenu[i] = QString::number(M.M[i]);
	}
	
	resjetcontenu = "M = { ";
	for(int i = 0; i<M.S; i++)
	{
		if(i == M.S-1)
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
	
	QString jetcg[M.T][2];
	QString resjetcg;
	
	for(int i = 0; i<M.T; i++)
	{
		for(int j = 0; j<2; j++)
		{
			jetcg[i][j] = QString::number(W[i][j]);
		}
	}
	
	
	resjetcg = "W = { ";
	
	
	for(int i = 0; i<M.T; i++)
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
		if(i == M.T-1)
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
	QString jetmax[M.S];
	QString resjetmax;
	
	for(int i = 0; i<M.S; i++)
	{
		jetmax[i] = QString::number(M.K[i]);
	}
	
	resjetmax = "K = { ";
	for(int i = 0; i<M.S; i++)
	{
		if(i == M.S-1)
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



// CREATION DES SLOTS

void InterfaceGraphique::fct_etatInitial()
{
    E.RenvoyerEtatReseau(0);
    echeancierintro->setText(QString("Te = %1 <br/>").arg(M.Te)+QString("S = %1 <br/>").arg(S));
	
	// RAFRAICHIR PROBA P
	QString resproba2;
	QString proba2[2];
	
	QString proba[M.T];
	QString resproba;
	
	for(int i = 0; i<M.T; i++)
	{
		proba[i] = QString::number(M.P[i]);
	}
	
	resproba = "P = { ";
	
	for(int i = 0; i<M.T; i++)
	{
		if(i == M.T-1)
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
	int sa = sizeof(this->M.F);
	QString arcs[sa][3];
	QString resarcs;
	
	for(int i = 0; i<sa; i++)
	{
		for(int j = 0; j<3; j++)
		{
			arcs[i][j] = QString::number(F[i][j]);
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
	QString jetcontenu[M.S];
	QString resjetcontenu;
	
	for(int i = 0; i<M.S; i++)
	{
		jetcontenu[i] = QString::number(M.M[i]);
	}
	
	resjetcontenu = "M = { ";
	for(int i = 0; i<M.S; i++)
	{
		if(i == M.S-1)
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
	
	QString jetcg[M.T][2];
	QString resjetcg;
	
	for(int i = 0; i<M.T; i++)
	{
		for(int j = 0; j<2; j++)
		{
			jetcg[i][j] = QString::number(W[i][j]);
		}
	}
	
	
	resjetcg = "W = { ";
	
	
	for(int i = 0; i<M.T; i++)
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
		if(i == M.T-1)
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
	
	QString jetmax[M.S];
	QString resjetmax;
	
	for(int i = 0; i<M.S; i++)
	{
		jetmax[i] = QString::number(M.K[i]);
	}
	
	resjetmax = "K = { ";
	for(int i = 0; i<M.S; i++)
	{
		if(i == M.S-1)
		{
			resjetmax = resjetmax + jetmax[i] + " }";
		}
		else
		{
			resjetmax = resjetmax + jetmax[i] + " , ";
		}
	}
	tabjetmax->setText(resjetmax);
}

void InterfaceGraphique::fct_avancer()
{
	E.RenvoyerEtatReseau(M.Te+1);
	echeancierintro->setText(QString("Te = %1 <br/>").arg(M.Te)+QString("S = %1 <br/>").arg(S));
	
	// RAFRAICHIR PROBA P
	QString resproba2;
	QString proba2[2];
	
	QString proba[M.T];
	QString resproba;
	
	for(int i = 0; i<M.T; i++)
	{
		proba[i] = QString::number(M.P[i]);
	}
	
	resproba = "P = { ";
	
	for(int i = 0; i<M.T; i++)
	{
		if(i == M.T-1)
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
	int sa = sizeof(this->M.F);
	QString arcs[sa][3];
	QString resarcs;
	
	for(int i = 0; i<sa; i++)
	{
		for(int j = 0; j<3; j++)
		{
			arcs[i][j] = QString::number(F[i][j]);
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
	QString jetcontenu[M.S];
	QString resjetcontenu;
	
	for(int i = 0; i<M.S; i++)
	{
		jetcontenu[i] = QString::number(M.M[i]);
	}
	
	resjetcontenu = "M = { ";
	for(int i = 0; i<M.S; i++)
	{
		if(i == M.S-1)
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
	
	QString jetcg[M.T][2];
	QString resjetcg;
	
	for(int i = 0; i<M.T; i++)
	{
		for(int j = 0; j<2; j++)
		{
			jetcg[i][j] = QString::number(W[i][j]);
		}
	}
	
	
	resjetcg = "W = { ";
	
	
	for(int i = 0; i<M.T; i++)
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
		if(i == M.T-1)
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
	
	QString jetmax[M.S];
	QString resjetmax;
	
	for(int i = 0; i<M.S; i++)
	{
		jetmax[i] = QString::number(M.K[i]);
	}
	
	resjetmax = "K = { ";
	for(int i = 0; i<M.S; i++)
	{
		if(i == M.S-1)
		{
			resjetmax = resjetmax + jetmax[i] + " }";
		}
		else
		{
			resjetmax = resjetmax + jetmax[i] + " , ";
		}
	}
	tabjetmax->setText(resjetmax);
	
}

void InterfaceGraphique::fct_reculer()
{
    E.RenvoyerEtatReseau(M.Te-1);
    echeancierintro->setText(QString("Te = %1 <br/>").arg(M.Te)+QString("S = %1 <br/>").arg(S));
	
	// RAFRAICHIR PROBA P
	QString resproba2;
	QString proba2[2];
	
	QString proba[M.T];
	QString resproba;
	
	for(int i = 0; i<M.T; i++)
	{
		proba[i] = QString::number(M.P[i]);
	}
	
	resproba = "P = { ";
	
	for(int i = 0; i<M.T; i++)
	{
		if(i == M.T-1)
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
	int sa = sizeof(this->M.F);
	QString arcs[sa][3];
	QString resarcs;
	
	for(int i = 0; i<sa; i++)
	{
		for(int j = 0; j<3; j++)
		{
			arcs[i][j] = QString::number(F[i][j]);
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
	QString jetcontenu[M.S];
	QString resjetcontenu;
	
	for(int i = 0; i<M.S; i++)
	{
		jetcontenu[i] = QString::number(M.M[i]);
	}
	
	resjetcontenu = "M = { ";
	for(int i = 0; i<M.S; i++)
	{
		if(i == M.S-1)
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
	
	QString jetcg[M.T][2];
	QString resjetcg;
	
	for(int i = 0; i<M.T; i++)
	{
		for(int j = 0; j<2; j++)
		{
			jetcg[i][j] = QString::number(W[i][j]);
		}
	}
	
	
	resjetcg = "W = { ";
	
	
	for(int i = 0; i<M.T; i++)
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
		if(i == M.T-1)
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
	
	QString jetmax[M.S];
	QString resjetmax;
	
	for(int i = 0; i<M.S; i++)
	{
		jetmax[i] = QString::number(M.K[i]);
	}
	
	resjetmax = "K = { ";
	for(int i = 0; i<M.S; i++)
	{
		if(i == M.S-1)
		{
			resjetmax = resjetmax + jetmax[i] + " }";
		}
		else
		{
			resjetmax = resjetmax + jetmax[i] + " , ";
		}
	}
	tabjetmax->setText(resjetmax);
}

void InterfaceGraphique::fct_enregistrer()
{
    EnregistrerEcheancier(temp, fichier);
}

void InterfaceGraphique::fct_charger()
{
    charger(fichier);
}
