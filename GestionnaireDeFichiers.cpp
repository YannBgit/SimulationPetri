// LIBRAIRIES

#include "GestionnaireDeFichiers.hpp"
#include "Moteur.hpp"
#define TAILLE_MAX 999

// FONCTIONS

GestionnaireDeFichiers::GestionnaireDeFichiers(FILE *fichier)
{
    this->fichier = fichier;
	char *nom = "RdP.txt";
	this->nom_fichier = nom;
}

GestionnaireDeFichiers::~GestionnaireDeFichiers()
{}

void GestionnaireDeFichiers::Charger(char *nom_fichier)
{
	this->nom_fichier = nom_fichier;
}

FILE *GestionnaireDeFichiers::CreerFichierTemporaire()
{
	FILE *fic;
	fic = fopen("temp.txt","w");
	this->temp = fic;
	return temp;
}

void GestionnaireDeFichiers::EcrireEtat(Moteur M, FILE *fichier)
{
	//On prends les infos du Moteur
	int Te = M.getTe();
	int S = M.getS();
	int T = M.getT(); 
	float *P = M.getP();
	int **F = M.getF();
	int *M1 = M.getM();
	int **W = M.getW();
	int *K = M.getK();
	int arc = this->getarc();
    
    //a+ pour ajouter à chaque fois à la fin du fichier
    fichier = fopen("temp.txt","a+");
	
	this->fichier = fichier;
	
    if(fichier){
		
		printf("Fichier ouvert\n");
		fprintf(fichier, "Te=%d;\n", Te);
		fprintf(fichier, "S=%d;\n", S);
		fprintf(fichier, "T=%d;\n", T);

		
		//Afficher P
		fprintf(fichier, "P={");
		for(int i = 0; i < T; i++){
			if(i == T - 1){
				fprintf(fichier, "%.1f",P[i]);
			}
			else{
				fprintf(fichier, "%.1f,",P[i]);
			}
		}
		fprintf(fichier, "};\n");
		
		//Afficher F
		fprintf(fichier, "F={");
		for(int i = 0; i < arc; i++){
			fprintf(fichier, "{");
			for(int j = 0; j < 3; j++){
				if(j == 3 - 1){fprintf(fichier, "%d",F[i][j]);}
				else{fprintf(fichier, "%d,",F[i][j]);}
			}
			fprintf(fichier, "}");
		}
		fprintf(fichier, "};\n");
		
		//Afficher M
		fprintf(fichier, "M={");
		for(int i = 0; i < S; i++){
			if(i == S - 1){
				fprintf(fichier, "%d",M1[i]);
			}
			else{
				fprintf(fichier, "%d,", M1[i]);
			}
		}
		fprintf(fichier, "};\n");
		
		//Afficher W
		fprintf(fichier, "W={");
		for(int i = 0; i < T; i++){
			fprintf(fichier, "{");
			for(int j = 0; j < 2; j++){
				if(j == 2 - 1){fprintf(fichier, "%d",W[i][j]);}
				else{fprintf(fichier, "%d,",W[i][j]);}
			}
			fprintf(fichier, "}");
		}
		fprintf(fichier, "};\n");
		
		//Afficher K
		fprintf(fichier, "K={");
		for(int i = 0; i < S; i++){
			if(i == S - 1){
				fprintf(fichier, "%d",K[i]);
			}
			else{
				fprintf(fichier, "%d,", K[i]);
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
		std::cout << "Saving..." << std::endl;
        temp = fopen("temp.txt","r");
        fichier = fopen(nom_fichier, "a+");
        
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
	std::cout << "Save done." << std::endl;
	fclose(fichier);
	fclose(temp);
	
    return;
}

Moteur GestionnaireDeFichiers::rechercheEtat(int Te, char* nom_fichier){
	
	
	
	if (nom_fichier == nullptr) {
		nom_fichier = this->nom_fichier;
	}
	
	fichier = fopen(nom_fichier,"r");
	
	int S;
	int T; 

	
	char *ligne = (char*)malloc(sizeof(char)*TAILLE_MAX);
	
	int i = 0;
	int j = 0;
	int cpt = Te * 9 + 1;
	
	if(fichier){
		if(cpt > 1){
			while(i < cpt - 1){//On parcours le fichier de départ jusqu'à la ligne Te du paramètre
					char *c = fgets(ligne,TAILLE_MAX,fichier);
					i++;
				}
		}
		
		////// TE ////////
		char *str = fgets(ligne,TAILLE_MAX,fichier);
		char *decoupe;
		decoupe = strtok(str,"Te=;");
		Te = atoi(decoupe);
		//// FIN TE ////
		
		////// S ////////
		str = fgets(ligne,TAILLE_MAX,fichier);
		decoupe = strtok(str,"S=;");
		S = atoi(decoupe);

		//// FIN S ////
		
		////// T ////////
		str = fgets(ligne,TAILLE_MAX,fichier);
		decoupe = strtok(str,"T=;");
		T = atoi(decoupe);
		//// FIN T ////
		
		////// P ////////
		float *P = (float*)malloc(sizeof(float) * T);
		str = fgets(ligne, TAILLE_MAX,fichier);
		decoupe = strtok(str,"P={,}");
		i = 0;
		while (decoupe != NULL && i < T){
			P[i] = atof(decoupe);
			decoupe = strtok(NULL, "P={,}");
			i++;
		}

		//// FIN P ////
		
		////// F ////////
		str = fgets(ligne, TAILLE_MAX, fichier);
		
		int arcs = 0;
		i = 0;
		
		//On souhaite savoir il y a combien d'arcs
		while(str[i] != ';')
		{
			if(str[i] == '{')
			{
				arcs++;
				i++;
			}
			else
			{
				i++;
			}
		}

		arcs = arcs - 1;
		this->arc = arcs;
		
		int **F = (int**)malloc(sizeof(int*) * (arcs + 1));
		
		for(i = 0; i <= arcs; i++){
			F[i] = (int*)malloc((S + T) * sizeof(int));
		}
		decoupe = strtok(str,"F{=}; ");
		i = 0;
		while (decoupe != NULL && i < arc) {
			sscanf(decoupe,"%d,%d,%d",&(F[i][0]),&(F[i][1]),&(F[i][2]));
			decoupe = strtok(NULL, "F={} ");
			i++;
		}
		////// FIN F ////////
		
		////// M ////////
		int *M = (int*)malloc(sizeof(int) * S);
		str = fgets(ligne, TAILLE_MAX,fichier);
		decoupe = strtok(str,"M={,};");
		i = 0;
		while (decoupe != NULL && i < S) {
			M[i] = atoi(decoupe);
			decoupe = strtok(NULL, "M={,}");
			i++;
		}

		//// FIN M ////
		
		////// W ////////
		
		int **W = (int **)malloc(sizeof(int*) * 10);
		for(int i = 0; i < 10; i++){
			W[i] = (int*)malloc(10 * sizeof(int));
		}
		str = fgets(ligne,TAILLE_MAX,fichier);
		decoupe = strtok(str,"W{=};, ");
		i = 0;
		while (decoupe != NULL && i < T){
			j = 0;

			while(j < 2){
				sscanf(decoupe,"%d",&(W[i][j]));
				decoupe = strtok(NULL, "{,} ");
				j++;
			}
			i++;
		}
		////// FIN W ////////
		
		////// K ////////
		int *K = (int*)malloc(sizeof(int) * S);
		str = fgets(ligne, TAILLE_MAX,fichier);
		decoupe = strtok(str,"M={,};");
		i = 0;
		while (decoupe != NULL && i < S) {
			decoupe = strtok(NULL, "K={,}");
			K[i] = atoi(decoupe);
			i++;
		}

		//// FIN K ////
		
		Moteur *m = new Moteur(Te, S, T, P, F, M, W, K);
		free(ligne);
		return *m;
	}
	
	else
	{
		std::cout << "Erreur d'ouverture de fichier\n" << std::endl;
		exit(1);
	}
}

FILE *GestionnaireDeFichiers::getFichier()
{
    return this->fichier;
}

FILE *GestionnaireDeFichiers::getTemp()
{
    return this->temp;
}

int GestionnaireDeFichiers::getarc()
{
	return this->arc;
}

void GestionnaireDeFichiers::afficher(Moteur M, GestionnaireDeFichiers GDF){
			//std::cout << "--------------------------------------" << std::endl;
			std::cout << "Te = " << M.getTe() << std::endl;
			std::cout << "T = " << M.getT() << std::endl;
			std::cout << "S = " << M.getS() << std::endl;
		
			//P
			std::cout << "P = {";
			for(int i = 0; i < M.getT(); i++){
				if(i == M.getT() - 1){
					std::cout << M.getP()[i];
				}
				else {
					std::cout << M.getP()[i] << ",";
				}
			}
			std::cout << "}" << std::endl;
			//F
			std::cout << "F = {";
			for(int i = 0; i < GDF.getarc(); i++){
				std::cout << "{";
				for(int j = 0; j < 3; j++){
					if(j == 2){
						std::cout << M.getF()[i][j];
					}
					else{
						std::cout << M.getF()[i][j] << ",";
					}
				}
				std::cout << "}";
			}
			std::cout << "}" << std::endl;
			//M
			std::cout << "M = {";
			for(int i = 0; i < M.getS(); i++){
				if(i == M.getS() - 1){
					std::cout << M.getM()[i];
				}
				else{
					std::cout << M.getM()[i] << ",";
				}
			}
			std::cout << "}" << std::endl;
			//W
			std::cout << "W = {";
			for(int i = 0; i < M.getT(); i++){
				std::cout << "{";
				for(int j = 0; j < 2; j++){
					if(j == 1){
						std::cout << M.getW()[i][j] << "}";
					}
					else{
						std::cout << M.getW()[i][j] << ",";
					}
				}
			}
			std::cout << "}" << std::endl;
			//K
			std::cout << "K = {";
			for(int i = 0; i < M.getS(); i++){
				if(i == M.getS() - 1){
					std::cout << M.getK()[i];
				}
				else{
					std::cout << M.getK()[i] << ",";
				}
			}
			std::cout << "}" << std::endl;
			std::cout << "--------------------------------------" << std::endl;
}
