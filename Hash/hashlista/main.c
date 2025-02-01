#include <stdio.h>
#include "hash.h"

int main(){
    Hash* ha = criaHash(10);

    criaElemento(ha, 100, "Rodrigo Correa");
    criaElemento(ha, 150, "Aime Couto");
    criaElemento(ha, 111, "Pedro Sobral");
    criaElemento(ha, 231, "Bigorna Dura");

    // if(!buscaHash_Sem_Colisao(ha, 1002))
    //     printf("\nElemento nao encontrado!\n\n");

    printHash(ha);

    return 0;
}