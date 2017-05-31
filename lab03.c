
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

typedef struct{
	int topo;
	int tam;
	numero **elem;
}pilha;

void insereLista(int aux, numerao *number);
numero *criaNumeroString(char *str);
void imprimeLista (numero *num);
void soma(numero *n1, numero *n2,pilha *stack);
void subtrai(numero *n1, numero *n2,pilha *stack);
void condSubtrai(numero *n1, numero *n2,pilha *stack);
void liberaLista(numerao *p);	
numero *copiaLista(numero *n1);
void multiplica(numero *n1, numero *n2, pilha *stack);
void imprimePilha(pilha *p);
numero *pop(pilha *p);
void push(pilha *p, numero *n);
int pilhaCheia(pilha *p);
int pilhaVazia(pilha *p);
void criaPilha(pilha *p);
numero *retornaTopo(pilha *stack);



int main(int argc, char **argv)
{
	char str[1001];
	numero *n1;
	pilha *stack;
	stack = malloc(sizeof(pilha));
	
	criaPilha(stack);
	
	scanf("%s", str);
	
	while(strcmp(str, "FIM") != 0){
		if(strcmp(str, "+") == 0){
			soma(pop(stack), pop(stack), stack);
			imprimeLista(stack->elem[stack->topo]);
		}
		else if(strcmp(str, "-") == 0){
			condSubtrai(pop(stack), pop(stack), stack);
			imprimeLista(stack->elem[stack->topo]);
		}
		else if((strcmp(str, "*") == 0)){
			multiplica(pop(stack), pop(stack), stack);
			imprimeLista(stack->elem[stack->topo]);
		}
		else if((strcmp(str, "/") == 0)){
			//funcao que divide
			imprimeLista(stack->elem[stack->topo]);
		}
		else if((strcmp(str, "%") == 0)){
			//funcao que da o resto da divisao
			imprimeLista(stack->elem[stack->topo]);
		}
		else{
			n1 = criaNumeroString(str); //era pra colocar na pilha
			push(stack, n1);
		}
		scanf("%s", str);
	}
	


	//soma(pop(stack), pop(stack), stack);
	
	
	
	//multiplica(pop(stack), pop(stack), stack);
	//condSubtrai(pop(stack), pop(stack), stack);
	printf("\n\n");
	
	//imprimePilha(stack);
	//copy = multiplica(n1,n2);
		
	//liberaLista(n1->cabeca);
	//liberaLista(n2->cabeca);
	
	//free(n1);
	//free(n2);

	return 0;
}

numero *criaNumeroString(char *str){
	numero *num;
	numerao *number;
	int pos=0, i, aux, tam;
	
	num = malloc(sizeof(numero));
	number = malloc(sizeof(numerao));
	number->prox = NULL;
	number->dado = 0;
	
	if(str[0] == '-'){
		num->sinal = 1;
		num->tamanho = strlen(str)-1;
		pos = 1;
	}else{
		num->sinal = 0;
		num->tamanho = strlen(str);

	}
	tam = strlen(str);
		
	for(i=tam-1; i >= pos; i--){
		aux = atoi(&str[i]);
		insereLista(aux, number);
		str[i] = '\0';
	}
	
	num->cabeca = number;

	return num;
}
	
void insereLista(int aux, numerao *number){
	numerao *novo, *p= number;
	
	novo =(numerao *) malloc(sizeof(numerao));
	
	novo->dado = aux;
	novo->prox = NULL;
	
		
	while(p->prox != NULL) p = p->prox;
		
	p->prox = novo;
}

void removeLista(numerao *p){
   numerao *lixo;
   lixo = p->prox;
   p->prox = lixo->prox;
   free (lixo);
}

void imprimeLista (numero *num) {
	numerao *p;
	if(num->cabeca != NULL){
		if(num->sinal == 1){
			printf("-");
		}
		p=num->cabeca;
		for (p = p->prox; p != NULL; p = p->prox) 
	      printf ("%d", p->dado);
  }
  printf("\n");
}

/*funcao que soma numeros grandes*/
void soma(numero *n1, numero *n2, pilha *stack){
	numerao *p, *q;
	
	if(n1->tamanho < n2->tamanho){
		soma(n2, n1, stack);
		return;
	}
	
	
	if(n1->sinal == 1 && n2->sinal == 1){
		n1->sinal = 1;
	} else if(n1->sinal == 1 && n2->sinal ==0){
		n1->sinal = 0;
		condSubtrai(n2,n1, stack);
		return;
	}else if(n1->sinal == 0 && n2->sinal == 1){
		n2->sinal = 0;
		condSubtrai(n1,n2, stack);
		return;
	}
	
	p = n1->cabeca;
	q = n2->cabeca;
	

	/*soma e lemento a elemento da lista*/
	while(p != NULL && q != NULL){

		p->dado = p->dado + q->dado;
		
		/*casoa soma seja maior ou igual a 10 ele entra no if*/
		if (p->dado >=10){
			/*se nao existir um elemento depois ele cria um novo elemento na lista*/
			if(p->prox == NULL){
				insereLista(1, n1->cabeca);
				n1->tamanho ++;
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
	
	push(stack, n1);
	liberaLista(n2->cabeca);
	free(n2);
}

void condSubtrai(numero *n2, numero *n1, pilha  *stack){
	numerao *p, *q;
	int i;
	
	//caso o tamnho do numero 1 seja maior que o do numero dois (n1>n2)
	if(n1->tamanho > n2->tamanho){

		//caso o numero 1 seja negativo e o numero 2 seja positivo
		if(n1->sinal == 1 && n2->sinal == 0){
			//atribui a n2 = -n2 para ter -n1-n2 = -(n1+n2)
			n2->sinal = 1;
			soma(n1,n2, stack);
		}
		//caso o numero 1 seja positivo e o numero 2 negativo
		else if(n1->sinal == 0 && n2->sinal == 1){
			//considera que n1-(-n2) = n1+n2 e chama a funcao soma
			n2->sinal = 0;
			soma(n1,n2, stack);
		}else{
			subtrai(n1,n2, stack);
		}
	}
	//caso o tamanho do numero 1 seja menor que o numero dois (n2>n1)
	else if(n1->tamanho < n2->tamanho){
		if(n1->sinal == 1 && n2->sinal == 1){
			n1->sinal = 0;
			n2->sinal = 0;
			subtrai(n2, n1, stack);
		}
		//caso n1 seja negativo e n2 positivo -n2-n2 = -(n1+n2) entao chama a funcao soma
		else if(n1->sinal == 1 && n2->sinal == 0){
			n2->sinal = 1;
			soma(n1,n2, stack);
		}
		//caso n1-(-n2) = n1+n2, entao chama a funcao soma para ambos positivos
		else if(n1->sinal == 0 && n2->sinal == 1){
			n2->sinal =0;
			soma(n1,n2,stack);
		}else if(n1->sinal == 0 && n2->sinal == 0){
			subtrai(n2,n1, stack);
			n2->sinal = 1;
		}
		
	}
	
	else if(n1->tamanho == n2->tamanho){
		p = n1->cabeca;
		q = n2->cabeca;
		
		for(i=n1->tamanho; i>0; i--){
					
			if(p->prox->dado > q->prox->dado){
				if((n1->sinal == 1 && n2->sinal == 0) || (n1->sinal == 0 && n2->sinal == 1)){
					soma(n1,n2, stack);
					return;
				}
				else{
					subtrai(n1, n2,stack);
					return;
				}
				
			}else if(p->prox->dado < q->prox->dado){
				if((n1->sinal == 1 && n2->sinal == 0) || (n1->sinal == 0 && n2->sinal == 1)){
					soma(n1, n2, stack);
					return;
				}else if(n1->sinal ==1 && n2->sinal ==1){
					subtrai(n2,n1,stack);
					n2->sinal = 0;
					return;
				}else{
					subtrai(n2,n1,stack);
					n2->sinal = 1;
					return;
				}
			}
			p = p->prox;
			q = q->prox;
		}
	}else{
		subtrai(n1,n2,stack);
	}
}

void subtrai(numero *n1, numero *n2, pilha *stack){
	numerao *p, *q;
	int aux;
	
	p = n1->cabeca->prox;
	q = n2->cabeca->prox;
	
	while(p != NULL && q != NULL){
		aux = p->dado - q->dado;
		
		if (aux < 0){
			p->dado += 10;
			p->prox->dado -=1;
		}

		p->dado = p->dado - q->dado;
		
		/*vai para o proximo elemento*/
		p = p->prox;
		q = q->prox;
	}
	push(stack, n1);
	liberaLista(n2->cabeca);
	free(n2);
}

void multiplica(numero *n1, numero *n2, pilha *stack){
	int i, j, carry = 0, cont =0;
	numero *resultado, *aux, *n;
	numerao *p, *q;
	
	resultado = malloc(sizeof(numero));
	if((n1->sinal == 1 && n2->sinal == 0) || (n1->sinal == 0 && n2->sinal == 1)){
		resultado->sinal = 1;
	}else{
		resultado->sinal  = 0;
	}

	resultado->cabeca = malloc(sizeof(numerao));
	resultado->cabeca->prox = NULL;
	resultado->cabeca->dado = 0;
	resultado->tamanho = 1;	
	insereLista(0, resultado->cabeca);
	push(stack, resultado);
	 
	printf("lista antes de fazer a multiplica:");
	imprimePilha(stack);
	
	aux = malloc(sizeof(numero));
	aux->cabeca = malloc(sizeof(numerao));
	aux->cabeca->prox = NULL;	
	aux->tamanho = 0;
	
	for(p= n1->cabeca->prox; p != NULL; p = p->prox){
		carry = 0;
		for(j=0; j<cont; j++){
			insereLista(0, aux->cabeca);
			aux->tamanho++;
		}
		
		for(q= n2->cabeca->prox; q != NULL; q= q->prox){
			i = (q->dado) * (p->dado) + carry;
			carry = 0;
			if(i>=10){
				carry = i / 10;
				i %= 10;
			}
			insereLista(i, aux->cabeca);
			aux->tamanho++;
		}
		
		soma(pop(stack), aux, stack);
		
		liberaLista(aux->cabeca);
		aux->cabeca = malloc(sizeof(numerao));
		aux->cabeca->prox = NULL;	
		cont ++;
	}

	insereLista(carry, (retornaTopo(stack))->cabeca);
}
numero *copiaLista(numero *n1){
	numero 	*copia;
	numerao *aux, *novo;
	
	copia = malloc(sizeof(numero));
	copia->tamanho = n1->tamanho;
	
	aux= n1->cabeca;
	
	while(aux != NULL){
		insereLista(aux->dado, novo);
		aux = aux->prox;
	}
	copia->cabeca = novo;
	
	return copia;
}
void liberaLista(numerao *p){
	if(p != NULL){
		liberaLista(p->prox);
		free(p);
	}
}

void criaPilha(pilha *p){
	p->topo = -1;
	p->tam = 10;
	p->elem = (numero **)malloc (sizeof(numero *) * 10); //esse negocio tem que ser dinamico e dar realloc com o tempo	
}

int pilhaVazia(pilha *p){
	if(p->topo == -1)	return 1; //vazia
	else return 0; //nao vazia
}

int pilhaCheia(pilha *p){
	if(p->topo == p->tam -1) return 1; //esta cheia
	else return 0; //nao esta cheia
}

void push(pilha *p, numero *n){
	p->topo ++;
	p->elem[p->topo] = n;
}

numero *pop(pilha *p){
	numero *aux;
	aux = p->elem[p->topo];
	p->topo --;
	return aux;
}

void imprimePilha(pilha *p){
	int i;
	for(i=p->topo; i>=0; i--){
		imprimeLista(p->elem[i]);
	}
	printf("\n");
}

numero *retornaTopo(pilha *p){
	return p->elem[p->topo];
}
