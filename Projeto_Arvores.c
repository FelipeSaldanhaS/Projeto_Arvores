//nome: David Belizario Rodrigues – prontuário: gu3011631 – Turma: ADS2ºSEM.

//nome: Felipe Saldanha de Souza – prontuário: gu3011801 – Turma: ADS2ºSEM.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Projeto_Arvores.h"

//STRUCT NO PARA USO NAS ARVORES
struct NO
{
    Funcionario func;
    int alt;
    struct NO *esq;
    struct NO *dir;
    int cor;
};
//CODIGO DE ORDENAÇÃO
void QuickSort(Funcionario *vetor, int esquerda, int direita)
{
    int i, j, meio, troca;
    i = esquerda;
    j= direita;
    meio = vetor[(esquerda+direita)/2].id;

    while(i <= j)
    {
        while(vetor[i].id<meio && i<direita)
        {
            i++;
        }
        while(vetor[j].id>meio && j>esquerda)
        {
            j--;
        }
        if(i<=j)
        {
            troca = vetor[i].id;
            vetor[i].id = vetor[j].id;
            vetor[j].id = troca;
            i++;
            j--;
        }
    }

    if(j>esquerda)
    {
        QuickSort(vetor, esquerda, j);
    }
    if(i<direita)
    {
        QuickSort(vetor, i, direita);
    }
}
//CÓDIGO DE GERAÇÃO DO ARQUIVO ORDENADO

int gerar_arquivo_ordenado(Funcionario *func)
{
    FILE *f = fopen("arquivo_gerado_ordenado.txt","w");
    if(f == NULL)
    {
        printf("\nErro na criação do arquivo ordenado!\n");
        exit(1);
    }
    else
    {
        printf("\nArquivo ordenado criado com sucesso!\n");
    }
    for(int i = 0; i < TAMANHO; i++)
    {
        fprintf(f,"%d;%s;%d;%s;%s;%.2f\n",func[i].id,func[i].nome,func[i].idade,func[i].empresa,func[i].depto,func[i].sal);
    }
    fclose(f);
}

//CONSTANTES USADAS:
#define RED 1
#define BLACK 0


// ARVORE AVL E SUAS FUNÇÕES:


struct NO *remove_atual(struct NO *atual)
{
    struct NO *no1, *no2;
    if(atual->esq == NULL)
    {
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL)
    {
        no1 = no2;
        no2 = no2->dir;
    }
    if(no1 != atual)
    {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

ArvAVL *cria_arvAVL()
{
    ArvAVL *raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
    {
        *raiz = NULL;
    }
    return raiz;
}

void liberar_arvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
    {
        return;
    }
    libera_NO(*raiz);
    free(raiz);
}

void libera_NO(struct NO *no)
{
    if(no == NULL)
    {
        return;
    }
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

int vazia_arvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
    {
        return 1;
    }
    if(*raiz == NULL)
    {
        return 1;
    }
    return 0;
}

int altura_arvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
    {
        return 0;
    }
    if(*raiz == NULL)
    {
        return 0;
    }
    int alt_esq = altura_arvAVL(&((*raiz)->esq));
    int alt_dir = altura_arvAVL(&((*raiz)->dir));
    if(alt_esq > alt_dir)
    {
        return(alt_esq + 1);
    }
    else
    {
        return(alt_dir + 1);
    }
}

int totalNO_arvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
    {
        return 0;
    }
    if(*raiz == NULL)
    {
        return 0;
    }
    int alt_esq = totalNO_arvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_arvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}
/*
void preOrdem_arvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
    {
        return;
    }
    if(*raiz != NULL)
    {
        printf("%d\n", (*raiz)->info);
        preOrdem_arvAVL(&((*raiz)->esq));
        preOrdem_arvAVL(&((*raiz)->dir));
    }
}
*/
void emOrdem_arvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
    {
        return;
    }
    if(*raiz != NULL)
    {
        emOrdem_arvAVL(&((*raiz)->esq));
        printf("\n==============\n");
        printf("%d\n", (*raiz)->func.id);
        printf("%s\n", (*raiz)->func.nome);
        printf("%d\n", (*raiz)->func.idade);
        printf("%s\n", (*raiz)->func.empresa);
        printf("%s\n", (*raiz)->func.depto);
        printf("%.2f\n", (*raiz)->func.sal);
        printf("\n==============\n");
        emOrdem_arvAVL(&((*raiz)->dir));
    }
}
/*
void posOrdem_arvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
    {
        return;
    }
    if(*raiz != NULL)
    {
        posOrdem_arvAVL(&((*raiz)->esq));
        posOrdem_arvAVL(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info);
    }
}
*/
int insere_arvAVL(ArvAVL *raiz, Funcionario func)
{
    int res;
    if(*raiz == NULL)
    {
        struct NO *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL)
        {
            return 0;
        }
        novo->func.id = func.id;
        strcpy(novo->func.nome, func.nome);
        novo->func.idade = func.idade;
        strcpy(novo->func.empresa, func.empresa);
        strcpy(novo->func.depto, func.depto);
        novo->func.sal = func.sal;

        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }
    struct NO *atual = *raiz;
    if(func.id < atual->func.id)
    {
        if((res = insere_arvAVL(&(atual->esq), func)) == 1)
        {
            if(fatorBalanceamento_NO(atual) >= 2)
            {
                if(func.id < (*raiz)->esq->func.id)
                {
                    rotacaoLL(raiz);
                }
                else
                {
                    rotacaoLR(raiz);
                }
            }
        }

    }
    else
    {
        if(func.id > atual->func.id)
        {
            if((res = insere_arvAVL(&(atual->dir), func)) == 1)
            {
                if(fatorBalanceamento_NO(atual) >= 2)
                {
                    if((*raiz)->dir->func.id< func.id)
                    {
                        rotacaoRR(raiz);
                    }
                    else
                    {
                        rotacaoRL(raiz);
                    }
                }
            }
        }
        else
        {
            //printf("Valor duplicado!\n");
            return 0;
        }
    }

    atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
    return res;
}

struct NO *procuramenor(struct NO *atual)
{
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}
/*
int remove_arvAVL(ArvAVL *raiz, int valor)
{
    if(*raiz == NULL){
        return 0;
    }
    int res;
    if(valor < (*raiz)->info){
        if((res = remove_arvAVL(&(*raiz)->esq, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(alt_no((*raiz)->dir->esq)<= alt_no((*raiz)->dir->dir)){
                    rotacaoRR(raiz);
                }else{
                    rotacaoRL(raiz);
                }
            }
        }
    }

    if((*raiz)->info < valor){
        if((res = remove_arvAVL(&(*raiz)->dir,valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(alt_no((*raiz)->dir->esq) <= alt_no((*raiz)->esq->esq)){
                    rotacaoLL(raiz);
                }else{
                    rotacaoLR(raiz);
                }
            }
        }
    }
    if((*raiz)->info == valor){
        if(((*raiz)->esq == NULL) || (*raiz)->dir == NULL){
            struct NO *no_velho = (*raiz);
            if((*raiz)->esq != NULL){
                *raiz = (*raiz)->esq;
            }else{
                *raiz = (*raiz)->dir;
            }
            free(no_velho);
        }else{
            struct NO *temp = procuramenor((*raiz)->dir);
            (*raiz)->info = temp->info;
            remove_arvAVL( (*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq)){
                    rotacaoLL(raiz);
                }else{
                    rotacaoLR(raiz);
                }
            }
        }
        if(*raiz != NULL){
            (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
        }
        return 1;
    }
    if(*raiz != NULL){
        (*raiz)->alt = maior(alt_no((*raiz)->esq),alt_no((*raiz)->dir)) + 1;
    }
    return res;
}

*/
/*
int consulta_arvAVL(ArvAVL *raiz, int valor)
{
    if(raiz == NULL)
    {
        return 0;
    }
    struct NO *atual = *raiz;
    while(atual != NULL)
    {
        if(valor == atual->info)
        {
            return 1;
        }
        if(valor> atual->info)
        {
            atual = atual->dir;
        }
        else
        {
            atual = atual->esq;
        }

    }
    return 0;
}
*/
int alt_no(struct NO *no)
{
    if(no == NULL)
    {
        return -1;
    }
    else
    {
        return no->alt;
    }
}

int fatorBalanceamento_NO(struct NO *no)
{
    return labs(alt_no(no->esq) - alt_no(no->dir));
}

int maior(int x, int y)
{
    if(x > y)
    {
        return(x);
    }
    else
    {
        return(y);
    }
}

void rotacaoLL(ArvAVL *raiz)
{
    struct NO *no;
    no = (*raiz)->esq;
    (*raiz)->esq = no->dir;
    no->dir = (*raiz);
    (*raiz)->alt = maior(alt_no( (*raiz)->esq),alt_no( (*raiz)->dir) ) + 1;
    no->alt = maior(alt_no(no->esq), (*raiz)->alt) + 1;
    (*raiz) = no;
}

void rotacaoRR(ArvAVL *raiz)
{
    struct NO *no;
    no = (*raiz)->dir;
    (*raiz)->dir = no->esq;
    no->esq = (*raiz);
    (*raiz)->alt = maior(alt_no((*raiz)->esq),alt_no((*raiz)->dir)) + 1;
    no->alt = maior(alt_no(no->dir), (*raiz)->alt) + 1;
    *raiz = no;
}

void rotacaoRL(ArvAVL *raiz)
{
    rotacaoLL(&(*raiz)->dir);
    rotacaoRR(raiz);
}

void rotacaoLR(ArvAVL *raiz)
{
    rotacaoRR(&(*raiz)->esq);
    rotacaoLL(raiz);
}

//---------------------------------------------------------------------------------------------
//ARVORE RUBRO NEGRA INCLINADA PARA ESQUERDA
ArvLLRB *cria_arvLLRB()
{
    ArvLLRB *raiz = (ArvLLRB*) malloc(sizeof(ArvLLRB));
    if(raiz != NULL)
    {
        *raiz = NULL;
    }
    return raiz;
}

void liberar_arvLLRB(ArvLLRB *raiz)
{
    if(raiz == NULL)
    {
        return;
    }
    libera_NO(*raiz);
    free(raiz);
}

int vazia_arvLLRB(ArvLLRB *raiz)
{
    if(raiz == NULL)
    {
        return 1;
    }
    if(*raiz == NULL)
    {
        return 1;
    }
    return 0;
}

int altura_arvLLRB(ArvLLRB *raiz)
{
    if(raiz == NULL)
    {
        return 0;
    }
    if(*raiz == NULL)
    {
        return 0;
    }
    int alt_esq = altura_arvLLRB(&((*raiz)->esq));
    int alt_dir = altura_arvLLRB(&((*raiz)->dir));
    if(alt_esq > alt_dir)
    {
        return(alt_esq + 1);
    }
    else
    {
        return(alt_dir + 1);
    }
}

int totalNO_arvLLRB(ArvLLRB *raiz)
{
    if(raiz == NULL)
    {
        return 0;
    }
    if(*raiz == NULL)
    {
        return 0;
    }
    int alt_esq = totalNO_arvLLRB(&((*raiz)->esq));
    int alt_dir = totalNO_arvLLRB(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}
/*
void preOrdem_arvLLRB(ArvLLRB *raiz){
    if(raiz == NULL){
      return;
    }
    if(*raiz != NULL){
        printf("%d\n", (*raiz)->info);
        preOrdem_arvLLRB(&((*raiz)->esq));
        preOrdem_arvLLRB(&((*raiz)->dir));
    }
}
*/

void emOrdem_arvLLRB(ArvLLRB *raiz)
{
    if(raiz == NULL)
    {
        return;
    }
    if(*raiz != NULL)
    {
        emOrdem_arvLLRB(&((*raiz)->esq));
        printf("\n==============\n");
        printf("%d\n", (*raiz)->func.id);
        printf("%s\n", (*raiz)->func.nome);
        printf("%d\n", (*raiz)->func.idade);
        printf("%s\n", (*raiz)->func.empresa);
        printf("%s\n", (*raiz)->func.depto);
        printf("%.2f\n", (*raiz)->func.sal);
        printf("%d\n", (*raiz)->cor);
        printf("\n==============\n");
        emOrdem_arvLLRB(&((*raiz)->dir));
    }
}

/*
void posOrdem_arvLLRB(ArvLLRB *raiz){
    if(raiz == NULL){
      return;
    }
    if(*raiz != NULL){
        posOrdem_arvLLRB(&((*raiz)->esq));
        posOrdem_arvLLRB(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info);
    }
}
*/
int cor(struct NO *H)
{
    if(H == NULL)
    {
        return BLACK;
    }
    else
    {
        return H->cor;
    }
}

void trocaCor(struct NO *H)
{
    H->cor = !H->cor;
    if(H->esq != NULL)
    {
        H->esq->cor = !H->esq->cor;
    }
    if(H->dir != NULL)
    {
        H->dir->cor = !H->dir->cor;
    }
}

struct NO *rotacionaEsquerda(struct NO *A)
{
    struct NO *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
};

struct NO *rotacionaDireita(struct NO *A)
{
    struct NO *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
};

struct NO *move2EsqRED(struct NO *H)
{
    trocaCor(H);
    if(cor(H->dir->esq) == RED)
    {
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
};

struct NO *move2DirRED(struct NO *H)
{
    trocaCor(H);
    if(cor(H->esq->esq) == RED)
    {
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
};

struct NO *balancear(struct NO *H)
{
    if(cor(H->dir) == RED)
    {
        H = rotacionaEsquerda(H);
    }
    if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED)
    {
        H = rotacionaDireita(H);
    }
    if(cor(H->dir) == RED && cor(H->dir) == RED)
    {
        trocaCor(H);
    }
    return H;
};

struct NO *insereNO(struct NO *H,Funcionario func, int *resp)
{
    if(H == NULL)
    {
        struct NO *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL)
        {
            *resp = 0;
            return NULL;
        }

        novo->func.id = func.id;
        strcpy(novo->func.nome, func.nome);
        novo->func.idade = func.idade;
        strcpy(novo->func.empresa, func.empresa);
        strcpy(novo->func.depto, func.depto);
        novo->func.sal = func.sal;

        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }
    if(func.id == H->func.id)
    {
        *resp = 0;
    }
    else
    {
        if(func.id < H->func.id)
        {
            H->esq = insereNO(H->esq, func, resp);
        }
        else
        {
            H->dir = insereNO(H->dir, func, resp);
        }
    }
    if(cor(H->dir) == RED && cor(H->esq) == BLACK)
    {
        H = rotacionaEsquerda(H);
    }
    if(cor(H->esq) == RED && cor(H->esq->esq) == RED)
    {
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED)
    {
        trocaCor(H);
    }
    return H;
};

int insere_arvoreLLRB(ArvLLRB *raiz, Funcionario func)
{
    int resp;
    *raiz = insereNO(*raiz, func, &resp);
    if((*raiz) != NULL)
    {
        (*raiz)->cor = BLACK;
    }
    return resp;
}

struct NO *procuraMenor(struct NO *atual)
{
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
};

struct NO *removeMenor(struct NO *H)
{
    if(H->esq == NULL)
    {
        free(H);
        return NULL;
    }
    if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK)
    {
        H = move2EsqRED(H);
    }
    H->esq = removeMenor(H->esq);
    return balancear(H);
};

struct NO *removeNO(struct NO *H, Funcionario func)
{
    if(func.id < H->func.id)
    {
        if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK)
        {
            H = move2EsqRED(H);
        }
        H->esq = removeNO(H->esq, func);
    }
    else
    {
        if(cor(H->esq) == RED)
        {
            H = rotacionaDireita(H);
        }
        if(func.id == H->func.id && (H->dir == NULL))
        {
            free(H);
            return NULL;
        }
        if(cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK)
        {
            H = move2DirRED(H);
        }
        if(func.id == H->func.id)
        {
            struct NO *x = procuraMenor(H->dir);
            H->func.id = x->func.id;
            H->dir = removeMenor(H->dir);
        }
        else
        {
            H->dir = removeNO(H->dir, func);
        }
    }
    return balancear(H);
};

int remove_arvoreLLRB(ArvLLRB *raiz, Funcionario func)
{
    if(consulta_arvLLRB(raiz, func))
    {
        struct NO *H = *raiz;
        *raiz = removeNO(H, func);
        if(*raiz != NULL)
        {
            (*raiz)->cor = BLACK;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

int consulta_arvLLRB(ArvLLRB *raiz, Funcionario func)
{
    if(raiz == NULL)
    {
        return 0;
    }
    struct NO *atual = *raiz;
    while(atual != NULL)
    {
        if(func.id == atual->func.id)
        {
            return 1;
        }
        if(func.id > atual->func.id)
        {
            atual = atual->dir;
        }
        else
        {
            atual = atual->esq;
        }

    }
    return 0;
}



