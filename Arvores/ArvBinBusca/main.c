#include <stdio.h>
#include "arv_bin_bus.h"
int main(){
    ArvBin* raiz = criarArvore();

    inserirNo(raiz, 10);
    inserirNo(raiz, 8);
    inserirNo(raiz, 99);
    inserirNo(raiz, 100);
    inserirNo(raiz, 98);
    inserirNo(raiz, 1);
    inserirNo(raiz, 9);
    inserirNo(raiz, 120);

    printf("\nQuantidade de nos: %d\n", qntdNo(raiz));
    printf("Altura da arvore: %d\n\n", alturaArvore(raiz));

    posOrdem(raiz);

    liberaArvore(raiz);

    return 0;
}