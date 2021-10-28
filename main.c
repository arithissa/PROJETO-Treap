#include "treap.h"
#include <string.h>

int main(){
  int n, x;
  char op[10];
  arvore *treap = criar();	//cria a árvore treap 

  scanf("%d", &n);	//lê a quantidade de casos 

  for(int i = 0; i < n; i++){
    scanf(" %s", op);	//lê a operação requerida pelo usuário
	
    if(strcmp(op, "insercao") == 0){
      int chave, prioridade;
      scanf("%d %d", &chave, &prioridade);
      Insere(treap, chave, prioridade);
    }
    else if(strcmp(op, "remocao") == 0){
      int chave, prioridade;
      scanf("%d %d", &chave, &prioridade);
      Remove(treap, chave);
    }
    else if(strcmp(op, "buscar") == 0){
      int chave;
      scanf("%d", &chave);
      if(buscar(treap->raiz, chave) == 1)
        printf("1\n");
      else
        printf("0\n");
    } else{
        char modo[10];
        scanf(" %s", modo);

        if(strcmp(modo, "ordem") == 0){
          Em_Ordem(treap->raiz);
          printf("\n");
        }
        else if(strcmp(modo, "posordem") == 0){
          Pos_Ordem(treap->raiz);
          printf("\n");
        }
        else if(strcmp(modo, "preordem") == 0){
          Pre_Ordem(treap->raiz);
          printf("\n");
        }
        else{
		  fila *f = CriarFila();	//cria uma fila f
          largura(treap->raiz, f);
          printf("\n");
		  destruir(f);	//destrói a fila criada após a impressão
        }
    }

  }

  liberar(treap->raiz);	//libera o espaço de memória alocado para a árvore treap 

  return 0;
}
