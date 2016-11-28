#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOLER 1.0E-12

// Representa um elemento de localizador de Raiz
typedef struct parametros {
      double x0;
      double raiz;	
      int iterMax;
      int iter;
}parametros;

/* Globals Parametros */
parametros *parammetros;

//Adiciona os atributos da struct parametros
//Em caso de lista vazia a lista é iniciada
int addNewParametro(double x0, double raiz, int iterMax, int iter, parametros **parameT){
	
	parametros *newP;
	
	newP = malloc( sizeof (parametros) );
	
	if(newP != NULL){
		newP->x0 = x0;
		newP->raiz = raiz;		
		newP->iterMax = iterMax;
		newP->iter = iter;
				
		(*parameT) = newP;
		
		return 1;
	}
	return 0;
	
}

// Minera e armazena os parametros a partir do arquivo .txt
void extractData(parametros **params, FILE *file){

	char str[50], ch;
	int iterMax,iter;
	double x0, raiz;

	while(!feof(file)){
		fscanf(file, "%s", str);
		
		switch(str[0]){
			case 'p':
				fscanf(file, "%s", str);
				x0 = strtod(str, NULL);
			
				fscanf(file, "%s", str);
				raiz = strtod(str, NULL);

				fscanf(file, "%s", str);
				iterMax = atoi(str);
										
				fscanf(file, "%s", str);
				iter = atoi(str);

				addNewParametro(x0,raiz,iterMax,iter,params);
				break;
			default:
				break;
		}
	}

}

double fx3(double x)
{
   return pow(x,3) + 2*pow(x,2) + 10*x - 20;
}

double dfx(double x) {

   return (fx3(x+TOLER)-fx3(x))/TOLER;;

}

int newton(double x0, int iterMax, int *iteracoes, double *raiz)
{
   double f0, df0;
   int iter;

   f0 = fx3(x0);
   df0 = dfx(x0);

   while(fabs(f0) > TOLER && iter <= iterMax) {
      x0 = x0 - (f0/df0);
      f0 = fx3(x0);
      df0 = dfx(x0);
      iter++;
   }

   *raiz = x0;
   *iteracoes = iter;
   if(iter > iterMax) {
      return 1;
   }

   return 0;

}

int main(void)
{

	
       // criando a variável ponteiro para o arquivo
       FILE *pont_arq;
       parametros *params = malloc(sizeof(parametros));

       //abrindo o arquivo
       pont_arq = fopen("arquivo_atividade03.txt", "r");

       // Verifica se ocorreu erro na leitura do arquivo
       if(pont_arq == NULL){
	 printf("Falha no arquivo.\n");
       }

       // Chamada de Mátodo para extrair e armazenar
       // pontos e superfícies
       extractData(&params, pont_arq);
	
       // Fecha o arquivo
       fclose(pont_arq);

       // Incia Listas Golbais
       parammetros = params;

       double raiz;
       int iter, condErro;

	printf("Programa para achar a raiz da funcao, utilizando o metodo da Newton, com tolerancia 1.0E^-12\n");
	
	condErro = newton(parammetros->x0, parammetros->iterMax, &iter, &raiz);

	if(condErro) {
		printf("Erro ao achar o ponto\n");
		printf("ponto: %f\n", raiz);
                printf("Numero de interacoes realizadas: %d\n", iter);
	}
	else {
		printf("ponto: %.16f\n", raiz);
		printf("funcao: %.16f\n", fx3(raiz));
                printf("Numero de interacoes realizadas: %d\n", iter);
	}

        return 0;

}
