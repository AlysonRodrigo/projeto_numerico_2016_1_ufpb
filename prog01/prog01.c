#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOLER 1.0E-12

// Representa um elemento de localizador de Raiz
typedef struct parametros {
      double v1;
      double v2;
      double z; 
      int interMax;
      int inter;
}parametros;

/* Globals Parametros */
parametros *parammetros;

//Adiciona os atributos da struct parametros
//Em caso de lista vazia a lista é iniciada
int addNewParametro(double v1, double v2, double z, int interMax, int inter, parametros **parameT){
	
	parametros *newP;
	
	newP = malloc( sizeof (parametros) );
	
	if(newP != NULL){
		newP->v1 = v1;
		newP->v2 = v2;
		newP->z = z;
		newP->interMax = interMax;
		newP->inter = inter;
		
		(*parameT) = newP;
		
		return 1;
	}
	return 0;
	
}

// Minera e armazena os parametros a partir do arquivo .txt
void extractData(parametros **params, FILE *file){

	char str[50], ch;
	int interMax,inter;
	double v1, v2, z;

	while(!feof(file)){
		fscanf(file, "%s", str);
		
		switch(str[0]){
			case 'p':
				fscanf(file, "%s", str);
				v1 = strtod(str, NULL);
			
				fscanf(file, "%s", str);
				v2 = strtod(str, NULL);
			
				fscanf(file, "%s", str);
				z = strtod(str, NULL);
				
				fscanf(file, "%s", str);
				interMax = atoi(str);
			
				fscanf(file, "%s", str);
				inter = atoi(str);

				addNewParametro(v1,v2,z,interMax,inter,params);
				break;
			default:
				break;
		}
	}

}

double fx1(double x)
{
   return (2*(pow(x, 3)) - cos(x + 1) - 3);
}

int LocRaiz(double *v1, double *v2, double z, int iterMax, int *iteracoes)
{
   double a, b, fa, fb, aureo;
   int iter, condErro;

   iter = 0;
   aureo = 2/(sqrt(5) - 1);

   if(!z) {
      a = -0.05;
      b = 0.05;
   }
   else {
      a = 0.95*z;
      b = 1.05*z;
   }
   fa = fx1(a);
   fb = fx1(b);

   while(fa*fb > 0 && iter< iterMax) {
      if(fabs(fa) < fabs(fb)) {
         a = a - aureo*(b - a);
         fa = fx1(a);
      }
      else {
         b = b + aureo*(b - a);
         fb = fx1(b);
      }
      iter++;
   }

   double raiz = fa*fb;
   *iteracoes = iter;

   if(raiz < 0) {
      *v1 = a;
      *v2 = b;
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
   pont_arq = fopen("arquivo_atividade01.txt", "r");

   // Verifica se ocorreu erro na leitura do arquivo
   if(pont_arq == NULL){
	printf("Falha no arquivo.\n");
   }

   // Chamada de Mátodo para extrair e armazenar
   // pontotos e superfícies
   extractData(&params, pont_arq);
	
   // Fecha o arquivo
   fclose(pont_arq);

   // Incia Listas Golbais
   parammetros = params;

	
   // double a = 0.0, b = 0.0, z = 5.0;
   // int interMax = 50, condErro, inter;
   int inter, condErro;

   printf("Programa para achar o intervalo em que muda o sinal, utilizando o metodo localizador de raiz\n");

   condErro = LocRaiz(&parammetros->v1, &parammetros->v2, parammetros->z, parammetros->interMax, &inter);

   if(condErro) {
      printf("Erro ao achar o ponto\n");
   }
   else {
      printf("Intervalo em que esta o ponto: [%f,%f]\n", parammetros->v1, parammetros->v2);
      printf("Numero de interacoes realizadas: %d\n", inter);
   }

   return 0;

}
