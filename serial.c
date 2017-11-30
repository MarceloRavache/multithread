#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float** criarmatriz(int tamanho);

int main(int argc, char *argv[])
{
	printf("\nOK\n");
	char *matrizA=argv[1],*matrizB=argv[2],*matrizC=argv[3];
	char buffer[10000];
	char caractere;
	char minibuffer[10];
	int i=0,j=0;
	printf("\nOK%s\n",matrizA);

	FILE *arquivo1 = fopen(matrizA,"r");
	FILE *arquivo2 = fopen(matrizB,"r");
	printf("\nOK\n");
	int tamanho1,tamanho2;
	printf("\nOK\n");
	fgets(buffer,sizeof(buffer),arquivo1);
	printf("\nOK\n");
	tamanho1 = atoi(buffer);
		printf("\nOK\n");
	fgets(buffer,sizeof(buffer),arquivo2);
	tamanho2 = atoi(buffer);
	printf("\nOK\n");
	if(tamanho1 != tamanho2){
		printf("\nAs duas matrizes não são do mesmo tamanho\n");
	}else{

	strcpy(buffer,"");
	
	float **matriz1 = criarmatriz(tamanho1);
	
	//Pega todos os valores do txt1 e coverte em uma matriz digital

	while((caractere=fgetc(arquivo1)) != EOF){
 		if(caractere == ':'){
 			matriz1[i][j] = atof(buffer);
 			strcpy(buffer,"");
 			j++;
 		}else if(caractere == '\n'){
 			matriz1[i][j] = atof(buffer);
 			strcpy(buffer,"");
 			i++;
			j=0;
 		}else{
 			minibuffer[0]=caractere;
 			strcat(buffer,minibuffer);
 		}
 	}
	
	float **matriz2 = criarmatriz(tamanho2);

	i=0;
	strcpy(buffer,"");

	//Pega todos os valores do txt2 e coverte em uma matriz digital

	while((caractere=fgetc(arquivo2)) != EOF){
 		if(caractere == ':'){
 			matriz2[i][j] = atof(buffer);
 			strcpy(buffer,"");
			j++;
 		}else if(caractere == '\n'){
 			matriz2[i][j] = atof(buffer);
 			strcpy(buffer,"");
			i++;
			j=0;
 		}else{
 			minibuffer[0]=caractere;
 			strcat(buffer,minibuffer);
 		}
 	}
	
	float acumulador;
	int k;
	float **matriz3 = criarmatriz(tamanho1);
	for(i=0;i<tamanho1;i++){
		for(j=0;j<tamanho1;j++){
			acumulador = 0;
			for(k=0;k<tamanho1;k++){
				acumulador = acumulador + (matriz1[i][k] * matriz2[k][j]);
			}
			matriz3[i][j] = acumulador;
		}
	}

	FILE *arquivo3 = fopen(matrizC,"w+");
	fprintf(arquivo3, "%d\n",tamanho1);

	for (int i = 0; i < tamanho1; i++) {
		for (int j = 0; j < tamanho1; j++) {
			if (j < tamanho1 - 1)fprintf(arquivo3, "%.1f:", matriz3[i][j]);
	 else fprintf(arquivo3, "%.1f", matriz3[i][j]);
	}
	fprintf(arquivo3, "\n");
	}
	fclose(arquivo3);
}

	fclose(arquivo1);
 	fclose(arquivo2);
}

float** criarmatriz(int tamanho){
	int i;
	float **matriz = (float **)malloc(tamanho*sizeof(float *));
	for(i=0;i<tamanho;i++){
		matriz[i]= (float *) malloc(tamanho*sizeof(float));
	}
	return matriz;
}
