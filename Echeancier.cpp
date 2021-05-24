// LIBRAIRIES

#include "Echeancier.hpp"


// FONCTIONS

Echeancier::Echeancier(Moteur RDP)
{
    this->TempsCourant = RDP.getTemps();
}

Echeancier::~Echeancier();

void Echeancier::AjouterEtatReseau(Moteur M, GestionnaireDeFichiers GDF)
{
    StockerTempsCourant(M);
    GDF.EcrireEtat(M, GDF.getTemp());

    return;
}

Moteur Echeancier::RenvoyerEtatReseauCourant()
{
    Moteur M = RenvoyerEtatReseauSelonTemps(TempsCourant);
    return M;
}

void Echeancier::StockerTempsCourant(Moteur M)
{
    this->TempsCourant = M.getTemps();
    
    return;
}

Moteur Echeancier::RenvoyerEtatReseauSelonTemps(int Te, GestionnaireDeFichiers GDF)
{
    Moteur M;

    /* Recherche dans le fichier */
    M = GDF.rechercheChaine(search, GDF.getTemp);
    /* Fin de la recherche dans le fichier et le stockage du moteur */

    return M;
}
