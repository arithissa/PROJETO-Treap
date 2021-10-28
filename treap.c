#include "treap.h"

arvore *criar(){    //aloca memória para a treap 
    arvore *treap = (arvore *) malloc(sizeof(arvore));
    treap->raiz = NULL;

    return treap;    
}

fila *CriarFila(){	//aloca memória para uma fila  
	fila *f = (fila *) malloc(sizeof(fila));
	if(f == NULL)
		return NULL;  //erro
	f->inicio = 0;
	f->fim = 0;
    f->tam = 0;

	return f;
}

int EstaVazia(arvore *a){   //verifica se está vazia
    if(a == NULL)
        return 1; //erro
    if(a->raiz == NULL)
        return -1; //vazia
        
    return 0;
}

no *busca(no *raiz, elem x){    //faz a busca de um elemento x na treap 
    if(raiz == NULL)	//erro
        return NULL;
    else if(raiz->info == x)	//se x estiver na raiz, retorna a raiz
        return raiz;
    else if(x < raiz->info)		//se não, percorre a treap de forma recursiva em busca do elemento 
      return busca(raiz->esq, x);
    else
      return busca(raiz->dir, x);
}

int buscar(no *raiz, elem x){	//função chamada pelo usuário que executa a função de busca
  no *p = busca(raiz, x);
  if(p == NULL)
    return 0; //elemento não encontrado
  else
    return 1; //elemento encontrado
}

no *BuscaPai(no *raiz, elem x){ //faz a busca do pai de determinado elemento
     if(raiz == NULL)	//erro 
        return NULL;
        
    if(raiz->esq != NULL && raiz->esq->info == x)	//se o elemento x for igual a um dos filhos da raiz, então o pai é a raiz 
        return raiz;
    if(raiz->dir != NULL && raiz->dir->info == x)
        return raiz;
        
    no *p = BuscaPai(raiz->esq, x);	//se não, faz a busca recursivamente
    if(p == NULL)
        p = BuscaPai(raiz->dir, x);
        
    return p;
}

no *RotacionarEsq(no *p){ //faz uma rotação à esquerda
    no *no = p->dir;
    p->dir = no->esq;
    no->esq = p;
    
    return no;
}

no *RotacionarDir(no *p){ //faz uma rotação à direita
    no *no = p->esq;
    p->esq = no->dir;
    no->dir = p;
    
    return no;
}

no *Inserir(no *raiz, elem x, int p){	//insere um novo nó na treap
  if(raiz == NULL){		//aloca um novo nó 
    no *NovoNo = (no *) malloc(sizeof(no));
    if(NovoNo == NULL)
      return 0; //erro
    NovoNo->info = x;
    NovoNo->prioridade = p;
    NovoNo->esq = NULL;
    NovoNo->dir = NULL;

    return NovoNo;	//retorna o novo nó criado
  } 
  
  if(x < raiz->info){	//faz as verificações para as rotações
      raiz->esq = Inserir(raiz->esq, x, p);	//se x for menor que o elemento da raiz, insere à esquerda
      if(raiz->esq->prioridade > raiz->prioridade && raiz->esq != NULL)	//se a prioridade for maior que a da raiz, rotaciona para a direita
        raiz = RotacionarDir(raiz);
  } else if(x > raiz->info){	//se x for maior que o elemento da raiz, insere à direita
      raiz->dir = Inserir(raiz->dir, x, p);
      if(raiz->dir->prioridade > raiz->prioridade && raiz->dir != NULL)	//se a prioridade for maior que a da raiz, rotaciona para a esquerda
        raiz = RotacionarEsq(raiz);
  } else
      printf("Elemento ja existente\n");

  return raiz;
}

void Insere(arvore *treap, elem x, int p){	//função chamada pelo usuário que executa a função de inserção
  treap->raiz = Inserir(treap->raiz, x, p);

  return;
}

int InsereFila(fila *f, elem *x, int p){	//faz uma inserção na fila
	if(f->tam == max)
		return 1; // fila cheia

	f->itens[f->fim] = *x;
	f->pri[f->fim] = p;
	f->fim = (f->fim + 1);
	f->tam++;
	
	return 0; // sucesso
}

no *Remover(no *raiz, elem x){	//faz a remoção de um elemento na treap, com rotações apenas para a esquerda 
  no *p = busca(raiz, x);	//busca o elemento a ser removido na treap
  if(p == NULL)	//se não for encontrado:
    printf("Chave nao localizada\n");
  
  else if(raiz != NULL){	//se o elemento existe na treap:
    if(x < raiz->info)	//se for menor que o elemento da raiz, percorre o lado esquerdo
      raiz->esq = Remover(raiz->esq, x);
    else if(x > raiz->info)	//se não, percorre o lado direito
      raiz->dir = Remover(raiz->dir, x);
    else if(raiz->esq == NULL){
      no *p = raiz->dir;
      raiz = p;
    }
    else if(raiz->dir == NULL){
      no *p = raiz->esq;
      raiz = p;
    }
    else if(raiz->esq->prioridade < raiz->dir->prioridade){	//se a prioridade do elemento esquerdo for menor que a do direito 
      raiz = RotacionarEsq(raiz);
      raiz->esq = Remover(raiz->esq, x);
    }
    else{
      raiz = RotacionarEsq(raiz);
      raiz->esq = Remover(raiz->esq, x);
    }
  }

  return raiz;
}

void Remove(arvore *treap, elem x){	//função chamada pelo usuário que executa a função de remoção 
  treap->raiz = Remover(treap->raiz, x);
  
  return;
}

int RemoveFila(fila *f, elem *x){	//faz uma remoção na fila 
	if(f->tam == 0)
		return 1; //pilha vazia
		
	*x = f->itens[f->inicio];
	f->inicio = (f->inicio + 1);
	f->tam--;
	
	return 0; // sucesso		
}

void Pre_Ordem(no *raiz){ //impressão em pré ordem
  if(raiz != NULL){
        printf("(");
        printf("%d, ", raiz->info);
        printf("%d) ", raiz->prioridade);
        Pre_Ordem(raiz->esq);
        Pre_Ordem(raiz->dir);
    }
        
    return;
}

void Em_Ordem(no *raiz){  //impressão em ordem
  if(raiz != NULL){
    Em_Ordem(raiz->esq);
    printf("(");
    printf("%d, ", raiz->info);
    printf("%d) ", raiz->prioridade);
    Em_Ordem(raiz->dir);
  }
        
    return;
}

void Pos_Ordem(no *raiz){   //impressão em pós ordem
    if(raiz != NULL){
        Pos_Ordem(raiz->esq);
        Pos_Ordem(raiz->dir);
        printf("(");
        printf("%d, ", raiz->info);
        printf("%d) ", raiz->prioridade);
    }
        
    return;
}

void calcLargura(fila *f, no *raiz){	//insere os elementos na fila em ordem de largura 
	int i = 0, j = 0, k = 0;
	no *q = raiz;

	InsereFila(f, &raiz->info, raiz->prioridade);

	while(1){	//entra em um loop "infinito"
    q = busca(raiz, f->itens[i]);	//faz uma busca do primeiro elemento da fila na treap 
    if(q != NULL){
		if(q->esq != NULL){
			j++; 
			InsereFila(f, &q->esq->info, q->esq->prioridade);	//insere o elemento da esquerda na fila 
		}       
		if(q->dir != NULL){
			j++;
			InsereFila(f, &q->dir->info, q->dir->prioridade);	//insere o elemento da direita na fila 
		}
		if(q->dir == NULL && q->esq == NULL){
			k = j;
		} i++;
    } else //se q == NULL
      break;
	}

  return;
}

void largura(no *raiz, fila *f){	//faz a impressão em ordem de largura
  if(raiz != NULL){
      int i = 0;
      calcLargura(f, raiz);

      while(i != f->fim){
        printf("(%d, ", f->itens[i]);
        printf("%d) ", f->pri[i]);
        RemoveFila(f, &f->itens[i]);
        i++;
      }
    }

  return;
}

void destruir(fila *f){ //libera a memória alocada para a fila
	if(f != NULL)
		free(f);
}

void liberar(no *raiz){   //libera a memória alocada para a treap 
    if(raiz != NULL){
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}