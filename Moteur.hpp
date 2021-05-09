// DIRECTIVES
#ifndef MOTEUR_HPP
#define MOTEUR_HPP

// LIBRAIRIES
#include "Echeancier.hpp" // Pour utiliser la classe Echeancier
#include <stdio.h> // Permet principalement la manipulation des flux de caractères
#include <stdlib.h> // Permet principalement la génération de nombres aléatoires

// CLASSE
class Moteur
{
    private:
    // VARIABLES
    int Te; // Temps
    int S; // Nombre de sommets
    int T; // Nombre de transitions
    float *P; // Probabilité de tir pour chaque transition, 0 < P[n] < 1
    int **F; // Matrice des arcs : un arc est décrit par 3 valeurs, la première étant un nombre indiquant le sens de l'arc
    // (0 = sommet -> transition et 1 = transition -> sommet), la deuxième l'indice du sommet l'arc il est relié, et la troisième
    // l'indice de sa transition.
    int *M; // Nombre de jetons contenu dans chaque sommet
    int **W; // Nombre de jetons consommés et générés par chaque transition
    int *K; // Nombre de jetons maximum pour chaque sommet


    public:
    // CONSTRUCTEURS
    /*
    Constructeur de base.
    */
    Moteur(Moteur M)
    {
        this = M;
    }

    // DESTRUCTEUR
    ~Moteur()
    {}

    // METHODES
    /*
    Fonction de type int pour renvoyer un entier représentant le numéro de la transition tirée choisie aléatoirement parmi plusieurs.
    Arguments de type tableau d'entiers int *T liste des indices des transitions candidates au tirage et de type entier int n le nombre
    de transitions en conflit.
    La fonction choisit aléatoire une transition à tirer et renvoi son indice.
    */
    int ResoutConflit(int *T, int n)
    {
        return T[rand() % n];
    }

    /*
    Fonction de type int * pour renvoyer un tableau d'entiers représentant les indices des transitions tirables.
    Aucun argument n'est nécessaire car la fonction utilise les variables natives au moteur.
    Pour chaque transition, la fonction évalue si elle doit être tirée ou pas selon si la transition est tirable et sa probabilité de
    tirage associée, et si besoin notre fonction de résolution de conflits.
    */
    int *Tirage()
    {
        int *TableauTirage = malloc(sizeof(float) * this->T);

        // On vérifie que la transition considérée dispose d'assez de jetons dans ses sommets sources et on évalue aléatoirement si
        // elle doit être tirée.
        for(int i = 0; i < this->T; i++)
        {
            for(int j = 0; j < (sizeof(this->F)/sizeof(this->F[0])); j++)
            {
                if((this->F[j][0] == 0) && (i == this->F[j][2]) && (this->M[this->F[j][1]] >= this->W[i][0])
                && (100*this->P[i] > (rand() % 100)))
                {
                    TableauTirage[i] = 1;
                }
                else
                {
                    TableauTirage[i] = 0;
                }
            }
        }

        // On vérifie pour chaque transition à tirer qu'elle ne soit pas en concurrence avec une autre pour les mêmes jetons. Si oui,
        // on en tire une au hasard.
        for(int i = 0; i < this->T; i++)
        {
            for(int j = 0; j < this->T; j++)
            {
                if()
                {
                    
                }
            }
        }

        return TableauTirage;
    }
    
    /*
    Fonction de type void pour modifier le tableau de Marquage int *M pour représenter le déplacement des jetons tirés.
	Argument de type int *Tirage représentant le tableau des transitions tirables que l'on va activer, 
	int *M le tableau de Marquage que l'on va modifier (déplacement de jetons),
	**F Le tableau d'arc pour savoir quelles sont les places liés aux transitions tiréés et remettre les pro,
	**W Enregistrement du nombre de jetons consommé ou générer par chaque transitions tirées
	Pour chaque Indice du tableau Tirage, la fonction active la transition correspondante et retire/ajoute le nombre de jetons
    correspondant entre les places de la transition.
	*/
	void Activer_Transitions(int *Tirage, int *M, int **F, int **W)
    {
    	//Pour chaque transition
    	for (int i = 0; i < this->T; i++) {
    		//Si la transition est tirable
    		if (Tirage[i]) {
    			//On regarde sur chaque sommet
    			for (int j = 0; j < this->S; j++) {
    				//l'impact de la transition et on enlève/ajoute des jetons
    				M[j] += W[j][Tirage[i]];

    				//Vérification que le nombre de jetons ne dépasse pas le maximum
    				if (M[j] > K[j]) M[j] = K[j];
    			} 
    		}
    	}

    	//Ajout de la résolution de conflit

    	//Le marquage est directement modifié sur *M 
    	return;
    }

	/*
	Fonction de type Moteur pour renvoyer les infos d'un RDP.
	Moteur RDP pour renvoyer notre Réseau de Pétri à l'étape précédente.
	La fonction observe si l'utilisateur a choisi ou non de reculer, si oui il demande à l'échéancier les anciennes informations du
    RDP et les renvoi.
	*/
	Moteur Reculer(Moteur RDP)
    {
	this->Te = this.Te - 1;
	return RenvoyerEtatReseauSelonTemps(Te);
    }
	
	/*
	Fonction de type int* pour renvoyer un tableau  d'entier pour être le tableau de marquage.
	Argument de type int pour le nombre de sommet du réseau et int** pour la matrice représentant le nombre de jetons consommés et
    générés.
	La fonction parcourt tout les sommet et assigne à chacun de ces sommets les jetons restants.
	*/
	int *Marquage(int S, int **W)
    {

    }
	
	/*
	Cette fonction aide pour générer le tableau de marquage. 
	Fonction de type int, pour retourner le nombre de jetons restants.
	Elle prend en argument un int**, la matrice représentant le nombre de jetons consommés et générés, et un int représentant le
    numéro d'une transition.
	Pour chaque transition, on connait le nombre de jetons générés et consommés et de là, on déduit le nombre de jetons restants.
	*/
	int Nbr_Jetons(int **W, int T)
    {
        
    }

    /*
    Accesseurs pour les variables du moteur, nommés explicitement.
    */
    int getTemps()
    {
        return this->Te;
    }

    int getNbSommets()
    {
        return this->S;
    }

    int getNbTransitions()
    {
        return this->T=M.T;
    }

    float *getProbabiliteTirParTransition()
    {
        return this->P=M.P;
    }

    int **getMatricesArcs()
    {
        return this->F=M.F;
    }

    int *getNbJetonsParSommet()
    {
        return this->M=M.M;
    }

    int **getEvolutionNbJetonPourChaqueTransition()
    {
        return this->W=M.W;
    }

    int *getNbMaxJetonsParSommet()
    {
        return this->K=M.K;
    }
}

#endif