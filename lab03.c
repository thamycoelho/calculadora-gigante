#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct numerao{
	int dado;
	struct numerao *prox;
} numerao;

typedef struct numero{
	int sinal; //0 para positivo, 1 para negativo
	numerao *cabeca;
} numero;

void insereLista(int aux, numerao *number);
numerao *criaNumeroString(char *str, int tam);
void imprimeLista (numerao *num);

int main(int argc, char **argv)
{
	char str[101];
	int tam, x;
	numerao *n1, *n2;
	
	str[0] = '0'; //para entrar de primeira no while
	
	//while(strcmp(str, "FIM") != 0){
		scanf("%s", str);
		tam = strlen(str);
		n1 = criaNumeroString(str, tam);
		scanf("%s", str);
		tam = strlen(str);
		n2 = criaNumeroString(str, tam);
		
	//}
	
	imprimeLista (n1);
	printf("\n");
	imprimeLista (n2);
	

	return 0;
}

numerao *criaNumeroString(char *str, int tam){
	numero *num;
	numerao *number;
	
	num = malloc(sizeof(numero));
	int pos=0, i, aux;
	
	if(str[0] == '-'){
		num->sinal = 1;
		pos = 1;
	}
	number = malloc(sizeof(numerao));
	num->cabeca = number;
	
	
	for(i=tam-1; i >= pos; i--){
		aux = atoi(&str[i]);
		insereLista(aux, number);
		str[i] = '\0';
	}

	return number;
}
	
void insereLista(int aux, numerao *number){
	numerao *novo, *p= number;
	
	novo =(numerao *) malloc(sizeof(numerao));
	
	novo->dado = aux;
	novo->prox = NULL;
	
		
	while(p->prox != NULL)
			p = p->prox;
		
		p->prox = novo;
}

void imprimeLista (numerao *num) {
	numerao *p;
	for (p = num->prox; p != NULL; p = p->prox) 
      printf ("%d", p->dado);
}
