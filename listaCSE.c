#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int dado;
    struct no *prox;
} No;

typedef struct
{
    No *inicio;
    No *fim;
    int tam;
} ListaCSE;

// Funções de manipulação
void cria(ListaCSE *l);
int insere(ListaCSE *l, int dado);
int insereOrdenado(ListaCSE *l, int dado);
int retira(ListaCSE *l, int dado);

// Funções de visualização
int estaVazia(ListaCSE l);
int getInicio(ListaCSE l);
int getFim(ListaCSE l);
int getTamanho(ListaCSE l);
void mostra(ListaCSE l);

int main()
{
    ListaCSE l;
    int dado, sucesso, opcao;

    cria(&l);

    sucesso = insereOrdenado(&l, 400);
    sucesso = insereOrdenado(&l, 250);
    sucesso = insereOrdenado(&l, 666);
    sucesso = insereOrdenado(&l, 5000);
    sucesso = insereOrdenado(&l, 10);

    if (!estaVazia(l))
    {
        mostra(l);
    }

    opcao = 1;
    while (opcao == 1)
    {
        printf("\n-------------------------------------------------\n");
        printf("Qual dado deseja remover? ");
        scanf("%d", &dado);

        sucesso = retira(&l, dado);
        if (!sucesso)
            printf("FALHA EM REMOVER: %d\n\n", dado);

        mostra(l);

        printf("\nDeseja remover mais algum elemento? \n1 - Sim \n2 - Nao\n");
        scanf("%d", &opcao);
    }

    while (!estaVazia(l))
    {
        sucesso = retira(&l, getInicio(l));
    }

    return 0;
}

void cria(ListaCSE *l)
{
    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;
}

int insere(ListaCSE *l, int dado)
{
    No *aux = (No *)malloc(sizeof(No));
    if (aux == NULL)
        return 0;

    aux->dado = dado;
    l->tam++;

    if (l->inicio == NULL)
    {
        l->inicio = aux;
        l->fim = aux;
        aux->prox = l->inicio;

        return 1;
    }

    aux->prox = l->inicio;
    l->fim->prox = aux;
    l->fim = aux;

    return 1;
}

int insereOrdenado(ListaCSE *l, int dado)
{
    No *aux = (No *)malloc(sizeof(No));
    if (aux == NULL)
        return 0;

    aux->dado = dado;
    l->tam++;

    if (l->inicio == NULL)
    {
        l->inicio = aux;
        l->fim = aux;
        aux->prox = l->inicio;
    }
    else if (dado < l->inicio->dado)
    {
        aux->prox = l->inicio;
        l->inicio = aux;
        l->fim->prox = l->inicio;
    }
    else if (dado > l->fim->dado)
    {
        aux->prox = l->inicio;
        l->fim->prox = aux;
        l->fim = aux;
    }
    else
    {
        No *anterior = l->inicio;
        No *atual = anterior->prox;

        while (dado > atual->dado)
        {
            anterior = atual;
            atual = atual->prox;
        }

        aux->prox = atual;
        anterior->prox = aux;
    }

    return 1;
}

int retira(ListaCSE *l, int dado)
{
    No *aux;
    No *auxFim;

    if (l->inicio == NULL)
    {
        printf("Lista vazia\n");
        return 0;
    }

    if ((dado == l->inicio->dado) && (l->inicio == l->fim))
    {
        aux = l->inicio;
        l->inicio = NULL;
        l->fim = NULL;
        free(aux);
        l->tam--;

        return 1;
    }

    if (dado == l->inicio->dado)
    {
        aux = l->inicio;
        l->inicio = aux->prox;
        l->fim->prox = l->inicio;
        free(aux);
        l->tam--;

        return 1;
    }

    if (dado == l->fim->dado)
    {
        aux = l->fim;
        auxFim = l->inicio;

        while (auxFim->prox != l->fim)
        {
            auxFim = auxFim->prox;
        }

        auxFim->prox = l->inicio;
        l->fim = auxFim;

        free(aux);
        l->tam--;

        return 1;
    }

    auxFim = l->inicio->prox;
    aux = l->inicio;

    while ((dado != auxFim->dado) && (auxFim != l->fim))
    {
        auxFim = auxFim->prox;
        aux = aux->prox;
    }

    if (auxFim == l->fim)
    {
        printf("O elemento %d nao esta na lista.\n", dado);
        return 0;
    }

    aux->prox = auxFim->prox;
    free(auxFim);
    l->tam--;

    return 1;
}

int estaVazia(ListaCSE l)
{
    return l.inicio == NULL;
}

int getInicio(ListaCSE l)
{
    return l.inicio->dado;
}

int getFim(ListaCSE l)
{
    return l.fim->dado;
}

int getTamanho(ListaCSE l)
{
    return l.tam;
}

void mostra(ListaCSE l)
{
    No *aux;

    if (l.inicio == NULL)
    {
        printf("Lista vazia!\n");
    }
    else
    {
        printf("\nExibindo lista do inicio ao fim:\n\n");
        aux = l.inicio;
        do
        {
            printf("Dado: %d\n", aux->dado);
            aux = aux->prox;
        } while (aux != l.inicio);
    }
}