#include <stdio.h>
#include <stdlib.h>
#include "arv_bin_bus.h"

struct no{
    int dado;
    struct no* esq;
    struct no* dir; 
};

ArvBin* criarArvore(){
    ArvBin* raiz = (ArvBin*) malloc (sizeof(ArvBin));

    if(!raiz){
        printf("Erro de alocacao da arvore\n");
        exit(1);
    }

    *raiz = NULL;

    return raiz;
}

void liberaArvore(ArvBin* raiz){
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

int inserirNo(ArvBin* raiz, int dado){
    No* novo = (No*) malloc (sizeof(No));

    if(!novo){
        printf("Estouro de memoria\n");
        return 0;
    }

    novo->dado = dado;
    novo->esq = NULL;
    novo->dir = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        No* atual = *raiz;
        No* ant;
        while(atual != NULL){
            ant = atual;
            
            if(dado == atual->dado){
                printf("Elemento repetido\n");
                return 0;
            }

            if(dado > atual->dado)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        
        if(dado > ant->dado)
            ant->dir = novo;
        else
            ant->esq = novo;
    }

    return 1;
}

int removerNo(ArvBin* raiz, int chave){
    if(*raiz == NULL)
        return 0;

    if(chave > (*raiz)->dado)
        removerNo(&((*raiz)->dir), chave);
    else if(chave < (*raiz)->dado)
        removerNo(&((*raiz)->esq), chave);
    else{
        if((*raiz)->esq == NULL && (*raiz)->dir == NULL){
            free((*raiz));
            return 1;
        }

        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            No* aux = (*raiz);

            if((*raiz)->esq != NULL){
                (*raiz) = (*raiz)->esq;
                free(aux);
            }
            else{
                (*raiz) = (*raiz)->dir;
                free(aux);
            }

            return 1;
        }

        No* ant = (*raiz);
        No* suc = (*raiz)->dir;

        while(suc->esq != NULL){
            ant = suc;
            suc = suc->esq;
        }

        (*raiz)->dado = suc->dado;
        if(ant == (*raiz)){
            ant->dir = suc->dir;
            free(suc);
        }
        else{
            ant->esq = suc->dir;
            free(suc);
        }
    }
    return 1;
}

int estaVazia(ArvBin* raiz){
    if(!(*raiz))
        return 1;
    else 
        return 0;
}

int alturaArvore(ArvBin* raiz){
    if(!(*raiz))
        return 0;

    int alt_esq = alturaArvore(&((*raiz)->esq));
    int alt_dir = alturaArvore(&((*raiz)->dir));

    if(alt_esq > alt_dir)
        return alt_esq + 1;
    else   
        return alt_dir + 1;
}

int qntdNo(ArvBin* raiz){
    if(!(*raiz))
        return 0;

    int cont_esq = qntdNo(&((*raiz)->esq));
    int cont_dir = qntdNo(&((*raiz)->dir));

    return cont_esq + cont_dir + 1;
}

int consultarNo(ArvBin* raiz, int chave){
    if((*raiz) == NULL)
        return 0;

    if(chave > (*raiz)->dado)
        consultarNo(&((*raiz)->dir), chave);
    else if(chave < (*raiz)->dado)
        consultarNo(&((*raiz)->esq), chave);
    else{
        printf("Elemento encontrado!\n");
        return 1;
    }
    return 0;
}

void preOrdem(ArvBin* raiz){
    if(!raiz)
        return;

    if(*raiz){
        printf("%d\n", (*raiz)->dado);
        preOrdem(&((*raiz)->esq));
        preOrdem(&((*raiz)->dir));
    }
}

void emOrdem(ArvBin* raiz){
    if(!raiz)
        return;

    if(*raiz){
        emOrdem(&((*raiz)->esq));
        printf("%d\n", (*raiz)->dado);
        emOrdem(&((*raiz)->dir));
    }
}

void posOrdem(ArvBin* raiz){
    if(!raiz)
        return;

    if(*raiz){
        posOrdem(&((*raiz)->esq));
        posOrdem(&((*raiz)->dir));
        printf("%d\n", (*raiz)->dado);
    }
}