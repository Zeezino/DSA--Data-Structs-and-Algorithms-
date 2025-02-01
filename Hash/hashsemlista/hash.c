#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

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
        for(int I=0; I<ha->size; I++){
            if(ha->itens[I])
                free(ha->itens[I]);
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

int sondagemLinear(int pos, int i, int size){
    return ((pos + i) & 0x7FFFFFFF) % size;
}

int sondagemQuadratica(int pos, int i, int size){
    pos = pos + 2*i + 3*i*i;
    return (pos & 0x7FFFFFFF) % size;
}

int insereHash_Sem_Colisao(Hash* ha, Elem elemento){
    if(ha){
        int pos = chaveDivisao(elemento.chave, ha->size);
        // int pos = chaveMultiplicacao(elemento.chave, ha->size);
        // int pos = chaveString(elemento.nome);

        int newpos, I;
        for(I=0; I<ha->size; I++){
            newpos = sondagemLinear(pos, I, ha->size);
            // newpos = sondagemQuadratica(pos, I, ha->size);

            if(!ha->itens[newpos]){
                Elem* novo = (Elem*) malloc (sizeof(Elem));
                if(novo){
                    *novo = elemento;
                    ha->itens[newpos] = novo;
                    return 1;
                }

                return 0;
            }
        }
    }
    return 0;
}

int buscaHash_Sem_Colisao(Hash* ha, int chave){
    if(ha){
        int pos, newpos, I;
        pos = chaveDivisao(chave, ha->size);
        // int pos = chaveMultiplicacao(elemento.chave, ha->size);
        // int pos = chaveString(elemento.nome);

        if(ha->itens[pos]){
            for(I=0; I<ha->size; I++){
                newpos = sondagemLinear(pos, I, ha->size);
                // newpos = sondagemQuadratica(pos, I, ha->size);

                if(!ha->itens[newpos])
                    return 0;

                if(ha->itens[newpos]->chave == chave){
                    printf("\nElemento encontrado!\n\nInformacoes:\n");
                    printf("Chave: %d\nNome: ", chave);
                    puts(ha->itens[newpos]->nome);
                    printf("\n");

                    return 1;
                }
            }
        }
    }

    return 0;
}

void printHash(Hash* ha){
    printf("--------------\nArray do Hash:\n--------------\n");
    for(int I=0; I<ha->size; I++){
        if(!ha->itens[I])
            printf("NULL\n");
        else
            puts(ha->itens[I]->nome);
    }
    printf("\n");
}