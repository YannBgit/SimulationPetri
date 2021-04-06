// DIRECTIVES
#ifndef MOTEUR_HPP
#define MOTEUR_HPP

// LIBRAIRIES

// CLASSE
class Moteur
{
    private:
    // VARIABLES
    int S; // nombre de sommets
    int T; // nombre de transitions
    float *P; // probabilité de tir pour chaque transition, 0<P[n]<1
    int **F; // matrice des arcs : un arc est décrit par 2 valeurs, la première étant l'indice du sommet auquel il est relié, et la seconde l'indice de sa transition
    int *M; // nombre de jetons contenu dans chaque sommet
    int **W; // nombre de jetons consommés et générés par chaque transition
    int *K; // nombre de jetons maximum pour chaque sommet
    int Te; // temps

    public:
    // CONSTRUCTEURS
    Moteur(int S, int T, float *P, int **F, int *M, int **W, int *K, int Te)
    {}

    // DESTRUCTEUR
    ~Moteur()
    {}

    // METHODES
    /*
    Fonction de type int pour renvoyer un entier représentant le numéro de la transition tirée choisie aléatoirement parmi plusieurs.
    Argument de type tableau d'entiers int *T liste des indices des transitions candidates au tirage.
    La fonction choisit aléatoire une transition à tirer et renvoi son indice.
    */
    int RésoutConflit(int *T)
    {}

    /*
    Fonction de type int * pour renvoyer un tableau d'entiers représentant les indices des transitions tirables.
    Arguments int T nombre de transitions du réseau de Petri, donc un entier, et float *P donc un tableau de nombres flottants représentant la probabilité de tir
    associée à chaque transition.
    Pour chaque transition, la fonction évalue si elle doit être tirée ou pas selon si la transition est tirable et sa probabilité de tirage associée, et si besoin notre fonction de résolution de
    conflits.
    */
    int *Tirage(int T, float *P)
    {}
    
    /*
    Fonction de type int* pour renvoyer le tableau de Marquage représentant le déplacements des jetons tirés.
	Argument de type int *Tirage représentant le tableau des transitions tirable que l'on va activer, 
	int *M le tableau de Marquage que l'on va modifier (déplacement de jetons),
	**F Le tableau d'arc pour savoir quelles sont les places liés aux transitions tiréés et remettre les pro,
	**W Enregistrement du nombre de jetons consommé ou générer par chaque transitions tirées
	Pour chaque Indice du tableau Tirage, la fonction active la transition correspondante et retire/ajoute le nombre de jetons correspondant entre les places de la transition.
	*/
	int* Activer_Transitions(int *Tirage, int *M, int **F, int **W)
	{}

	/*
	Fonction de type Moteur pour renvoyer les infos d'un RDP.
	Argument de type bool Ordre pour simuler un choix, si vrai, on recule, sinon on continue notre tour dans le RDP,
	Moteur RDP pour renvoyer notre Réseau de Pétri à l'étape précédente.
	La fonction observe si l'utilisateur a choisi ou non de reculer, si oui il demande à l'échéancier les anciennes informations du RDP et les renvois.
	*/
	Moteur Reculer(bool Ordre, Moteur RDP)
	{}
}

#endif
