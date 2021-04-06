// LIBRAIRIES

// FONCTIONS

// MAIN
int main()
{
    FILE *fichier;

    GestionnaireDeFichiers GDF=(fichier);
    Echéancier E=(GDF);
    Moteur M=(E.RenvoyerEtatRéseauCourant());
    InterfaceGraphique IG=();

    return 0;
}