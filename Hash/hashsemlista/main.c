#include <stdio.h>
#include "hash.h"

int main(){
    Elem ricardo = {1000, "Ricardo"};
    Elem maria = {1020, "Maria"};
    Elem aime = {1001, "Amorzinhu"};
    Elem rodrigo = {1037, "Rodrigo"};

    Hash* ha = criaHash(10);

    insereHash_Sem_Colisao(ha, ricardo);
    insereHash_Sem_Colisao(ha, rodrigo);
    insereHash_Sem_Colisao(ha, aime);
    insereHash_Sem_Colisao(ha, maria);

    if(!buscaHash_Sem_Colisao(ha, 1002))
        printf("\nElemento nao encontrado!\n\n");

    printHash(ha);

    return 0;
}