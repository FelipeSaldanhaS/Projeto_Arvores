//nome: David Belizario Rodrigues – prontuário: gu3011631 – Turma: ADS2ºSEM.

//nome: Felipe Saldanha de Souza – prontuário: gu3011801 – Turma: ADS2ºSEM.

#define TAMANHO 15000


typedef struct funcionario
{
    int id;
    char nome[100];
    int idade;
    char empresa[100];
    char depto[100];
    float sal;
} Funcionario;

//FUNÇÃO DE ORDENAÇÃO
void QuickSort(Funcionario *vetor, int esquerda, int direita);

//---------------------------
//ARVORE RUBRO NEGRA E METODOS:
typedef struct NO *ArvLLRB;

ArvLLRB *cria_arvLLRB();

void liberar_arvLLRB(ArvLLRB *raiz);

int vazia_arvLLRB(ArvLLRB *raiz);

int altura_arvLLRB(ArvLLRB *raiz);

int totalNO_arvLLRB(ArvLLRB *raiz);

void preOrdem_arvLLRB(ArvLLRB *raiz);

void emOrdem_arvLLRB(ArvLLRB *raiz);

void posOrdem_arvLLRB(ArvLLRB *raiz);

int insere_arvoreLLRB(ArvLLRB *raiz, Funcionario func);

int remove_arvoreLLRB(ArvLLRB *raiz, Funcionario func);

int consulta_arvLLRB(ArvLLRB *raiz, Funcionario func);

//---------------------------
//ARVORE AVL E METODOS:

typedef struct NO *ArvAVL;

ArvAVL *cria_arvAVL();

void liberar_arvAVL(ArvAVL *raiz);

int vazia_arvAVL(ArvAVL *raiz);

int altura_arvAVL(ArvAVL *raiz);

int totalNO_arvAVL(ArvAVL *raiz);

void preOrdem_arvAVL(ArvAVL *raiz);

void emOrdem_arvAVL(ArvAVL *raiz);

void posOrdem_arvAVL(ArvAVL *raiz);

int insere_arvAVL(ArvAVL *raiz, Funcionario func);

int remove_arvAVL(ArvAVL *raiz, Funcionario func);

int consulta_arvAVL(ArvAVL *raiz, Funcionario func);


int alt_no(struct NO *no);

int fatorBalanceamento_NO(struct NO *no);

int maior(int x, int y);

void rotacaoLL(ArvAVL *raiz);

void rotacaoRR(ArvAVL *raiz);

void rotacaoLR(ArvAVL *raiz);

void rotacaoRL(ArvAVL *raiz);
