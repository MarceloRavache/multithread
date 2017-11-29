#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

float *matrizA;
float *matrizB;
float *matrizC;
int tamanho,process,tam1,tam2;
char *mtA,*mtB,*mtC;

void *tr(void *pr);

float* cm(int tam){
	int i;
	int aux = tam*tam;
	float *matriz = (float *)malloc(aux*sizeof(float));
	return matriz;
}
int main(int argc, char *argv[]){
	char cp[10],buffer[10000],ch,bf[10];
	system("grep -c processor /proc/cpuinfo > cpu.txt");
	FILE *cpu = fopen("cpu.txt","r");
	fgets(cp,sizeof(cp),cpu);
	process = atoi(cp);
	process *= 2;
	char c[100];
	mtA=argv[1];
	mtB=argv[2];
	mtC=argv[3];
	register int i=0,j=0;

	FILE *arq1 = fopen(mtA,"r");
	fgets(buffer,sizeof(buffer),arq1);
	tam1 = atoi(buffer);
	
	FILE *arq2 = fopen(mtA,"r");
	fgets(buffer,sizeof(buffer),arq2);
	tam2 = atoi(buffer);
	if(tam1 != tam2){
		printf("\nAs duas matrizes nÃ£o sÃ£o do mesmo tamanho\n");
	}else{

	matrizA = cm(tam1);
	strcpy(buffer,"");
	
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
	
	strcpy(buffer,"");
	matrizB = cm(tam2);

	i=0;
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

	fclose(arq1);
	fclose(arq2);
	
	matrizC = cm(tam1);

	pthread_t tid[process];

	tamanho = tam1;
	for(i=0;i<process;i++){

		pthread_create(&(tid[i]), NULL, tr, i);

	}
	for(i=0;i<process;i++){
		pthread_join(tid[i], NULL);
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
	printf("\nFinal\n");
}


void *tr(void *pr){

	int t = (int ) pr;
	register float acumulador;

	register int i,j,k,aux;
	register int tam = tamanho/process;
	register int tm = tamanho;
	aux = t * tam;

	for(i=0+aux;i<tam+aux;i++){
		for(j=0;j<tm;j++){
			acumulador = 0;
			for(k=0;k<tm;k++){
				acumulador = acumulador + ( matrizA[(i*tm)+k] * matrizB[(k*tm)+j] );
			}
			matrizC[(i*tm)+j] = acumulador;
		}
	}
}
