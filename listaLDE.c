#include<stdio.h>
#include<stdlib.h>

typedef struct no {
    int dado;
    struct no *ant;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int tam;

} ListaLDE;

// Funções de manipulação
void cria(ListaLDE *l);
int insere(ListaLDE *l, int dado);
int insereOrdenado(ListaLDE *l, int dado);
int retira(ListaLDE *l, int dado);

// Funções de visualização
int estaVazia(ListaLDE l);
int getInicio(ListaLDE l);
int getFim(ListaLDE l);
int getTamanho(ListaLDE l);
void mostra(ListaLDE l, int sentido);

int main() {
    ListaLDE l;
    int dado, sucesso, opcao;

    cria(&l);

    sucesso = insereOrdenado(&l, 400);
    sucesso = insereOrdenado(&l, 250);
    sucesso = insereOrdenado(&l, 666);
    sucesso = insereOrdenado(&l, 5000);
    sucesso = insereOrdenado(&l, 10);

  if(!estaVazia(l)){ //exibindo a lista
        printf("\n-------------------------------------------------\n");
        printf("Deseja ver os dados a partir de onde?\n1 - inicio \n2 - fim\n");
        scanf("%d", &opcao);
        mostra(l, opcao);}

    opcao = 1;
    while (opcao == 1) {
        printf("\n-------------------------------------------------\n");
        printf("Qual dado deseja remover? ");
        scanf("%d", &dado);

        sucesso = retira(&l, dado);
        if (!sucesso)
            printf("FALHA EM REMOVER: %d\n\n", dado);

        mostra(l, 1);

        printf("\nDeseja remover mais algum elemento? \n1 - sim \n2 - nao\n");
        scanf("%d", &opcao);
    }

    while (!estaVazia(l)) {
        sucesso = retira(&l, getInicio(l));
    }

    return 0;
}

void cria(ListaLDE *l) {
    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;
}

int insere(ListaLDE *l, int dado) {
    No *aux = (No *) malloc(sizeof(No));
    if (aux == NULL)
        return 0;

    aux->dado = dado;
    aux->ant = NULL;
    aux->prox = NULL;

    l->tam++;

    if (l->inicio == NULL) {
        l->inicio = aux;
        l->fim = aux;
    }

    else {
        aux->ant = l->fim;
        l->fim->prox = aux;
        l->fim = aux;
        l->inicio->ant = NULL;
    }

    return 1;
}

int insereOrdenado(ListaLDE *l, int dado) {
    No *aux = (No *) malloc(sizeof(No));
    if (aux == NULL)
        return 0;

    aux->dado = dado;
    l->tam++;

    if (l->inicio == NULL) {

        aux->ant = NULL;
        aux->prox = NULL;
        l->inicio = aux;
        l->fim = aux;

    } else if (dado < l->inicio->dado) {

        aux->ant = NULL;
        aux->prox = l->inicio;
        l->inicio->ant = aux;
        l->inicio = aux;
        l->fim->prox = NULL;

    } else if (dado > l->fim->dado) {
        aux->ant = l->fim;
        aux->prox = NULL;
        l->fim->prox = aux;
        l->fim = aux;
        l->inicio->ant = NULL;

    } else {
        No *anterior = l->inicio;
        No *atual = anterior->prox;

        while (dado > atual->dado) {
            anterior = atual;
            atual = atual->prox;
        }

        aux->prox = atual;
        anterior->prox = aux;
        anterior->prox = aux; // prox do anterior aponta para o novo no
        atual->ant = aux;
    }

    return 1;
}

int retira(ListaLDE *l, int dado) {
    No *aux;

    if (l->inicio == NULL) {
        printf("Lista vazia\n");
        return 0;
    }

    if ((dado == l->inicio->dado) && (l->inicio == l->fim)) {
        aux = l->inicio;
        l->inicio = NULL;
        l->fim = NULL;
        free(aux);
        l->tam--;

        return 1;
    }

    if (dado == l->inicio->dado) {
        aux = l->inicio;
        l->inicio = aux->prox;
        l->inicio->ant = NULL;
        l->fim->prox = NULL;
        free(aux);
        l->tam--;

        return 1;
    }

  if(dado == l->fim->dado) {
        aux = l->fim; // aux aponta para o no que vou remover
        l->fim = aux->ant; //fim aponta para o novo fim (penultimo elemento)
        l->fim->prox = NULL; // o proximo do novo fim aponta para o inicio
        l->inicio->ant = NULL; // o anterior do inicio aponta para o novo fim
        free(aux); //libero a memoria
        l->tam--;

        return 1;
    }

    /* 4o caso: removendo um elemento no meio */
    aux = l->inicio->prox; // aux aponta para o segundo elemento

    //percorro a lista ate achar o elemento, ou chegar no fim
    while((dado != aux->dado) && (aux != l->fim))
        aux = aux->prox;

    if(aux == l->fim){ // se cheguei ao fim, nao encontrei o elemento
        printf("O elemento %d nao esta na lista.\n", dado);
        return 0;
    }

    //se encontrei o elemento, removo ele
    aux->prox->ant = aux->ant; // o anterior do proximo a aux aponta para o elemento anterior a aux
    aux->ant->prox = aux->prox; // o proximo do anterior a aux aponta para o proximo elemento em relacao a aux
    free(aux); //libero a memoria
    l->tam--;

    return 1;
}

int estaVazia(ListaLDE l) {
    return l.inicio == NULL;
}

int getInicio(ListaLDE l) {
    return l.inicio->dado;
}

int getFim(ListaLDE l) {
    return l.fim->dado;
}

int getTamanho(ListaLDE l) {
    return l.tam;
}

void mostra(ListaLDE l, int sentido){

    No *aux;

    if(l.inicio == NULL) // lista vazia, nao mostra nada
            printf("Lista vazia!\n");

    else { // lista possui elementos, mostra dependendo do sentido

        if(sentido == 1){ // percorrendo do inicio ao fim

            printf("\nExibindo lista do inicio ao fim:\n\n");
            aux = l.inicio;
            while(aux != NULL){
                printf("Dado: %d\n", aux->dado);
                aux = aux->prox;
            }
        }

        else { // percorrendo do fim ao inicio

            printf("\nExibindo lista do fim ao inicio:\n\n");
            aux = l.fim;
           while(aux != NULL){
                printf("Dado: %d\n", aux->dado);
                aux = aux->ant;
            }
        }
    }
}
