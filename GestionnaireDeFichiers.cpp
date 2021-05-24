// LIBRAIRIES

#include "GestionnaireDeFichiers.hpp"
#include "Moteur.hpp"


// FONCTIONS

GestionnaireDeFichiers::GestionnaireDeFichiers(FILE *fichier)
{
    this->fichier = fichier;
}

GestionnaireDeFichiers::~GestionnaireDeFichiers();

void GestionnaireDeFichiers::CreerFichierTemporaire(Moteur M)
{
    //Pour chaque temps Te
    for (int i = 0; i < M.getTemps(); i++)
    {
        this->fichier = fopen("rdpv.txt", "r+");	// Ouvre le fichier vide en lecture et écriture
            
        if (this->fichier == NULL)	// Erreur dans l'ouverture
            std::cout << "Impossible d'ouvrir le fichier en écriture !" << std::endl;
        else
        {	// Ouverture réussie et on ecrit dans le fichier
            std::cout << "S=" << M.getNbSommets() << std::endl;
            std::cout<< "T="<< M.getNbTransitions()<< std::endl;
            std::cout<< "P="<< M.getProbabiliteTirParTransition()<< std::endl;
            std::cout<< "F="<< M.getMatricesArcs()<< std::endl;
            std::cout<< "M="<< M.getNbJetonsParSommet()<< std::endl;
            std::cout<< "W="<< M.getEvolutionNbJetonPourChaqueTransition()<< std::endl;
            std::cout<< "K="<< M.getNbMaxJetonsParSommet()<< std::endl;

            fclose (this->fichier);
        }
    }

    return;
}

void GestionnaireDeFichiers::EcrireEtat(Moteur M, FILE *fichier)
{
    //Pour chaque temps Te
    for (int i = 0; i < M.getTemps(); i++)
    {
        this->fichier = fopen("etatreseau.txt", "r++");
    
        if (fichier == NULL)	// Erreur dans l'ouverture
            std::cout << "Impossible d'ouvrir le fichier en écriture !" << std::endl;
        else
        {
            std::cout<< "S="<< M.getNbSommets()<< std::endl;
            std::cout<< "T="<< M.getNbTransitions()<< std::endl;
            std::cout<< "P="<< M.getProbabiliteTirParTransition()<< std::endl;
            std::cout<< "F="<< M.getMatricesArcs()<< std::endl;
            std::cout<< "M="<< M.getNbJetonsParSommet()<< std::endl;
            std::cout<< "W="<< M.getEvolutionNbJetonPourChaqueTransition()<< std::endl;
            std::cout<< "K="<< M.getNbMaxJetonsParSommet()<< std::endl;

            fclose (this->fichier);
        }
    }
}

void GestionnaireDeFichiers::EnregistrerEcheancier(FILE *temp, FILE *fichier)
{
    this->temp = fopen("rdvp.txt","r");
    this->fichier = fopen("rdp.txt", "r++");
        
    if (this->temp != NULL) //si le fichier existe bien
    {
    /*string ligne;*/
        while(getline(this->temp, ligne)) // On le lis ligne par ligne
        {
            if(this->fichier) // Si le lieu de destination existe ( j'entend par la le dossier )
            {
                this->fichier << ligne << std::endl; // On ecrit dans le fichier de destination
            }                          // Et au passage on le créer si il n'existe pas
            else
            {
                std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
            }
        }
    }

    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }

    return;
}

FILE *GestionnaireDeFichiers::getFichier()
{
    return this->fichier;
}

FILE *GestionnaireDeFichiers::getTemp()
{
    return this->temp;
}