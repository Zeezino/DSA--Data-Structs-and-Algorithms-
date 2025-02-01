typedef struct heap Heap;

Heap* createHeap(int size);
void freeHeap(Heap* h);

int insHeap(Heap* h, int element);
void bottomTop(Heap* h, int index);

int remHeap(Heap* h);
void topBottom(Heap* h, int index);

void printHeap(Heap* h);