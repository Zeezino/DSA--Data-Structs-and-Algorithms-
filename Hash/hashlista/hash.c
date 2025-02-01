#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

struct elemento{
    int chave;
    char nome[30];
    struct elemento* prox;
};

struct hash{
    int size, qntd;
    struct elemento** itens;
};

Hash* criaHash(int size){
    Hash* ha = (Hash*) malloc (sizeof(Hash));

    if(ha){
        ha->size = size;
        ha->itens = (Elem**) malloc (size*sizeof(Elem*));

        if(!ha->itens){
            free(ha);
            return NULL;
        }

        ha->qntd = 0;
        for(int I=0; I<size; I++){
            ha->itens[I] = NULL;
        }

        return ha;
    }

    return NULL;
}

void liberaHash(Hash* ha){
    if(ha){
        Elem* aux;
        for(int I=0; I<ha->size; I++){
            if(ha->itens[I]){
                aux = ha->itens[I];
                while(aux){
                    ha->itens[I] = ha->itens[I]->prox;
                    free(aux);
                    aux = ha->itens[I];
                }
            }
        }
        free(ha);
    }
}

int chaveDivisao(int chave, int tam){
    return (chave & 0x7FFFFFFF) % tam;
}

int chaveMultiplicacao(int chave, int tam){
    float fracionario = 0.6189274276;
    float aux = chave * fracionario;
    aux -= (int)aux;

    return (int) aux*tam;
}

int chaveString(char* str){
    int I, valor=13;
    int tam = strlen(str);
    for(I=0; I<tam; I++)
        valor = 31*valor + (int)str[I];

    return valor;    
}

int criaElemento(Hash* ha, int chave, char* nome){
    Elem* novo = (Elem*) malloc (sizeof(Elem));
    if(novo){
        novo->chave = chave;
        strcpy(novo->nome, nome);
        novo->prox = NULL;

        insereHash_Sem_Colisao(ha, novo);
    }
    return 0;
}

int insereHash_Sem_Colisao(Hash* ha, Elem* elemento){
    if(ha){
        int pos = chaveDivisao(elemento->chave, ha->size);
        // int pos = chaveMultiplicacao(elemento.chave, ha->size);
        // int pos = chaveString(elemento.nome);

        if(!ha->itens[pos])
            ha->itens[pos] = elemento;

        else{
            Elem* aux = ha->itens[pos];
            while(aux->prox) 
                aux=aux->prox;
            aux->prox = elemento;
        }

        return 1;
    }
    return 0;
}

int buscaHash_Sem_Colisao(Hash* ha, int chave){
    if(ha){
        int pos;
        pos = chaveDivisao(chave, ha->size);
        // int pos = chaveMultiplicacao(elemento.chave, ha->size);
        // int pos = chaveString(elemento.nome);

        if(ha->itens[pos]){
            Elem* aux = ha->itens[pos];
            while(aux && aux->chave != chave){
                aux = aux->prox;
            }
            if(!aux)
                return 0;
            else{
                printf("\nElemento encontrado!\n\nInformacoes:\n");
                printf("Chave: %d\nNome: ", chave);
                puts(aux->nome);
                printf("\n");
                return 1;
            }
        }
    }

    return 0;
}

void printHash(Hash* ha){
    printf("--------------\nArray do Hash:\n--------------\n");
    for(int I=0; I<ha->size; I++){
        printf("Posicao %d: ", I);
        if(!ha->itens[I])
            printf("NULL\n");
        else{
            Elem* aux = ha->itens[I];
            while(aux){
                aux->prox == NULL ? printf("%s ", aux->nome) : printf("%s, ", aux->nome);
                aux = aux->prox;
            }
            printf("\n");
        }
    }
    printf("\n");
}