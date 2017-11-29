#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float* cm(int tam){
	int i;
	int aux = tam*tam;
	float *matriz = (float *)malloc(aux*sizeof(float));
	return matriz;
}

int main(int argc, char *argv[])
{

	char c[100],*mtA=argv[1],*mtB=argv[2],*mtC=argv[3];
	char buffer[10000];
	char ch;
	char bf[10];
	int i=0,j=0;

	FILE *arq1 = fopen(mtA,"r");
	FILE *arq2 = fopen(mtB,"r");

	int tam1,tam2;

	fgets(buffer,sizeof(buffer),arq1);
	tam1 = atoi(buffer);

	fgets(buffer,sizeof(buffer),arq2);
	tam2 = atoi(buffer);

	if(tam1 != tam2){
		printf("\nAs duas matrizes não são do mesmo tamanho\n");
	}else{

	strcpy(buffer,"");
	
	float *matrizA = cm(tam1);
	
	//Pega todos os valores do txt1 e coverte em uma matriz digital

	while((ch=fgetc(arq1)) != EOF){
 		if(ch == ':'){
 			matrizA[i] = atof(buffer);
 			strcpy(buffer,"");
 			i++;
 		}else if(ch == '\n'){
 			matrizA[i] = atof(buffer);
 			strcpy(buffer,"");
 			i++;
 		}else{
 			bf[0]=ch;
 			strcat(buffer,bf);
 		}
 	}
	
	float *matrizB = cm(tam2);

	i=0;
	strcpy(buffer,"");

	//Pega todos os valores do txt2 e coverte em uma matriz digital

	while((ch=fgetc(arq2)) != EOF){
 		if(ch == ':'){
 			matrizB[i] = atof(buffer);
 			strcpy(buffer,"");
			i++;
 		}else if(ch == '\n'){
 			matrizB[i] = atof(buffer);
 			strcpy(buffer,"");
			i++;
 		}else{
 			bf[0]=ch;
 			strcat(buffer,bf);
 		}
 	}
	
	float acumulador;
	int k;
	float *matrizC = cm(tam1);
	for(i=0;i<tam1;i++){
		for(j=0;j<tam1;j++){
			acumulador = 0;
			for(k=0;k<tam1;k++){
				acumulador = acumulador + (matrizA[(i*tam1)+k]*matrizB[(k*tam1)+j]);
			}
			matrizC[(i*tam1)+j] = acumulador;
		}
	}

	FILE *arq3 = fopen(mtC,"w+");
	fprintf(arq3, "%d\n",tam1);

	for (int i = 0; i < tam1; i++) {
		for (int j = 0; j < tam1; j++) {
			if (j < tam1 - 1)fprintf(arq3, "%.1f:", matrizC[(i*tam1)+j]);
	 else fprintf(arq3, "%.1f", matrizC[(i*tam1)+j]);
	}
	fprintf(arq3, "\n");
	}
	fclose(arq3);
}

	fclose(arq1);
 	fclose(arq2);
}
