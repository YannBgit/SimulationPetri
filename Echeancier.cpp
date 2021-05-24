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
    
    const char *chaine = "Te = ";
    char te[3];
    atol(Te,te,10);	// Conversion int en char
    char search[9];

    /* Concaténation de la chaine sous la forme de "Te = [Te en paramètre]" */
    int i, j;

    // Pour itérer la première chaîne du début à la fin
    for (i = 0; chaine[i] != '\0'; i++)
    {
        search[i] = chaine[i];
    }

    // Concaténer te dans search   
    for (j = 0; te[j] != '\0'; j++, i++)
    {
        search[i] = te[j];
    }

    search[i] = '\0';
    //       int max = i;	// Nombre de caractère dans la chaine search
    /* Fin de la concaténation */

    /* Recherche dans le fichier */
    M = GDF.rechercheChaine(search, GDF->temp);
    /* Fin de la recherche dans le fichier et le stockage du moteur */

    free(search);
    return M;
}