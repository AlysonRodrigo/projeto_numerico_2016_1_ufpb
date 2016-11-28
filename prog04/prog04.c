#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOLER 1.0E-12

// Representa um elemento de localizador de Raiz
typedef struct parametros {
      double a;
      double b;
      double raiz; 
      int iterMax;
      int iter;
}parametros;

/* Globals Parametros */
parametros *parammetros;

//Adiciona os atributos da struct parametros
//Em caso de lista vazia a lista é iniciada
int addNewParametro(double a, double b, double raiz, int iterMax, int iter, parametros **parameT){
	
	parametros *newP;
	
	newP = malloc( sizeof (parametros) );
	
	if(newP != NULL){
		newP->a = a;
		newP->b = b;
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
	int interMax,inter;
	double a, b, raiz;

	while(!feof(file)){
		fscanf(file, "%s", str);
		switch(str[0]){
			case 'p':
				fscanf(file, "%s", str);
				a = strtod(str, NULL);
				
				fscanf(file, "%s", str);
				b = strtod(str, NULL);
				
				fscanf(file, "%s", str);
				raiz = strtod(str, NULL);
				
				fscanf(file, "%s", str);
				interMax = atoi(str);
					
				fscanf(file, "%s", str);
				inter = atoi(str);

				addNewParametro(a,b,raiz,interMax,inter,params);
			  break;
			default:
			  break;
	      }
	}

}

double fx4(double x)
{
	return (2*pow(x,3) - cos(x + 1) - 3);
}

// Precisa dos intervalos
int secante(double a, double b, int iterMax, int *iteracoes, double *raiz)
{
	double fa, fb, fx, x;
	int iter;
	iter = 0;
	fa = fx4(a);
	fb = fx4(b);
	x = b - fb*((b-a)/(fb - fa));
	fx = fx4(x);

	if(fa*fb >= 0) {
        printf("Erro, pegue outro intervalo!!\n\n");
          return 1;
	}

	while(b - a > TOLER && iter <= iterMax  && fabs(fx) > TOLER) {
		x = b - ((fb*(b-a))/(fb - fa));
		fx = fx4(x);
		if(fx*fa < 0) {
			b = x;
			fb = fx;
		}
		else {
			a = x;
			fa = fx;
		}
         iter++;
       }

       *iteracoes = iter;
       *raiz = x;
       if(iter > iterMax) {
        return 1;
       }
       return 0;
}

int main(){

    // criando a variável ponteiro para o arquivo
    FILE *pont_arq;
    parametros *params = malloc(sizeof(parametros));

    // abrindo o arquivo
    pont_arq = fopen("arquivo_atividade04.txt", "r");

   if(pont_arq == NULL){
      printf("Falha no arquivo.\n");
   }

   // Chamada de Mátodo para extrair e armazenar
   // pontotos e superfícies
   extractData(&params, pont_arq);
	
   fclose(pont_arq);

   // Incia Listas Golbais
   parammetros = params;
	

   double raiz;
   int iter, condErro;

   printf("Programa para achar a raiz da funcao, utilizando o metodo da secante, com tolerancia 1.0E^-12\n");
   
   condErro = secante(parammetros->a, parammetros->b, parammetros->iterMax, &iter, &raiz);

   if(condErro) {
     printf("Erro ao achar o ponto\n");
     printf("ponto: %f\n", raiz);
     printf("Numero de interacoes realizadas: %d\n", iter);
   }
   else {
    printf("ponto: %.16f\n", raiz);
    printf("funcao: %.16f\n", fx4(raiz));
    printf("Numero de interacoes realizadas: %d\n", iter);
   }

    return 0;
}

