// LIBRAIRIES

#include "Moteur.hpp"

// FONCTIONS

Moteur::Moteur(int Te, int S, int T, float *P, int **F, int *M, int **W, int *K)
{
    this->Te = Te;
    this->S = S;
    this->T = T;
    this->P = P;
    this->F = F;
    this->M = M;
    this->W = W;
    this->K = K;
}

Moteur::~Moteur()
{}

int Moteur::ResoutConflit(int *T, int n)
{
    return T[rand() % n];
}

int *Moteur::Tirage(GestionnaireDeFichiers GDF)
{
    int *TableauTirage = (int *)malloc(sizeof(int) * this->T);

    // On vérifie que la transition considérée dispose d'assez de jetons dans ses sommets sources et on évalue aléatoirement si
    // elle doit être tirée.
    for(int i = 0; i < this->T; i++)
    {
        //La transition peut être tirée
        TableauTirage[i] = 1;
        for(int j = 0; j < GDF.getarc(); j++)
        {   
            //Sauf si un des sommets sources n'a pas assez de jetons
            if((this->F[j][0] == 0) && (i == this->F[j][2]) && (this->M[this->F[j][1]] < this->W[i][0]))
            {
                TableauTirage[i] = 0;
            }
        }
        //On choisit ensuite de façon aléatoire si elle sera tiré
        //Si la valeur tirée aléatoirement est au dessus de la probabilité de tir
        //Alors elle ne sera pas tirée
        if ((TableauTirage[i] == 1) && ((100 * this->P[i]) <= (rand() % 100)))
            TableauTirage[i] = 0;

    }

    // On vérifie pour chaque transition à tirer qu'elle ne soit pas en concurrence avec une autre pour les mêmes jetons. Si oui,
    // on en tire une au hasard.
    for(int i = 0; i < GDF.getarc(); i++)
    {
        if((this->F[i][0] == 0))
        {
            int nbTransitionsConflit = 1;
            int *IDtransitionsConflit = (int *)malloc(nbTransitionsConflit * sizeof(int));
            IDtransitionsConflit[0] = this->F[i][2];

            for(int j = 0; j < GDF.getarc(); j++)
            {
                if((this->F[i] != this->F[j]) && (this->F[j][0] == 0) && (this->F[i][1] == this->F[j][1]) && ((this->W[this->F[i][2]][0] +
                this->W[this->F[j][2]][0]) > this->M[this->F[i][1]]))
                {
                    nbTransitionsConflit++;
                    IDtransitionsConflit = (int *)realloc(IDtransitionsConflit, sizeof(int) * nbTransitionsConflit);
                    IDtransitionsConflit[nbTransitionsConflit - 1] = this->F[j][2];
                }
            }

            // Mise à zéro des transitions en conflit
            if(nbTransitionsConflit > 1)
            {
                for(int k = 0; k < nbTransitionsConflit; k++)
                {
                    TableauTirage[IDtransitionsConflit[k]] = 0;
                }

                // Désignation de la transition à tirer
                TableauTirage[ResoutConflit(IDtransitionsConflit, nbTransitionsConflit)] = 1;
            }

            free(IDtransitionsConflit);
        }
    }

    return TableauTirage;
}

void Moteur::Activer_Transitions(int *Tirage, GestionnaireDeFichiers GDF)
{
    //Pour chaque transition
    for (int i = 0; i < this->T; i++) {
        //Si la transition est tirable
        if (Tirage[i]) {
            //On regarde pour chaque arc
            for (int j = 0; j < GDF.getarc(); j++) {
                //Si l'arc est lié à la transition
                if (this->F[j][2] == i) {
                    //Si l'arc est place -> transition on enlève un jeton
                    if (this->F[j][0] == 0 && this->M[F[j][1]] > 0) this->M[F[j][1]] -= 1;
                    //Sinon on en rajoute un
                    else {
                        if (this->M[F[j][1]] + 1 > this->K[F[j][1]]) 
                            this->M[F[j][1]] = this->K[F[j][1]];
                        else this->M[F[j][1]] += 1;
                    }
                }
            }
        }
    }

    this->Te++;

    //Le marquage est directement modifié sur *M
    return;
}

void Moteur::Reculer(Echeancier E, GestionnaireDeFichiers GDF, char *nom_fichier)
{
    E.RenvoyerEtatReseauSelonTemps(this->Te--,GDF, nom_fichier);
}


int Moteur::Nbr_Jetons(int **W, int T, int S, int *M)
{
    int nbr;
    nbr = W[S][T] + M[S];
    return nbr;
}

int *Moteur::transition_possible(int S, int T, int **F)
{
    int *transition = (int*) malloc(sizeof(int)*T);
    int i;
    //initialisation de transition
    for(i=0;i<T;i++)
    {
      transition[i]=0;
    }
    
    for(i=0;i<T;i++)
    {
        if(F[0][S]==i) transition[i]=1 + transition[i];
        if(F[1][S]==i) transition[i]=1 + transition[i];
    }
        return transition;
}

int	Moteur::nbr_transition(int *transition, int T)
{

    int nbr_transi=0;

    for(int i=0;i<T;i++)
        if(transition[i]) nbr_transi++;

    return nbr_transi;
}

int *Moteur::Marquage(Moteur RDP)
{
	int S = RDP.getS();
    int *marq = (int*) malloc(sizeof(int)*S);
    int *transi_p = (int*) malloc(sizeof(int)*T); //ce tableau à en valeur des transitions
    int nbr_transi;
    int i,j;

    for(i=0; i<S;i++) marq[i]=0;

    for(i=0; i<S; i++)
    {
        transi_p = transition_possible(S,RDP.getT(), RDP.getF());
        nbr_transi = nbr_transition(transi_p, RDP.getT());

        for(j=0; j<=nbr_transi;j++)
        {
            marq[i] = marq[i]+Nbr_Jetons(RDP.getW(),transi_p[j],S,RDP.getM());
        }
    }
    free(transi_p);

    return marq;
}

int Moteur::getTe()
{
    return this->Te;
}

int Moteur::getS()
{
    return this->S;
}

int Moteur::getT()
{
    return this->T;
}

float *Moteur::getP()
{
    return this->P;
}

int **Moteur::getF()
{
    return this->F;
}

int *Moteur::getM()
{
    return this->M;
}

int **Moteur::getW()
{
    return this->W;
}

int *Moteur::getK()
{
    return this->K;
}
