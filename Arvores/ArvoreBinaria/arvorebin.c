#include <stdio.h>
#include <stdlib.h>
#include "arvorebin.h"

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

    liberaNOeFilhos(*raiz);
    free(raiz);
}

int liberaNOeFilhos(No* no){
    if(no == NULL)
        return 0;
    liberaNOeFilhos(no->esq);
    liberaNOeFilhos(no->dir);
    free(no);

    return 1;
}

void preOrdem(ArvBin* raiz){
    if(raiz){
        
    }
}