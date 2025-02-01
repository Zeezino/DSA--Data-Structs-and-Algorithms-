typedef struct no No;
typedef struct no* ArvAVL;

ArvAVL* criarArvore();
void liberaArvore(ArvAVL* raiz);
int liberaSubarvore(No* alvo);

int estaVazia(ArvAVL* raiz);
int alturaArvore(ArvAVL* raiz);

int qntdNo(ArvAVL* raiz);
int consultarNo(ArvAVL* raiz, int chave);

void preOrdem(ArvAVL* raiz);
void emOrdem(ArvAVL* raiz);
void posOrdem(ArvAVL* raiz);

int alturaNo(No* no);
int fb(No* no);
int maior(int a, int b);

void rotacaoLL(ArvAVL* A);
void rotacaoRR(ArvAVL* A);
void rotacaoLR(ArvAVL* A);
void rotacaoRL(ArvAVL* A);

int inserirNo(ArvAVL* raiz, int dado);
int removerNo(ArvAVL* raiz, int chave);

No* procuraMenor(No* no);