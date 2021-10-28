#include <stdio.h>
#include <stdlib.h>
#define max 100

typedef int elem;
typedef struct NoTreap no;
typedef struct ArvoreTreap arvore;
typedef struct fila fila;

struct ArvoreTreap{
    no *raiz;
};

struct NoTreap{
    no *esq, *dir;
    elem info;
    int prioridade;
};

struct fila{
	int inicio, fim, tam;
	elem itens[max];
	int pri[max];
};

arvore *criar();	//aloca memória para a treap
fila *CriarFila();	//aloca memória para uma fila
int buscar(no *raiz, elem x);	//busca um elemento x
void Insere(arvore *treap, elem x, int p);	//inserção de um elemento x
void Remove(arvore *treap, elem x);	//remoção de um elemento x
void Pos_Ordem(no *raiz);	//impressão em Pós-Ordem
void Pre_Ordem(no *raiz);	//impressão em Pré-Ordem
void Em_Ordem(no *raiz);	//impressão em Ordem 
void largura(no *raiz, fila *f);	//impressão por largura 
void liberar(no *raiz);	//libera a memória alocada para a treap
void destruir(fila *f);	//libera a memória alocada para a fila 