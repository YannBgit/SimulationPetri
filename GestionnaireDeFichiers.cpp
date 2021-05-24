// LIBRAIRIES

#include "GestionnaireDeFichiers.hpp"
#include "Moteur.hpp"
#define TAILLE_MAX 999

// FONCTIONS

GestionnaireDeFichiers::GestionnaireDeFichiers(FILE *fichier)
{
    this->fichier = fichier;
}

GestionnaireDeFichiers::~GestionnaireDeFichiers();

void GestionnaireDeFichiers::Charger(FILE *fichier)
{
	this->fichier = fichier;
	return;
}

void GestionnaireDeFichiers::CreerFichierTemporaire()
{
	FILE *fichier;
	this->temp = fichier;
	return;
	
}

void GestionnaireDeFichiers::EcrireEtat(Moteur M, FILE *fichier)
{
	//On prends les infos du Moteur
	int Te = M.getTemps();
	int S = M.getNbSommets();
	int T = M.getNbTransitions(); 
	float *P = M.getProbabiliteTirParTransition();
	int **F = M.getMatricesArcs();
	int *M1 = M.getNbJetonsParSommet();
	int **W = M.getEvolutionNbJetonPourChaqueTransition();
	int *K = M.getNbMaxJetonsParSommet();
    
    //a+ pour ajouter à chaque fois à la fin du fichier
    fichier = fopen("Temporaire.txt","a+");
	this->fichier = fichier;
	
    if(fichier){
		
		printf("Fichier ouvert\n");
		fprintf(fichier, "Te= %d;\n", Te);
		fprintf(fichier, "S= %d;\n", S);
		fprintf(fichier, "T= %d;\n", T);

		
		//Afficher P
		fprintf(fichier, "P= {");
		for(int i = 0; i < T; i++){
			if(i == T - 1){
				fprintf(fichier, "%.1f",P[i]);
			}
			else{
				fprintf(fichier, "%.1f, ",P[i]);
			}
		}
		fprintf(fichier, "};\n");
		
		//Afficher F
		fprintf(fichier, "F= {");
		for(int i = 0; i < S; i++){
			fprintf(fichier, "{");
			for(int j = 0; j < S; j++){
				if(j == S - 1){fprintf(fichier, "%d} ",F[i][j]);}
				else{fprintf(fichier, "%d, ",F[i][j]);}
			}
		}
		fprintf(fichier, "};\n");
		
		//Afficher M
		fprintf(fichier, "M= {");
		for(int i = 0; i < S; i++){
			if(i == S - 1){
				fprintf(fichier, "%d",M1[i]);
			}
			else{
				fprintf(fichier, "%d, ", M1[i]);
			}
		}
		fprintf(fichier, "};\n");
		
		//Afficher W
		fprintf(fichier, "W= {");
		for(int i = 0; i < T; i++){
			fprintf(fichier, "{");
			for(int j = 0; j < S; j++){
				if(j == S - 1){fprintf(fichier, "%d} ",W[i][j]);}
				else{fprintf(fichier, "%d, ",W[i][j]);}
			}
		}
		fprintf(fichier, "};\n");
		
		//Afficher K
		fprintf(fichier, "K= {");
		for(int i = 0; i < S; i++){
			if(i == S - 1){
				fprintf(fichier, "%d",K[i]);
			}
			else{
				fprintf(fichier, "%d, ", K[i]);
			}
		}
		fprintf(fichier, "};\n");
		fprintf(fichier, "------------------------\n");
	}
	
	else{
		std::cout << "Erreur d'ouverture de fichier\n" << std::endl;
		exit(1);
	}
	
	fclose(fichier);
	   
}

void GestionnaireDeFichiers::EnregistrerEcheancier(FILE *temp, FILE *fichier)
{
        temp = fopen("Temporaire.txt","r");
        fichier = fopen("RdP.txt", "a+");
        
        this->fichier = fichier;
        this->temp = temp;
        
        //Configurer la chaine qui lira ligne par ligne
        char ligne[TAILLE_MAX] = "";
        if(temp)
        {
			if(fichier)
			{
				while((fgets(ligne,TAILLE_MAX,temp)) != NULL){//On parcours le fichier de départ tant qu'on est pas à la fin du fichier 
					
					fputs(ligne,fichier);// On ecrit dans le fichier de destination
				}
			}
			
			else
			{
				std::cout << "Erreur d'ouverture de fichier\n" << std::endl;
				exit(1);
			}
		}
		
		else
		{
			std::cout << "Erreur d'ouverture de fichier\n" << std::endl;
			exit(1);
		}

	fclose(fichier);
	fclose(temp);
	
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
