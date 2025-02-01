#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "avl.h"

struct no{
    int chave;
    int altura;
    struct no* esq;
    struct no* dir; 
};

ArvAVL* criarArvore(){
    ArvAVL* raiz = (ArvAVL*) malloc (sizeof(ArvAVL));

    if(!raiz){
        printf("Erro de alocacao da arvore\n");
        exit(1);
    }

    *raiz = NULL;

    return raiz;
}

void liberaArvore(ArvAVL* raiz){
    if(*raiz == NULL)
        free(raiz);

    liberaSubarvore(*raiz);
    free(raiz);
}

int liberaSubarvore(No* no){
    if(no == NULL)
        return 0;
    liberaSubarvore(no->esq);
    liberaSubarvore(no->dir);
    free(no);

    return 1;
}

int consultarNo(ArvAVL* raiz, int chave){
    if((*raiz) == NULL)
        return 0;

    if(chave > (*raiz)->chave)
        consultarNo(&((*raiz)->dir), chave);
    else if(chave < (*raiz)->chave)
        consultarNo(&((*raiz)->esq), chave);
    else{
        printf("Elemento encontrado!\n");
        return 1;
    }
    return 0;
}

int estaVazia(ArvAVL* raiz){
    if(!(*raiz))
        return 1;
    else 
        return 0;
}

int alturaArvore(ArvAVL* raiz){
    if(!(*raiz))
        return 0;

    int alt_esq = alturaArvore(&((*raiz)->esq));
    int alt_dir = alturaArvore(&((*raiz)->dir));

    if(alt_esq > alt_dir)
        return alt_esq + 1;
    else   
        return alt_dir + 1;
}

int qntdNo(ArvAVL* raiz){
    if(!(*raiz))
        return 0;

    int cont_esq = qntdNo(&((*raiz)->esq));
    int cont_dir = qntdNo(&((*raiz)->dir));

    return cont_esq + cont_dir + 1;
}

int consultarNo(ArvAVL* raiz, int chave){
    if((*raiz) == NULL)
        return 0;

    if(chave > (*raiz)->chave)
        consultarNo(&((*raiz)->dir), chave);
    else if(chave < (*raiz)->chave)
        consultarNo(&((*raiz)->esq), chave);
    else{
        printf("Elemento encontrado!\n");
        return 1;
    }
    return 0;
}

void preOrdem(ArvAVL* raiz){
    if(!raiz)
        return;

    if(*raiz){
        printf("%d\n", (*raiz)->chave);
        preOrdem(&((*raiz)->esq));
        preOrdem(&((*raiz)->dir));
    }
}

void emOrdem(ArvAVL* raiz){
    if(!raiz)
        return;

    if(*raiz){
        emOrdem(&((*raiz)->esq));
        printf("%d\n", (*raiz)->chave);
        emOrdem(&((*raiz)->dir));
    }
}

void posOrdem(ArvAVL* raiz){
    if(!raiz)
        return;

    if(*raiz){
        posOrdem(&((*raiz)->esq));
        posOrdem(&((*raiz)->dir));
        printf("%d\n", (*raiz)->chave);
    }
}

int alturaNo(No* no){
    if(!no)
        return 0;

    return no->altura;
}

int fb(No* no){
    if(!no)
        return -1;
    return abs(alturaNo(no->esq) - alturaNo(no->dir));
}

int maior(int a, int b){
    if(a > b) 
        return a;
    else
        return b;
}

void rotacaoLL(ArvAVL* A){
    No* B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;

    (*A)->altura = maior(alturaNo((*A)->esq), alturaNo((*A)->dir)) + 1;
    B->altura = maior(alturaNo(B->esq), alturaNo(B->dir)) + 1;

    *A = B;
}

void rotacaoRR(ArvAVL* A){
    No* B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;

    (*A)->altura = maior(alturaNo((*A)->esq), alturaNo((*A)->dir)) + 1;
    B->altura = maior(alturaNo(B->esq), alturaNo(B->dir)) + 1;

    *A = B;
}

void rotacaoLR(ArvAVL* A){
    rotacaoRR(&((*A)->esq));
    rotacaoLL(A);
}

void rotacaoRL(ArvAVL* A){
    rotacaoLL(&((*A)->dir));
    rotacaoRR(A);
}

int inserirNo(ArvAVL* raiz, int chave){
    int res;
    if(!(*raiz)){
        No* novo = (No*) malloc (sizeof(No));
        if(!novo)
            return 0;

        novo->chave = chave;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;

        *raiz = novo;
        return 1;
    }

    No* atual = *raiz;
    if(chave < atual->chave){
        if(res = inserirNo(&(atual->esq), chave) == 1){
            if(fb(atual) >= 2){
                if(chave < atual->esq)
                    rotacaoLL(raiz);
                else
                    rotacaoLR(raiz);
            }
        }
    }
    else if(chave > atual->chave){
        if(res = inserirNo(&(atual->dir), chave) == 1){
            if(fb(atual) >=2){
                if(chave > atual->dir)
                    rotacaoRR(raiz);
                else
                    rotacaoRL(raiz);
            }
        }
    }
    else
        return 0;

    atual->altura = maior(alturaNo(atual->esq), alturaNo(atual->dir)) + 1;
    return res;
}

int removerNo(ArvAVL* raiz, int chave){
    if(!(*raiz))
        return 0;

    int res;

    if(chave < (*raiz)->chave){
        res = removerNo(&(*raiz)->esq, chave);
        if(res == 1){
            if(fb(*raiz) >= 2){
                if(alturaNo((*raiz)->dir->esq <= alturaNo((*raiz)->dir->dir)))
                    rotacaoRR(raiz);
                else   
                    rotacaoRL(raiz);
            }
        }
    }

    else if(chave > (*raiz)->chave){
        res = removerNo(&(*raiz)->dir, chave);
        if(res == 1){
            if(fb(*raiz) >= 2){
                if(alturaNo((*raiz)->esq->dir) <= alturaNo((*raiz)->esq->esq))
                    rotacaoLL(raiz);
                else
                    rotacaoLR(raiz);
            }
        }
    }

    else{
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            No* temp = (*raiz);
            if(temp->esq == NULL)
                (*raiz) = (*raiz)->dir;
            else
                (*raiz) = (*raiz)->dir;
            free(temp);
        }
        else{
            No* ant = *raiz;
            No* suc = ant->dir;
            while(suc){
                ant = suc;
                suc = suc->esq;
            }

            if(ant == *raiz)
                (*raiz)->chave = (*raiz)->dir->chave;
            else
                (*raiz)->chave = ant->chave;

            removerNo(&(*raiz)->dir, (*raiz)->chave);
        }

        (*raiz)->altura = maior(alturaNo((*raiz)->esq), alturaNo((*raiz)->dir)) + 1;
    }

}

No* procuraMenor(No* atual){
    No* suc = atual->esq;
}