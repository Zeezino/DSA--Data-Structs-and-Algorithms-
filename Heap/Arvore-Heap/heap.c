#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

struct node{
    int value;
    struct node* left;
    struct node* right;
};

struct heap{
    int size, pos;
    int* vet;
};

Heap* createHeap(int size){
    Heap* h = (Heap*) malloc (sizeof(Heap));

    if(h){
        h->vet = (int*) calloc (size, sizeof(int));
        if(h->vet){
            h->pos = 0;
            h->size = size;
            return h;
        }
        free(h);
    }
    return NULL;
}

void freeHeap(Heap* h){
    free(h->vet);
    free(h);
}

int insHeap(Heap* h, int element){
    if(h->pos == h->size){
        printf("\nHeap ja esta cheia\n\n");
        return 0;
    }

    h->vet[h->pos] = element;
    bottomTop(h, h->pos);
    h->pos++;

    return 1;
}

void bottomTop(Heap* h, int index){
    int parent;
    while(index > 0){
        parent = (index - 1)/2;
        if(h->vet[index] > h->vet[parent]){
            int aux = h->vet[index];
            h->vet[index] = h->vet[parent];
            h->vet[parent] = aux;
            index = parent;
        }
        else
            break;
    }
}

int remHeap(Heap* h){
    if(h->pos == 0){
        printf("\nHeap ja esta vazia\n");
        return 0;
    }

    int max = h->vet[0];
    h->pos--;
    h->vet[0] = h->vet[h->pos];
    topBottom(h, 0);
    return max;
}

void topBottom(Heap* h, int index){
    int left, right, max;

    while(1){
        left = index*2 +1;
        right = index*2 + 2;
        max = index;

        if(h->vet[max] < h->vet[left])
            max = left;
        if(h->vet[max] < h->vet[right])
            max = right;
        if(max == index)
            break;

        int aux = h->vet[max];
        h->vet[max] = h->vet[index];
        h->vet[index] = aux;
        index = max;
    }
}

void printHeap(Heap* h){
    printf("\nImpressao heap:\n");
    for(int I=0; I<h->pos; I++){
        printf("%d ", h->vet[I]);
    }
    printf("\n\n");
}