#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOLER 1.0E-12

// Representa um elemento que acha a raiz da funcao
typedef struct parametros {
      double a; // a) Pega do intervalo do primeiro programa
      double b; // b) Pega do intervalo do primeiro programa
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
	int interMax,iter;
	int v = 0, f = 0;
	double a, b, raiz;

	while(!feof(file)){
		fscanf(file, "%s", str);
			switch(str[0]){
				case 'p':		
					fscanf(file, "%s", str);
					raiz = strtod(str, NULL);
					
					fscanf(file, "%s", str);
					interMax = atoi(str);
					
					fscanf(file, "%s", str);
					iter = atoi(str);

					addNewParametro(a,b,raiz,interMax,iter,params);
					break;
				default:
					break;
			}
	}
}

// Tira essa função e o usuario escolhe qual vai usar
//double fx2(double x)
// {
//   int i;
//   switch(i){
//	case 1:
//	    return (0.05*pow(x,3) - 0.4*pow(x,2) + 3*sin(x));
//	case 2:
//	    return  
//   }
   
//}

double fx2(double x)
{
   return (0.05*pow(x,3) - 0.4*pow(x,2) + 3*sin(x));
}

int bissecao(double a, double b, int iterMax, int *iteracoes, double *raiz)
{
   double r, fa, fb, dx, x, fx;
   int iter, condErro;

   fa = fx2(a);
   fb = fx2(b);
   dx = b - a;
   x = (b + a)/2.0;
   fx = fx2(x);
   iter = 0;

   while(dx > TOLER && fabs(fx) > TOLER && iter <= iterMax) {
      x = (b + a)/2.0;
      fx = fx2(x);
      if(fx*fa < 0) {
         b = x;
         fb = fx;
      }
      else {
         a = x;
         fa = fx;
      }
      dx = dx/2;
      iter++;
   }
   *iteracoes = iter;
   *raiz = x;
   r = fa*fb;
   if(r < 0) {
      condErro = 0;
   }
   else {
      condErro = 1;
   }

   return condErro;

}

int main(void)
{

	// criando a variável ponteiro para o arquivo
   	FILE *pont_arq;
  	parametros *params = malloc(sizeof(parametros));

   	//abrindo o arquivo
   	pont_arq = fopen("arquivo_atividade02.txt", "r");

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

	printf("Programa para achar a bissecao, 1.0E^-12\n");
	
	condErro = bissecao(parammetros->a, parammetros->b, parammetros->iterMax, &iter, &raiz);

	if(condErro) {
		printf("Erro ao achar o ponto\n");
		printf("ponto: %f\n", raiz);
      		printf("Numero de interacoes realizadas: %d\n", iter);
	}
	else {
		printf("ponto: %.16f\n", raiz);
		printf("funcao: %.16f\n", fx2(raiz));
      		printf("Numero de interacoes realizadas: %d\n", iter);
	}

        return 0;

}
