#include <stdlib.h>
#include <stdio.h>

struct TNoABP
{
  int chave, fb;
  struct TNoABP  *esq, *dir;
};

typedef struct TNoABP TNoABP;

int altura(TNoABP *r) 
{
  if (r == NULL)
  return 0;
  int hesq = altura(r->esq);  
  int hdir = altura(r->dir);
  return hesq > hdir ? hesq + 1 : hdir + 1;
}

void atualizarfb(TNoABP *raiz)
{
  if (raiz != NULL)
  {
    atualizarfb(raiz->esq);
    raiz->fb=altura(raiz->dir)-altura(raiz->esq);
    atualizarfb(raiz->dir);
  }
}

void rotacaoDireita(TNoABP **r)
{
	TNoABP *aux, *q;
	q = (*r)->esq;
	aux = q->dir;
	q->dir=(*r);
	(*r)->esq=aux;
	(*r)=q;
}

void rotacaoEsquerda(TNoABP **r)
{
	TNoABP *aux, *q;
	q = (*r)->dir;
	aux = q->esq;
	q->esq=(*r);
	(*r)->dir=aux;
	(*r)=q;
}

TNoABP *insereNoABP(TNoABP **r, int k)
{
  if (*r == NULL) //arvore vazia
	{
		(*r) = (TNoABP*)malloc(sizeof(TNoABP));
		(*r)->chave = k;
		(*r)->dir = NULL;
		(*r)->esq = NULL;
	}
	else if (k > (*r)->chave)
	{
		return insereNoABP(&((*r)->dir), k);
	}
	else{
		return insereNoABP(&((*r)->esq),k);
	}
  return 0;
}

void verificarAVL(TNoABP **r)
{
	if (*r != NULL){
		if ((*r)->fb == 2)
		{
			if ((*r)->dir != NULL)
			{
				if ((*r)->dir->fb == 1)
				{
					rotacaoEsquerda(r);
					return;
				}
				if ((*r)->dir->fb == -1)
				{
					//caso 2
					rotacaoDireita(&((*r)->dir));
					rotacaoEsquerda(r);
					return;
				}
			}
			if ((*r)->esq != NULL)
			{
				if ((*r)->esq->fb == 1)
				{
					rotacaoEsquerda(r);
					return;
				}
				if ((*r)->esq->fb == -1)
				{
					//caso 2
					rotacaoDireita(&((*r)->esq));
					rotacaoEsquerda(r);
					return;
				}
			}
		}
		if ((*r)->fb == -2)
		{
			if ((*r)->dir != NULL)
			{
				if ((*r)->dir->fb == -1)
				{
					rotacaoDireita(r);
					return;
				}
				if ((*r)->dir->fb == 1)
				{
					//caso 2
					rotacaoEsquerda(&((*r)->dir));
					rotacaoDireita(r);
					return;
				}
			}
			if ((*r)->esq != NULL)
			{
				if ((*r)->esq->fb == -1)
				{
					rotacaoDireita(r);
					return;
				}
				if ((*r)->esq->fb == 1)
				{
					//caso 2
					rotacaoEsquerda(&((*r)->esq));
					rotacaoDireita(r);
					return;
				}
			}
		}
		verificarAVL(&((*r)->dir));
		verificarAVL(&((*r)->esq));
	}
}

int buscaNoABP(TNoABP *r, int k)
{
	int fb;
	if (r == NULL)
		return 0;
	if (r->chave == k)
	{
		printf("FB eh igual a: %d\n",fb=altura(r->dir)-altura(r->esq));
		return 1;
	}
	if (r->chave < k)
		return buscaNoABP(r->dir, k);
	else
		return buscaNoABP(r->esq, k);
   return -1;
}

TNoABP** buscaPP(TNoABP **r, int k)
{
	if (*r == NULL)
		return NULL;
	if ((*r)->chave == k)
		return r;
	if ((*r)->chave > k)
	return 
	buscaPP(&((*r)->esq),k);
	return NULL;
}

TNoABP* ppMenor(TNoABP **r)
{
	if((*r)->esq != NULL) 
       return ppMenor(&(*r)->esq);
    else{
       TNoABP *aux = *r;
       if((*r)->dir != NULL)
          *r = (*r)->dir;
       else
          *r = NULL;
       return aux;
       }
}

void *removeNoABP(TNoABP **raiz, int k)
{
	if((*raiz) == NULL) 
	return NULL;
    if(k < (*raiz)->chave) 
	removeNoABP(&(*raiz)->esq, k);    
    if(k > (*raiz)->chave) 
	removeNoABP(&(*raiz)->dir, k);
    else if(k == (*raiz)->chave)
	{

		TNoABP **pp = buscaPP(raiz, k);
		TNoABP *filho = NULL;
	
		//caso1
		if ((*pp)->dir == NULL &&
			(*pp)->esq == NULL)
		{
			free(*pp);
			*pp = NULL;
			return NULL;
		}
	
		//caso 2
		if( ( (*pp)->dir == NULL) !=
 		( (*pp)->esq == NULL) )
 		{
 			filho =((*pp)->esq == NULL) ?
 			(*pp)->dir : (*pp)->esq;
 			free(*pp);
 			*pp = filho; 
			return NULL;
		}

		//caso 3
		if ((*pp)->esq && (*pp)->dir)
		{
			TNoABP *pps=ppMenor(&((*raiz)->dir));
  	    	pps->esq = (*raiz)->esq;
  	    	pps->dir = (*raiz)->dir;
  	    	(*raiz)->esq = (*raiz)->dir = NULL;
  	    	free((*raiz));
			*raiz = pps;
			pps = NULL;
		}
	}
	return NULL;
}

void emOrdem(TNoABP *raiz)
{
  if (raiz != NULL)
  {
    emOrdem(raiz->esq);
    printf("%d\n", raiz->chave);
    emOrdem(raiz->dir);
  }
}

void emOrdemfb(TNoABP *raiz)
{
  if (raiz != NULL)
  {
    emOrdemfb(raiz->esq);
    printf("chave: %d fb:%d\n", raiz->chave, raiz->fb);
    emOrdemfb(raiz->dir);
  }
}

void posOrdem(TNoABP *raiz)
{
	if (raiz != NULL)
  {
    posOrdem(raiz->esq);
    posOrdem(raiz->dir);
    printf("%d\n", raiz->chave);
  }
}

void preOrdem(TNoABP *raiz)
{
	if (raiz != NULL)
  {
  	printf("%d\n", raiz->chave);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
  }
}

int main()
{
  TNoABP *raiz = NULL; //arvore nascendo vazia
  int N, chave, i;
 
  //populando a arvore
  scanf("%d", &N); //numero de chaves a inserir
  for(i=0; i<N; ++i)
  {
    scanf("%d", &chave);    
    insereNoABP(&raiz, chave);
	atualizarfb(raiz);
	verificarAVL(&raiz);
	atualizarfb(raiz);
  }
  
  //buscando na arvore
  scanf("%d", &N); //numero de chaves a buscar
  for(i=0; i<N; ++i)
  {
    scanf("%d", &chave);    
    printf("%d\n", buscaNoABP(raiz, chave));
  }

  //removendo na arvore
  scanf("%d", &N);//numero de nos a remover
  for(i=0; i<N; ++i)
  {
    scanf("%d", &chave);    
    removeNoABP(&raiz, chave);
  }

  printf("EM ORDEM:\n");
  emOrdem(raiz);
  printf("POS ORDEM:\n");
  posOrdem(raiz);
  printf("PRE ORDEM:\n");
  preOrdem(raiz);
  printf("FBS EM ORDEM:\n");
  emOrdemfb(raiz);
  return 0;
}
