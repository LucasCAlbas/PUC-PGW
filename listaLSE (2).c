#include<stdio.h>
#include<stdlib.h>

typedef struct no {
    int dado;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int tam;
} ListaLSE;

// Funções de manipulação
void cria(ListaLSE *l);
int insere(ListaLSE *l, int dado);
int insereOrdenado(ListaLSE *l, int dado);
int retira(ListaLSE *l, int dado);

// Funções de visualização
int estaVazia(ListaLSE l);
int getInicio(ListaLSE l);
int getFim(ListaLSE l);
int getTamanho(ListaLSE l);
void mostra(ListaLSE l);

int main() {
    ListaLSE l;
    int dado, sucesso, opcao;

    cria(&l);

    sucesso = insereOrdenado(&l, 400);
    sucesso = insereOrdenado(&l, 250);
    sucesso = insereOrdenado(&l, 666);
    sucesso = insereOrdenado(&l, 5000);
    sucesso = insereOrdenado(&l, 10);

    if (!estaVazia(l)) {
        mostra(l);
    }

    opcao = 1;
    while (opcao == 1) {
        printf("\n-------------------------------------------------\n");
        printf("Qual dado deseja remover? ");
        scanf("%d", &dado);

        sucesso = retira(&l, dado);
        if (!sucesso)
            printf("FALHA EM REMOVER: %d\n\n", dado);

        mostra(l);

        printf("\nDeseja remover mais algum elemento? \n1 - sim \n2 - nao\n");
        scanf("%d", &opcao);
    }

    while (!estaVazia(l)) {
        sucesso = retira(&l, getInicio(l));
    }

    return 0;
}

void cria(ListaLSE *l) {
    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;
}

int insere(ListaLSE *l, int dado) {
    No *aux = (No *) malloc(sizeof(No));
    if (aux == NULL)
        return 0;

    aux->dado = dado;
    aux->prox = NULL;

    l->tam++;

    if (l->inicio == NULL) {
        l->inicio = aux;
        l->fim = aux;
    } else {
        l->fim->prox = aux;
        l->fim = aux;
    }

    return 1;
}

int insereOrdenado(ListaLSE *l, int dado) {
    No *aux = (No *) malloc(sizeof(No));
    if (aux == NULL)
        return 0;

    aux->dado = dado;
    l->tam++;

    if (l->inicio == NULL) {
        aux->prox = NULL;
        l->inicio = aux;
        l->fim = aux;
    } else if (dado < l->inicio->dado) {
        aux->prox = l->inicio;
        l->inicio = aux;
    } else if (dado > l->fim->dado) {
        aux->prox = NULL;
        l->fim->prox = aux;
        l->fim = aux;
    } else {
        No *anterior = l->inicio;
        No *atual = anterior->prox;

        while (dado > atual->dado) {
            anterior = atual;
            atual = atual->prox;
        }

        aux->prox = atual;
        anterior->prox = aux;
    }

    return 1;
}

int retira(ListaLSE *l, int dado) {
    No *aux;
    No *auxFim;

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
        free(aux);
        l->tam--;

        return 1;
    }

    if (dado == l->fim->dado) {
        aux = l->inicio;
        auxFim = l->inicio->prox;

        while (auxFim != l->fim) {
            aux = aux->prox;
            auxFim = auxFim->prox;
        }

        aux->prox = NULL;
        l->fim = aux;

        free(auxFim);
        l->tam--;

        return 1;
    }

    auxFim = l->inicio->prox;
    aux = l->inicio;

    while ((dado != auxFim->dado) && (auxFim != l->fim)) {
        auxFim = auxFim->prox;
        aux = aux->prox;
    }

    if (auxFim == l->fim) {
        printf("O elemento %d nao esta na lista.\n", dado);
        return 0;
    }

    aux->prox = auxFim->prox;
    free(auxFim);
    l->tam--;

    return 1;
}

int estaVazia(ListaLSE l) {
    return l.inicio == NULL;
}

int getInicio(ListaLSE l) {
    return l.inicio->dado;
}

int getFim(ListaLSE l) {
    return l.fim->dado;
}

int getTamanho(ListaLSE l) {
    return l.tam;
}

void mostra(ListaLSE l) {
    No *aux;

    if (l.inicio == NULL) {
        printf("Lista vazia!\n");
    } else {
        printf("\nExibindo lista do inicio ao fim:\n\n");
        aux = l.inicio;
        while (aux != NULL) {
            printf("Dado: %d\n", aux->dado);
            aux = aux->prox;
        }
    }
}
