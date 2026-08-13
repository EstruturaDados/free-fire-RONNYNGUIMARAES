// TORRE DE RESGATE - MODULO AVANCADO DE ORGANIZACAO DE COMPONENTES
// ORDENACAO (BUBBLE, INSERTION, SELECTION), BUSCA BINARIA E DESEMPENHO

// BIBLIOTECAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// CONSTANTE - NUMERO MAXIMO DE COMPONENTES DA TORRE

#define MAX_COMPONENTES 20

// STRUCT - REPRESENTA UM COMPONENTE DA TORRE DE RESGATE

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;

} Componente;

// CONTADOR GLOBAL - NUMERO DE COMPARACOES DA ULTIMA ORDENACAO/BUSCA EXECUTADA

long comparacoes = 0;

// FLAG DE CONTROLE - indica se o vetor esta ordenado por nome no momento

int ordenadoPorNome = 0;

// limparBuffer - Limpa caracteres que eventualmente ficaram no buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* ============================================================
 * ==================  CADASTRO DE COMPONENTES  ===============
 * ============================================================
*/

// Cadastra um novo componente no vetor, respeitando o limite maximo

int cadastrarComponente(Componente vetor[], int quantidade) {

    if (quantidade >= MAX_COMPONENTES) {
        printf("\n========================================\n");
        printf("   LIMITE DE COMPONENTES ATINGIDO!\n");
        printf("==========================================\n");
        printf("Nao e possivel cadastrar mais componentes (maximo %d).\n", MAX_COMPONENTES);

        return quantidade;
    }

    printf("\n========================================\n");
    printf("        CADASTRO DE COMPONENTE\n");
    printf("==========================================\n");

    printf("Digite o nome do componente (ex: chip central): ");
    fgets(vetor[quantidade].nome, sizeof(vetor[quantidade].nome), stdin);
    vetor[quantidade].nome[strcspn(vetor[quantidade].nome, "\n")] = '\0';

    printf("Digite o tipo do componente (ex: controle, suporte, propulsao): ");
    fgets(vetor[quantidade].tipo, sizeof(vetor[quantidade].tipo), stdin);
    vetor[quantidade].tipo[strcspn(vetor[quantidade].tipo, "\n")] = '\0';

    printf("Digite a prioridade do componente (1 a 10): ");
    scanf("%d", &vetor[quantidade].prioridade);
    limparBuffer();

    quantidade++;

    // Qualquer novo cadastro invalida a ordenacao por nome vigente
    ordenadoPorNome = 0;

    printf("Componente cadastrado com sucesso!\n");

    return quantidade;
}

/* ============================================================
 * ===================  ALGORITMOS DE ORDENACAO  ==============
 * ============================================================
 */

// Bubble sort - ordena o vetor de componentes por NOME (string)

void bubbleSortNome(Componente vetor[], int tamanho) {

    int i, j;
    Componente auxiliar;

    comparacoes = 0;

    for (i = 0; i < tamanho - 1; i++) {

        for (j = 0; j < tamanho - i - 1; j++) {

            comparacoes++;

            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                auxiliar = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = auxiliar;
            }
        }
    }

    ordenadoPorNome = 1;
}

// Insertion sort - ordena o vetor de componentes por TIPO (string)

void insertionSortTipo(Componente vetor[], int tamanho) {

    int i, j;
    Componente atual;

    comparacoes = 0;

    for (i = 1; i < tamanho; i++) {

        atual = vetor[i];
        j = i - 1;

        // A condicao dupla do while conta como uma comparacao relevante
        
        while (j >= 0) {

            comparacoes++;

            if (strcmp(vetor[j].tipo, atual.tipo) > 0) {
                vetor[j + 1] = vetor[j];
                j--;
            }
            else {
                break;
            }
        }

        vetor[j + 1] = atual;
    }

    ordenadoPorNome = 0;
}

// Selection sort - ordena o vetor de componentes por PRIORIDADE (int)

void selectionSortPrioridade(Componente vetor[], int tamanho) {

    int i, j, indiceMenor;
    Componente auxiliar;

    comparacoes = 0;

    for (i = 0; i < tamanho - 1; i++) {

        indiceMenor = i;

        for (j = i + 1; j < tamanho; j++) {

            comparacoes++;

            if (vetor[j].prioridade < vetor[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }

        if (indiceMenor != i) {
            auxiliar = vetor[i];
            vetor[i] = vetor[indiceMenor];
            vetor[indiceMenor] = auxiliar;
        }
    }

    ordenadoPorNome = 0;
}

/* ============================================================
 * =====================  BUSCA BINARIA  ======================
 * ============================================================
*/

// Busca binaria pelo componente-chave, aplicavel apenas apos a
// ordenacao por nome. Retorna o indice do componente ou -1

int buscaBinariaPorNome(Componente vetor[], int tamanho, char chave[]) {

    int inicio = 0;
    int fim = tamanho - 1;
    int meio;
    int comparacao;

    comparacoes = 0;

    while (inicio <= fim) {

        meio = (inicio + fim) / 2;

        comparacoes++;
        comparacao = strcmp(vetor[meio].nome, chave);

        if (comparacao == 0) {
            return meio;
        }
        else if (comparacao < 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    return -1;
}

/* ===========================================================
 * =====================  EXIBICAO  ==========================
 * ===========================================================
*/

// Exibe todos os componentes cadastrados, formatados em tabela

void mostrarComponentes(Componente vetor[], int tamanho) {

    int i;

    printf("\n========================================\n");
    printf("        COMPONENTES DA TORRE\n");
    printf("==========================================\n");

    if (tamanho == 0) {
        printf("Nenhum componente cadastrado ainda.\n");
        return;
    }

    for (i = 0; i < tamanho; i++) {

        printf("\nComponente %d\n", i + 1);
        printf("Nome: %s\n", vetor[i].nome);
        printf("Tipo: %s\n", vetor[i].tipo);
        printf("Prioridade: %d\n", vetor[i].prioridade);
        printf("----------------------------------------\n");
    }
}

/* ============================================================
 * ==================  MEDICAO DE DESEMPENHO  =================
 * ============================================================
*/

// Executa o algoritmo de ordenacao recebido por ponteiro de funcao,
// medindo o tempo gasto (clock()) e reportando o numero de
// comparacoes realizadas (via contador global "comparacoes")

void medirTempo(void (*algoritmo)(Componente[], int), Componente vetor[], int tamanho) {

    clock_t inicioTempo, fimTempo;
    double tempoGasto;

    inicioTempo = clock();
    algoritmo(vetor, tamanho);
    fimTempo = clock();

    tempoGasto = ((double) (fimTempo - inicioTempo)) / CLOCKS_PER_SEC * 1000.0;

    printf("\n----------------------------------------\n");
    printf("Comparacoes realizadas: %ld\n", comparacoes);
    printf("Tempo gasto: %.5f ms\n", tempoGasto);
    printf("------------------------------------------\n");
}

/* ============================================================
 * FUNCAO PRINCIPAL - MAIN
 * ============================================================
*/

int main() {

    // Vetor de structs - capacidade fixa para MAX_COMPONENTES itens

    Componente torre[MAX_COMPONENTES];
    int quantidade = 0;

    int opcao;
    char chaveBusca[30];
    int indiceEncontrado;

    do {

        printf("\n\n");
        printf("========================================\n");
        printf(" TORRE DE RESGATE - MODULO AVANCADO\n");
        printf("========================================\n");

        printf("Componentes cadastrados: %d/%d | Ordenado por nome: %s\n",
               quantidade,
               MAX_COMPONENTES,
               ordenadoPorNome ? "SIM" : "NAO");

        printf("----------------------------------------\n");

        printf("1 - Cadastrar componente\n");
        printf("2 - Ordenar por NOME (Bubble Sort)\n");
        printf("3 - Ordenar por TIPO (Insertion Sort)\n");
        printf("4 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5 - Buscar componente-chave (Busca Binaria - so apos ordenar por nome)\n");
        printf("6 - Mostrar componentes\n");
        printf("0 - Sair\n");

        printf("----------------------------------------\n");

        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {

            /* =================================================
             * OPCAO 1 - CADASTRAR
             * =================================================
             */

            case 1:

                quantidade = cadastrarComponente(torre, quantidade);
                mostrarComponentes(torre, quantidade);

                break;

            /* =================================================
             * OPCAO 2 - BUBBLE SORT POR NOME
             * =================================================
             */

            case 2:

                if (quantidade == 0) {
                    printf("\nNenhum componente cadastrado. Nada a ordenar.\n");
                    break;
                }

                printf("\n========================================\n");
                printf("   ORDENANDO POR NOME (BUBBLE SORT)\n");
                printf("==========================================\n");

                medirTempo(bubbleSortNome, torre, quantidade);
                mostrarComponentes(torre, quantidade);

                break;

            /* =================================================
             * OPCAO 3 - INSERTION SORT POR TIPO
             * =================================================
             */

            case 3:

                if (quantidade == 0) {
                    printf("\nNenhum componente cadastrado. Nada a ordenar.\n");
                    break;
                }

                printf("\n========================================\n");
                printf("  ORDENANDO POR TIPO (INSERTION SORT)\n");
                printf("==========================================\n");

                medirTempo(insertionSortTipo, torre, quantidade);
                mostrarComponentes(torre, quantidade);

                break;

            /* =================================================
             * OPCAO 4 - SELECTION SORT POR PRIORIDADE
             * =================================================
             */

            case 4:

                if (quantidade == 0) {
                    printf("\nNenhum componente cadastrado. Nada a ordenar.\n");
                    break;
                }

                printf("\n========================================\n");
                printf(" ORDENANDO POR PRIORIDADE (SELECTION SORT)\n");
                printf("==========================================\n");

                medirTempo(selectionSortPrioridade, torre, quantidade);
                mostrarComponentes(torre, quantidade);

                break;

            /* ========================================================
             * OPCAO 5 - BUSCA BINARIA (SOMENTE APOS ORDENAR POR NOME)
             * ========================================================
             */

            case 5:

                if (quantidade == 0) {
                    printf("\nNenhum componente cadastrado. Nada a buscar.\n");
                    break;
                }

                if (!ordenadoPorNome) {
                    printf("\nO vetor precisa estar ordenado por NOME para a busca binaria.\n");
                    printf("Utilize a opcao 2 antes de tentar novamente.\n");
                    break;
                }

                printf("\n========================================\n");
                printf("     BUSCAR COMPONENTE-CHAVE\n");
                printf("==========================================\n");

                printf("Digite o nome do componente-chave: ");
                fgets(chaveBusca, sizeof(chaveBusca), stdin);
                chaveBusca[strcspn(chaveBusca, "\n")] = '\0';

                indiceEncontrado = buscaBinariaPorNome(torre, quantidade, chaveBusca);

                if (indiceEncontrado != -1) {
                    printf("\nComponente-chave ENCONTRADO! Torre pode ser ativada.\n");
                    printf("Nome: %s\n", torre[indiceEncontrado].nome);
                    printf("Tipo: %s\n", torre[indiceEncontrado].tipo);
                    printf("Prioridade: %d\n", torre[indiceEncontrado].prioridade);
                }
                else {
                    printf("\nComponente-chave NAO encontrado. Torre nao pode ser ativada.\n");
                }

                printf("\n----------------------------------------\n");
                printf("Comparacoes realizadas: %ld\n", comparacoes);
                printf("----------------------------------------\n");

                break;

            /* =================================================
             * OPCAO 6 - MOSTRAR COMPONENTES
             * =================================================
             */

            case 6:

                mostrarComponentes(torre, quantidade);

                break;

            /* =================================================
             * OPCAO 0 - SAIR
             * =================================================
             */

            case 0:

                printf("\n========================================\n");
                printf("   Encerrando o modulo da torre...\n");
                printf("   Boa sorte na fuga da ilha!\n");
                printf("==========================================\n");

                break;

            /* =================================================
             * OPCAO INVALIDA
             * =================================================
             */

            default:

                printf("\nOpcao invalida!\n");
                printf("Escolha uma opcao entre 0 e 6.\n");

                break;
        }

    } while (opcao != 0);

    return 0;
}