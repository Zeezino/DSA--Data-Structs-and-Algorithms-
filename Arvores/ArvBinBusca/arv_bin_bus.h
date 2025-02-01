typedef struct no No;
typedef struct no* ArvBin;

ArvBin* criarArvore();
void liberaArvore(ArvBin* raiz);
int liberaSubarvore(No* alvo);

int inserirNo(ArvBin* raiz, int dado);
int removerNo(ArvBin* raiz, int chave);

int estaVazia(ArvBin* raiz);
int alturaArvore(ArvBin* raiz);

int qntdNo(ArvBin* raiz);
int consultarNo(ArvBin* raiz, int chave);

void preOrdem(ArvBin* raiz);
void emOrdem(ArvBin* raiz);
void posOrdem(ArvBin* raiz);