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

void insereLista(int aux, numerao **number);
numerao *criaNumeroString(char *str, int tam);
void imprimeLista (numerao *num);



int main(int argc, char **argv)
{
	char str[101];
	int tam, x;
	numerao *n1;
	
	scanf("%s", str);
	/*
	while(strcmp(str, "FIM") != 0){
		scanf("%s", str);
		
	}
	*/
	
	tam = strlen(str);
	printf("%d\n", tam);
	
	n1 = criaNumeroString(str, tam);
	
	imprimeLista (n1);
	

	return 0;
}

numero *criaNumeroString(char *str, int tam){
	numerao *number;
	numero *num;
	
	num = malloc(sizeof(numero));
	int pos=0, i, aux;
	
	if(str[0] == '-'){
		num->sinal = 1;
		pos = 1;
	}
	
	number = malloc(sizeof(numerao));
	
	if(!number){
		printf("NAO ALOCOU MEMORIA");
	}
	number->prox = NULL;
	
	printf("\n");
	for(i=tam-1; i >= pos; i--){
		aux = atoi(&str[i]);
		printf("%d ", aux);
		insereLista(aux, &number);
		str[i] = '\0';
	}
		printf("\n");

	num->cabeca = number;
	return num;
}
	

void insereLista(int aux, numero **number){
	numerao *novo, *p = (*number->cabeca);
	novo = (numerao *)malloc(sizeof(numerao));
    novo->dado = aux;
    novo->prox = NULL;
    
    while(p->prox != NULL){
		p = p->prox;
	}
    p->prox = novo;   
}
	
void imprimeLista (numero *num) {
   numerao *p;
   
   for (p = num->cabeca; p != NULL; p = p->prox) 
      printf ("%d\n", p->dado);
}


