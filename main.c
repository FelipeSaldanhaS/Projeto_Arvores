//nome: David Belizario Rodrigues – prontuário: gu3011631 – Turma: ADS2ºSEM.

//nome: Felipe Saldanha de Souza – prontuário: gu3011801 – Turma: ADS2ºSEM.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/time.h>
#include <time.h>
#include "Projeto_Arvores.h"
int main()
{
    setlocale(LC_ALL, "Portuguese");
    printf("ALGORITMO DE ORGANIZAÇÃO\n");
    //------VARIAVEIS-------
    //Contendo estruturas para medição de tempo, estruturas de dados, estruturas das arvores, seletores inteiros, string para absorver informação futuramente e ponteiros
    //com proposito de abrir arquivos e armazenar dados.
    struct timeval Tempo_antes, Tempo_depois;
    double deltaT;
    ArvAVL *raiz = NULL;
    ArvLLRB *raizRB = NULL;
    Funcionario *func_aux;
    Funcionario func;
    int menu = 0;
    int i = 0;
    char texto[150];
    FILE *f;
    //------INICIALIZAÇÃO DAS ARVORES E MALLOCS-----
    raiz = cria_arvAVL();
    raizRB = cria_arvLLRB();

    func_aux = (Funcionario *) malloc(TAMANHO * sizeof(Funcionario));
    //------ABERTURA DO ARQUIVO-----
    f = fopen("massaDados.csv","r");
    if(f==NULL)
    {
        printf("erro na abertura do arquivo\n");
    }
    else
    {
        printf("Arquivo aberto com sucesso\n");
    }
    //------MENU------------
    //Este menu foi criado com a intenção de dar opções de escolha ao usuário de forma sucinta.
    while(menu == 0)
    {
        //Este trecho de código em loop vai perguntar qual caso do switch seguinte ele deverá executar.
        int i = 0;
        printf("\n====== MENU ========\n");
        printf("\nEscolha o tipo de árvore que vai ter valores inseridos: \n1 - AVL \n2 - RUBRO NEGRA INCLINADA PARA ESQUERDA \nQualquer outro valor resultará na saida do sistema.\nDica: Executar no loop uma opção depois dessa da mesma árvore criará um resultado insatisfatório.\nRecomenda-se reiniciar o programa depois de uma operação em cada árvore.\n");
        scanf("%d", &i);
        printf("\n==============\n");
        //Switch criado para opções de árvore, seja a AVL ou a LLRB.
        switch(i)
        {
        //--------------- ARVORE AVL ----------------------
        case 1:
            printf("\n==============\n");
            printf("Escolha se quer \n1-Ordenado \nou \n2-Desordenado \nQualquer outro valor encerrará o programa.\n");
            scanf("%d", &i);
            printf("\n==============\n");
            //ORDENADO AVL------------------------------------------------------------------------------------------
            if(i == 1)
            {

                //Verificando se a árvore se encontra vazia para executar o reconhecimento do arquivo e depois o preenchimento do vetor auxiliar.
                if(vazia_arvAVL(raiz))
                {

                    while(fgets(texto, 100, f))
                    {
                        //printf("entrou no while\n\n");
                        func.id = atoi(strtok(texto, ";"));
                        strcpy(func.nome, strtok(NULL, ";"));
                        func.idade = atoi(strtok(NULL, ";"));
                        strcpy(func.empresa, strtok(NULL, ";"));
                        strcpy(func.depto, strtok(NULL, ";"));
                        func.sal = atof(strtok(NULL, "\n"));


                        func_aux[i].id = func.id;
                        strcpy(func_aux[i].nome, func.nome);
                        func_aux[i].idade = func.idade;
                        strcpy(func_aux[i].empresa, func.empresa);
                        strcpy(func_aux[i].depto, func.depto);
                        func_aux[i].sal = func.sal;
                        i++;
                    }



                    //--- QUICKSORT sendo executado para ordenar o vetor auxiliar de func
                    QuickSort(func_aux, 0, TAMANHO - 1);

                    /* VERIFICAÇÃO DO ORDENADO
                    for(int i = 0; i<TAMANHO; i++)
                    {
                        printf("ID %d\n", func_aux[i].id);
                    }
                    */

                    gerar_arquivo_ordenado(func_aux);
                    //FOR para inserir os dados na arvore depois de ordenados.
                    gettimeofday (&Tempo_antes, NULL);
                    for(int i = 0; i< TAMANHO-1; i++)
                    {
                        //printf("entrou no for insere\n\n");
                        insere_arvAVL(raiz, func_aux[i]);
                    }

                }
                else
                {
                    printf("Já preenchida AVL\n");
                    gettimeofday (&Tempo_antes, NULL);
                }

                gettimeofday (&Tempo_depois, NULL);

                deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) -
                         (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);

                printf("Tempo para inserção na Árvore AVL Ordenada por QuickSort: %f\n",deltaT);

                printf("\n==============\n");
                //Trecho do código que irá demonstrar os valores, como a base de dados é muito grande, deixamos como opcional;
                //No software de execução do relatório, essa operação demorou 64 segundos utilizando 25% da CPU.
                printf("Deseja ver as informações da árvore? 1- SIM e qualquer outro número para NÃO.\n");
                scanf("%d", &i);

                printf("\n==============\n");
                if(i == 1)
                {
                    gettimeofday (&Tempo_antes, NULL);
                    printf("Altura da arvore AVL: %d\n", altura_arvAVL(raiz));
                    printf("Visitando em-Ordem:\n");
                    emOrdem_arvAVL(raiz);

                    gettimeofday (&Tempo_depois, NULL);
                    deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) -
                             (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
                    printf("Tempo para demonstrar as informações da Árvore AVL Ordenada por QuickSort: %f\n",deltaT);
                }
                //A função acima também possui uma cadeia de decisão além de uma medida de tempo que é impressa se permitida.
                system("pause");
                system("cls");

            }
            //DESORDENADO AVL---------------------------------------------------------
            else if(i == 2)
            {
                gettimeofday (&Tempo_antes, NULL);

                if(vazia_arvAVL(raiz))
                {
                    while(fgets(texto, 100, f))
                    {
                        //printf("entrou no while\n\n");
                        func.id = atoi(strtok(texto, ";"));
                        strcpy(func.nome, strtok(NULL, ";"));
                        func.idade = atoi(strtok(NULL, ";"));
                        strcpy(func.empresa, strtok(NULL, ";"));
                        strcpy(func.depto, strtok(NULL, ";"));
                        func.sal = atof(strtok(NULL, "\n"));

                        insere_arvAVL(raiz, func);
                    }
                }
                else
                {
                    printf("Já preenchida AVL\n");
                    gettimeofday (&Tempo_antes, NULL);
                }
                gettimeofday (&Tempo_depois, NULL);

                deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) -
                         (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);

                printf("Tempo para inserção na Árvore AVL Desordenada: %f\n",deltaT);

                printf("\n==============\n");

                //Trecho do código que irá demonstrar os valores, como a base de dados é muito grande, deixamos como opcional;
                //No software de execução do relatório, essa operação demorou 64 segundos utilizando 25% da CPU.
                printf("Deseja ver as informações da árvore? 1- SIM e qualquer outro número para NÃO.\n");
                scanf("%d", &i);

                printf("\n==============\n");
                if(i == 1)
                {
                    gettimeofday (&Tempo_antes, NULL);
                    printf("Altura da arvore AVL: %d\n", altura_arvAVL(raiz));
                    printf("Visitando em-Ordem:\n");
                    emOrdem_arvAVL(raiz);

                    gettimeofday (&Tempo_depois, NULL);
                    deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) -
                             (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
                    printf("Tempo para demonstrar as informações da Árvore AVL Desordenada: %f\n",deltaT);
                }
                //A função acima também possui uma cadeia de decisão além de uma medida de tempo que é impressa se permitida.
                system("pause");
                system("cls");

            }
            else
            {
                printf("Número não está nas opções, saindo da aplicação!\n");
                menu = 1;
            }
            break;
        //--------------- ARVORE LLRB ----------------------
        case 2:
            printf("Escolha se quer \n1-Ordenado \nou \n2-Desordenado \nQualquer outro valor encerrará o programa.\n");
            scanf("%d", &i);
            //ORDENADO LLRB------------------------------------------------------------------------------------
            if(i == 1)
            {


                if(vazia_arvLLRB(raizRB))
                {
                    while(fgets(texto, 100, f))
                    {
                        //printf("entrou no while\n\n");
                        func.id = atoi(strtok(texto, ";"));
                        strcpy(func.nome, strtok(NULL, ";"));
                        func.idade = atoi(strtok(NULL, ";"));
                        strcpy(func.empresa, strtok(NULL, ";"));
                        strcpy(func.depto, strtok(NULL, ";"));
                        func.sal = atof(strtok(NULL, "\n"));


                        func_aux[i].id = func.id;
                        strcpy(func_aux[i].nome, func.nome);
                        func_aux[i].idade = func.idade;
                        strcpy(func_aux[i].empresa, func.empresa);
                        strcpy(func_aux[i].depto, func.depto);
                        func_aux[i].sal = func.sal;
                        i++;
                    }

                    /* VENDO A ORDENAÇÃO
                    for(int i = 0; i<TAMANHO; i++)
                    {
                        printf("ID %d\n", func_aux[i].id);
                    }
                    */

                    //--- QUICKSORT sendo executado para ordenar o vetor auxiliar de func
                    QuickSort(func_aux, 0, TAMANHO-1);
                    gerar_arquivo_ordenado(func_aux);
                    //FOR para inserir os dados na arvore depois de ordenados.
                    gettimeofday (&Tempo_antes, NULL);
                    for(int i = 0; i< TAMANHO-1; i++)
                    {
                        //printf("entrou no for insere\n\n");
                        insere_arvoreLLRB(raizRB, func_aux[i]);
                    }

                }
                else
                {
                    printf("Já preenchida LLRB\n");
                    gettimeofday (&Tempo_antes, NULL);
                }
                gettimeofday (&Tempo_depois, NULL);

                deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) -
                         (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);

                printf("Tempo para inserção na Árvore LLRB Ordenada por QuickSort: %f\n",deltaT);

                printf("\n==============\n");

                //Trecho do código que irá demonstrar os valores, como a base de dados é muito grande, deixamos como opcional;
                //No software de execução do relatório, essa operação demorou 64 segundos utilizando 25% da CPU.
                printf("Deseja ver as informações da árvore? 1- SIM e qualquer outro número para NÃO.\n");
                scanf("%d", &i);

                printf("\n==============\n");
                if(i == 1)
                {
                    gettimeofday (&Tempo_antes, NULL);
                    printf("Altura da arvore LLRB: %d\n", altura_arvLLRB(raizRB));
                    printf("Visitando em-Ordem:\n");
                    emOrdem_arvLLRB(raizRB);

                    gettimeofday (&Tempo_depois, NULL);
                    deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) -
                             (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
                    printf("Tempo para demonstrar as informações da Árvore LLRB Ordenada por QuickSort: %f\n",deltaT);
                }
                //A função acima também possui uma cadeia de decisão além de uma medida de tempo que é impressa se permitida.
                system("pause");
                system("cls");
            }
            //DESORDENADO LLRB
            else if(i == 2)
            {
                gettimeofday (&Tempo_antes, NULL);

                if(vazia_arvLLRB(raizRB))
                {
                    while(fgets(texto, 100, f))
                    {
                        //printf("entrou no while\n\n");
                        func.id = atoi(strtok(texto, ";"));
                        strcpy(func.nome, strtok(NULL, ";"));
                        func.idade = atoi(strtok(NULL, ";"));
                        strcpy(func.empresa, strtok(NULL, ";"));
                        strcpy(func.depto, strtok(NULL, ";"));
                        func.sal = atof(strtok(NULL, "\n"));

                        insere_arvoreLLRB(raizRB,func);
                    }
                }
                else
                {
                    printf("Já preenchida LLRB\n");
                    gettimeofday (&Tempo_antes, NULL);
                }
                gettimeofday (&Tempo_depois, NULL);

                deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) -
                         (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);

                printf("Tempo para inserção na Árvore LLRB Desordenada: %f\n",deltaT);

                printf("\n==============\n");

                //Trecho do código que irá demonstrar os valores, como a base de dados é muito grande, deixamos como opcional;
                //No software de execução do relatório, essa operação demorou 64 segundos utilizando 25% da CPU.
                printf("Deseja ver as informações da árvore? 1- SIM e qualquer outro número para NÃO.\n");
                scanf("%d", &i);

                printf("\n==============\n");
                if(i == 1)
                {
                    gettimeofday (&Tempo_antes, NULL);
                    printf("Altura da arvore LLRB: %d\n", altura_arvLLRB(raizRB));
                    printf("Visitando em-Ordem:\n");
                    emOrdem_arvLLRB(raizRB);

                    gettimeofday (&Tempo_depois, NULL);
                    deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) -
                             (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
                    printf("Tempo para demonstrar as informações da Árvore LLRB Desordenada: %f\n",deltaT);
                }
                //A função acima também possui uma cadeia de decisão além de uma medida de tempo que é impressa se permitida.
                system("pause");
                system("cls");
            }
            else
            {
                printf("Número não está nas opções, saindo da aplicação!\n");
                menu = 1;
            }
            break;

        default:
            menu = 1;
            printf("Saindo da aplicação!\n");
            break;

        }

    }
    if(menu == 1)
    {
        system("cls");
        printf("\nFechando....\n");
    }
    //Liberando as variaveis dinamicas e ponteiros utilizados no projeto, além de fechar o arquivo.
    liberar_arvAVL(raiz);
    liberar_arvLLRB(raizRB);
    fclose(f);
    return 0;
}
