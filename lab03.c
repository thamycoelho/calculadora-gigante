#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct numerao{
	int dado;
	struct numerao *prox;
} numerao;

typedef struct numero{
	int sinal; //0 para positivo, 1 para negativo
	int tamanho; //quantidade de elementos do numero
	numerao *cabeca;
} numero;

void insereLista(int aux, numerao *number);
numerao *criaNumeroString(char *str, int tam);
void imprimeLista (numerao *num);
void soma(numerao *n1, numerao *n2, int tam1, int tam2);

int main(int argc, char **argv)
{
	char str[101];
	int tam1, tam2, x;
	numerao *n1, *n2;
	
	str[0] = '0'; //para entrar de primeira no while
	
	//while(strcmp(str, "FIM") != 0){
		scanf("%s", str);
		tam1 = strlen(str);
		n1 = criaNumeroString(str, tam1);
		scanf("%s", str);
		tam2 = strlen(str);
		n2 = criaNumeroString(str, tam2);
		
	//}
	
	imprimeLista (n1);
	printf("\n");
	imprimeLista (n2);
	printf("\n");

	soma(n1, n2, tam1,tam2);
	
	imprimeLista (n1);
	printf("\n");
	imprimeLista (n2);
		printf("\n");


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

void removeLista(numerao *p){
   numerao *lixo;
   lixo = p->prox;
   p->prox = lixo->prox;
   free (lixo);
}
void imprimeLista (numerao *num) {
	numerao *p;
	for (p = num->prox; p != NULL; p = p->prox) 
      printf ("%d", p->dado);
}

/*funcao que soma numeros grandes*/
void soma(numerao *n1, numerao *n2, int tam1, int tam2){
	numerao *p, *q;
	int tam, i;
	
	/*verifica qual lista tem o maior tamanho pra ser modificado*/
	if (tam1 >= tam2){
		p = n1;
		q = n2;
		tam = tam2;
	}else{
		p = n2;
		q = n1;
		tam = tam1;
	}
	
	/*soma elemento a elemento da lista*/
	for(i=0; i<=tam; i++){
		p->dado = p->dado + q->dado;
		
		/*casoa soma seja maior ou igual a 10 ele entra no if*/
		if (p->dado >=10){
			/*se nao existir um elemento depois ele cria um novo elemento na lista*/
			if(p->prox == NULL){
				insereLista(1, p);
				p->dado = p->dado - 10;
			}
			/*se existir outro elemento na lista ele soma no proximo elemento 1 e o restante soma no elemento analisado*/
			else{
				p->prox->dado += 1;
				p->dado = p->dado - 10;
			}
		}
		
		/*vai para o proximo elemento*/
		p = p->prox;
		q = q->prox;
	}
}

void subtrai(numerao *n1, numerao *n2, int tam1, int tam2){
	numerao *p, *q;
	int i, tam;
	
	if(tam1 >= tam2){
		//colocar na struct que eh positivo
		tam = tam2;
		p=n1;
		q=n2;
	}else if(tam1 < tam2){
		//colocar na struct que eh negativo
		p=n2;
		q=n1
		tam = tam1;
	}
	
	/*soma elemento a elemento da lista*/
	for(i=0; i<=tam; i++){
		p->dado = p->dado - q->dado;
		
		
		
		/*vai para o proximo elemento*/
		p = p->prox;
		q = q->prox;
	}
}

void multiplica(numerao *n1, numerao *n2, int tam1, int tam2){
	int i, j;
	for(i=0; i<=tam1; i++){
		for(j=0; j<=tam2; i++){
			
			
		}
	}
}

		
	
	
	
