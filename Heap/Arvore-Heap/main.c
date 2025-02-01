#include <stdio.h>
#include "heap.h"

int main(){
    Heap* h = createHeap(10);

    insHeap(h, 10);
    insHeap(h, 20);
    insHeap(h, 7);
    insHeap(h, 14);
    insHeap(h, 32);

    remHeap(h);

    insHeap(h, 100);
    insHeap(h, 2);
    insHeap(h, 123);
    insHeap(h, 13);
    insHeap(h, 1000);

    remHeap(h);

    insHeap(h, 1);
    insHeap(h, 888);

    printHeap(h);


    return 0;
}