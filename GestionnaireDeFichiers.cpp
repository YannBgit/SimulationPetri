// LIBRAIRIES

#include "GestionnaireDeFichiers.hpp"
#include "Moteur.hpp"
#define TAILLE_MAX 999

// FONCTIONS

GestionnaireDeFichiers::GestionnaireDeFichiers(FILE *fichier)
{
    this->fichier = fichier;
}

GestionnaireDeFichiers::~GestionnaireDeFichiers()
{}

void GestionnaireDeFichiers::Charger(FILE *fichier)
{
	this->fichier = fichier;
	
	return;
}

int GestionnaireDeFichiers::getarc(){
	return this->arc;
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
			for(int j = 0; j < 2; j++){
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
        temp = fopen("temp.txt","r");
        fichier = fopen("RdP.txt", "a+");
        
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

Moteur GestionnaireDeFichiers::rechercheEtat(int Te, FILE *fichier){
	
	fichier = fopen("RdP.txt","r");
	
	int S;
	int T; 

	
	char *ligne = (char*)malloc(sizeof(char)*TAILLE_MAX);
	
	char *c;
	int i = 0;
	int j = 0;
	int cpt = Te * 9 + 1;
	
	if(fichier){
		if(cpt > 1){
			while(i < cpt - 1){//On parcours le fichier de départ jusqu'à la ligne Te du paramètre
					c = fgets(ligne,TAILLE_MAX,fichier);
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
		while (decoupe != NULL && i < T) {
			P[i] = atof(decoupe);
			decoupe = strtok(NULL, "P={,}");
			i++;
		}
		for(j = 0; j < i - 1; j++){
			std::cout << "P = " << P[j] << " ";
		}
		std::cout << std::endl;
		//// FIN P ////
		
		////// F ////////
		
		str = fgets(ligne,TAILLE_MAX,fichier);
		
		int arcs = 0;
		i = 0;
		
		//On souhaite savoir il y a combien d'arcs
		while(str[i] != ';'){
			if(str[i] == '{'){
				arcs++;
				i++;
			}
			else{
				i++;
			}
		}
		arcs = arcs - 1;
		this->arc = arcs;
		std::cout << "arcs = " << arcs << std::endl;
		
		int **F = (int**)malloc(sizeof(int*) * (arcs + 1));
		
		for(i = 0; i <= arcs; i++){
			F[i] = (int*)malloc((S + T) * sizeof(int));
		}
		
		decoupe = strtok(str,"F{=}; ");
		i = 0;
		while (decoupe != NULL) {
			sscanf(decoupe,"%d,%d,%d",&(F[i][0]),&(F[i][1]),&(F[i][2]));
			decoupe = strtok(NULL, "F={} ");
			std::cout << "F = " << F[i][0] << " " << F[i][1] << " " << F[i][2] << std::endl;
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
		for(j = 0; j < i ; j++){
			std::cout << "M = " << M[j] << " ";
		}
		std::cout << std::endl;
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
			std::cout << "W = ";
			while(j < 2){
				sscanf(decoupe,"%d",&(W[i][j]));
				decoupe = strtok(NULL, "{,} ");
				std::cout << W[i][j] << " ";
				j++;
			}
			std::cout << std::endl;
			i++;
		}
		////// FIN W ////////
		
		////// K ////////
		int *K = (int*)malloc(sizeof(int) * S);
		str = fgets(ligne, TAILLE_MAX,fichier);
		decoupe = strtok(str,"M={,};");
		std::cout << "decoupe = " << decoupe << std::endl;
		i = 0;
		while (decoupe != NULL && i < S) {
			decoupe = strtok(NULL, "K={,}");
			K[i] = atoi(decoupe);
			i++;
		}
		for(j = 0; j < i ; j++){
			std::cout << "K = " << K[j] << " ";
		}
		std::cout << std::endl;
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
