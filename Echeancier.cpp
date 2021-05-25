// LIBRAIRIES

#include "Echeancier.hpp"


// FONCTIONS

Echeancier::Echeancier(Moteur M)
{
    this->TempsCourant = M.getTe();
}

Echeancier::~Echeancier()
{}

void Echeancier::AjouterEtatReseau(Moteur M, GestionnaireDeFichiers GDF)
{
    StockerTempsCourant(M);
    GDF.EcrireEtat(M, GDF.getTemp());

    return;
}

Moteur Echeancier::RenvoyerEtatReseauSelonTemps(int Te, GestionnaireDeFichiers GDF)
{
    return GDF.rechercheEtat(Te, GDF.getTemp());
}

void Echeancier::StockerTempsCourant(Moteur M)
{
    this->TempsCourant = M.getTe();
    
    return;
}
