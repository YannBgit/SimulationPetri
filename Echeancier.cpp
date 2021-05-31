// LIBRAIRIES

#include "Echeancier.hpp"


// FONCTIONS

Echeancier::Echeancier(Moteur M)
{
    this->TempsCourant = M.getTe();
}

Echeancier::~Echeancier()
{}

void Echeancier::StockerTempsCourant(Moteur M)
{
    this->TempsCourant = M.getTe();
    
    return;
}

void Echeancier::AjouterEtatReseau(Moteur M, GestionnaireDeFichiers GDF)
{
    StockerTempsCourant(M);
    GDF.EcrireEtat(M, GDF.getTemp());

    return;
}

Moteur Echeancier::RenvoyerEtatReseauSelonTemps(int Te, GestionnaireDeFichiers GDF, char *nom_fichier)
{
    return GDF.rechercheEtat(Te,nom_fichier);
}