typedef struct elemento Elem;
typedef struct hash Hash;

Hash* criaHash(int size);
void liberaHash(Hash* ha);

int chaveDivisao(int chave, int size);
int chaveMultiplicacao(int chave, int size);
int chaveString(char* str);

int criaElemento(Hash* ha, int chave, char* nome);
int insereHash_Sem_Colisao(Hash* ha, Elem* elemento);
int buscaHash_Sem_Colisao(Hash* ha, int chave);

void printHash(Hash* ha);