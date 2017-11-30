#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//variaveis globais para ter acesso nas threads
float **matriz1,**matriz2,**matriz3;

int tamanho,processos;

void *paralelo(void *id);

//função para criar em ponteiros allocados as matrizes dinamicamente
float** criarmatriz(int tamanhoM){
	int i;
	float **matriz = (float **)malloc(tamanhoM*sizeof(float*));
	for(i=0;i<tamanhoM;i++){
		matriz[i]= (float *)malloc(tamanhoM*sizeof(float));
	}
	return matriz;
}
					   
int main(int argc, char *argv[]){
	
	char cpuinfo[100],buffer[10000],caractere,minibuffer[10];
	
	system("grep -c processor /proc/cpuinfo > cpu.txt");
	FILE *cpu = fopen("cpu.txt","r");
	
	fgets(cpuinfo,sizeof(cpuinfo),cpu);
	int cputext = atoi(cpuinfo);
	processos = cputext;
	fclose(cpu);
	char c[100];
	//argumento 1
	char *matrizA=argv[1];
	//argumento 2
	char *matrizB=argv[2];
	//argumento 3
	char *matrizC=argv[3];
	
	int i=0,j=0;

	//abrir arquivo do argumento 1
	FILE *arquivo1 = fopen(matrizA,"r");
	//pega a primeira linha do arquivo que tem o tamanho da matriz
	fgets(buffer,sizeof(buffer),arquivo1);
	//converte a String em inteiro
	int tamanho1 = atoi(buffer);
	
	FILE *arquivo2 = fopen(matrizA,"r");
	fgets(buffer,sizeof(buffer),arquivo2);
	int tamanho2 = atoi(buffer);
	
	//verifica se as duas tem a mesma proporção
	if(tamanho1 != tamanho2){
		printf("\nAs duas matrizes nÃ£o sÃ£o do mesmo tamanho\n");
	}else{
	tamanho = tamanho1;//armazena o tamanho
		
	//armazena uma matriz dinamicamente alocada no ponteiro global
	matriz1 = criarmatriz(tamanho1);
	//zera o buffer de String
	strcpy(buffer,"");
	
	while((caractere=fgetc(arquivo1)) != EOF){//enquanto ele não encontrar o final do arquivo, ele vai pegando o primeiro caractere
 		if(caractere == ':'){// verifica se o caractere é igual ao ':' assim ele vai saber que chegou no final do numero
			
 			matriz1[i][j] = atof(buffer);//converte o buffer string(que contem o valor a ser armazenado em float), armazena o valor convertido na posição dele
			
 			strcpy(buffer,"");//zera o buffer
			
 			j++;//passa para a proxima coluna daquela linha
			
 		}else if(caractere == '\n'){//verifica se o caractere é igual a \n(final da linha)
 			matriz1[i][j] = atof(buffer);
 			strcpy(buffer,"");
 			i++;//passa para a porxima linha
			j=0;//e recomeça a coluna
 		}else{
 			minibuffer[0]=caractere;//guarda o caractere em um mini buffer
 			strcat(buffer,minibuffer);//junta o caractere no buffer que tinha antes
 		}
 	}
	
	strcpy(buffer,"");//zera o buffer
		
	matriz2 = criarmatriz(tamanho2);

	i=0;
	j=0;
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

	//fecha os dois arquivos
	fclose(arquivo1);
	fclose(arquivo2);
	
	matriz3 = criarmatriz(tamanho1);
	
	//cria os identificadores das threads de acordo com o que tem em process que é o tanto de cores que o processador tem
	pthread_t tid[processos];
	//armazena o tamanho da matriz em uma variavel global
	tamanho = tamanho1;
	
	for(i=0;i<processos;i++){//cria as threads

		pthread_create(&(tid[i]), NULL, paralelo, i);//passando o valor que esta em i(que é o idenficador das partes)

	}
	for(i=0;i<processos;i++){
		pthread_join(tid[i], NULL);//faz com que o processo principal espere as threads terminarem
	}
	
	FILE *arquivo3 = fopen(matrizC,"w+");
	
	fprintf(arquivo3, "%d\n",tamanho1);//escreve o tamanho da matriz e pula a linha no arquivo

	for (int i = 0; i < tamanho1; i++) {
		for (int j = 0; j < tamanho1; j++) {
			if (j < tamanho1 - 1)fprintf(arquivo3, "%.1f:", matriz3[i][j]);//ele escreve no arquivo os valores colocando o ':' no final ate encontrar a penultima posição da coluna
	 else fprintf(arquivo3, "%.1f", matriz3[i][j]);//ele escreve o ultimo valor na ultima posição
	}
	fprintf(arquivo3, "\n");//ele escreve a quebra de linha
	}
	fclose(arquivo3);
	}
	printf("\nFinal\n");
}


void *paralelo(void *id){

	
	float acumulador;
	int identificador = (int) id;

	int i,j,k,auxiliar;
	int tamanhoParte = tamanho/processos;
	auxiliar = identificador * tamanhoParte;

	for(i=0+auxiliar;i<tamanhoParte+auxiliar;i++){
		for(j=0;j<tamanho;j++){
			acumulador = 0;
			for(k=0;k<tamanho;k++){
				acumulador = acumulador + ( matriz1[i][k] * matriz2[k][j] );
			}
			matriz3[i][j] = acumulador;
		}
	}
}
