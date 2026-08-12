// CODIGO DA ILHA - SISTEMA DE INVENTARIO - NIVEL AVENTUREIRO
// COMPARACAO ENTRE VETOR (LISTA SEQUENCIAL) E LISTA ENCADEADA

// BIBLIOTECAS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// CONSTANTE - NUMERO MAXIMO DE ITENS QUE A MOCHILA (VETOR) PODE ARMAZENAR

#define MAX_ITENS 10

// STRUCT - REPRESENTA UM ITEM DO INVENTARIO

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;

} Item;

// STRUCT - NO DA LISTA ENCADEADA

typedef struct No {
    Item dados;
    struct No* proximo;

} No;

// CONTADORES GLOBAIS DE COMPARACOES

int comparacoesSequencialVetor = 0;
int comparacoesBinariaVetor    = 0;
int comparacoesSequencialLista = 0;

// FLAG DE CONTROLE - indica se o vetor esta ordenado no momento.
int vetorOrdenado = 0;

// limparBuffer - Limpa caracteres que eventualmente ficaram no buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* ============================================================
 * =====================  MOCHILA - VETOR  ====================
 * ============================================================
 *
 * Implementacao classica usando um vetor (lista sequencial).
  */

// Cadastro de item na mochila-vetor

int inserirItemVetor(Item vetor[], int quantidadeItens, Item novoItem) {

    // Verifica se a mochila ja esta cheia

    if (quantidadeItens >= MAX_ITENS) {
        printf("\n========================================\n");
        printf("     MOCHILA (VETOR) CHEIA!\n");
        printf("==========================================\n");
        printf("Nao e possivel cadastrar mais itens no vetor.\n");

        return quantidadeItens;
    }

    vetor[quantidadeItens] = novoItem;
    quantidadeItens++;

    // Uma nova insercao pode quebrar a ordenacao anterior.
    vetorOrdenado = 0;

    printf("Item cadastrado com sucesso na mochila-VETOR!\n");
    return quantidadeItens;
}

// Remocao de item na mochila-vetor por nome
int removerItemVetor(Item vetor[], int quantidadeItens, char nomeRemover[]) {

    int i;
    int encontrado = 0;

    if (quantidadeItens == 0) {
        printf("A mochila-VETOR esta vazia.\n");
        return quantidadeItens;
    }

    for (i = 0; i < quantidadeItens; i++) {
        if (strcmp(vetor[i].nome, nomeRemover) == 0) {
            encontrado = 1;

            // Deslocamento dos elementos para "tapar o buraco".
            for (int j = i; j < quantidadeItens - 1; j++) {
                vetor[j] = vetor[j + 1];
            }

            quantidadeItens--;

            printf("Item removido com sucesso da mochila-VETOR!\n");

            break;
        }
    }

    if (encontrado == 0) {
        printf("Item nao encontrado na mochila-VETOR.\n");
    }

    // A remocao tambem pode alterar a ordenacao (por conta do deslocamento).
    vetorOrdenado = 0;

    return quantidadeItens;
}

// Listagem de itens da mochila-vetor
void listarItensVetor(Item vetor[], int quantidadeItens) {

    int i;

    printf("\n========================================\n");
    printf("     INVENTARIO DA MOCHILA - VETOR\n");
    printf("==========================================\n");

    if (quantidadeItens == 0) {
        printf("A mochila-VETOR esta vazia.\n");
        return;
    }

    for (i = 0; i < quantidadeItens; i++) {

        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", vetor[i].nome);
        printf("Tipo: %s\n", vetor[i].tipo);
        printf("Quantidade: %d\n", vetor[i].quantidade);
        printf("----------------------------------------\n");
    }
}

// Busca SEQUENCIAL

int buscarSequencialVetor(Item vetor[], int quantidadeItens, char nomeBusca[]) {

    int i;
    comparacoesSequencialVetor = 0;

    for (i = 0; i < quantidadeItens; i++) {
        comparacoesSequencialVetor++;

        if (strcmp(vetor[i].nome, nomeBusca) == 0) {
            return i;
        }
    }

    return -1;
}

// Ordenacao do vetor por nome

void ordenarVetor(Item vetor[], int quantidadeItens) {

    int i, j;
    Item auxiliar;

    for (i = 0; i < quantidadeItens - 1; i++) {

        for (j = 0; j < quantidadeItens - i - 1; j++) {

            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {

                auxiliar = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = auxiliar;
            }
        }
    }

    vetorOrdenado = 1;

    printf("Vetor ordenado por nome com sucesso!\n");
}

// Busca BINARIA

int buscarBinariaVetor(Item vetor[], int quantidadeItens, char nomeBusca[]) {

    int inicio = 0;
    int fim = quantidadeItens - 1;
    int meio;
    int comparacao;

    comparacoesBinariaVetor = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        comparacoesBinariaVetor++;
        comparacao = strcmp(vetor[meio].nome, nomeBusca);

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

/* ============================================================
 * ==================  MOCHILA - LISTA ENCADEADA  =============
 * ============================================================
*/

// Cadastro de item na mochila-lista (insercao no final da lista)

No* inserirItemLista(No* inicio, Item novoItem) {

    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o novo item!\n");
        return inicio;
    }

    novoNo->dados = novoItem;
    novoNo->proximo = NULL;

    // Lista ainda vazia: o novo no passa a ser o inicio
    if (inicio == NULL) {
        printf("Item cadastrado com sucesso na mochila-LISTA!\n");
        return novoNo;
    }

    // Percorre ate o ultimo no para encadear o novo item no final
    No* atual = inicio;

    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }

    atual->proximo = novoNo;
    printf("Item cadastrado com sucesso na mochila-LISTA!\n");

    return inicio;
}

// Remocao de item na mochila-lista por nome

No* removerItemLista(No* inicio, char nomeRemover[]) {

    if (inicio == NULL) {
        printf("A mochila-LISTA esta vazia.\n");
        return inicio;
    }

    No* atual = inicio;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeRemover) == 0) {

            // Remocao do primeiro no da lista.
            if (anterior == NULL) {
                inicio = atual->proximo;
            }
            else {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            printf("Item removido com sucesso da mochila-LISTA!\n");
            return inicio;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item nao encontrado na mochila-LISTA.\n");
    return inicio;
}

// Listagem de itens da mochila-lista

void listarItensLista(No* inicio) {

    printf("\n========================================\n");
    printf("     INVENTARIO DA MOCHILA - LISTA\n");
    printf("==========================================\n");

    if (inicio == NULL) {
        printf("A mochila-LISTA esta vazia.\n");
        return;
    }

    No* atual = inicio;
    int i = 1;

    while (atual != NULL) {

        printf("\nItem %d\n", i);
        printf("Nome: %s\n", atual->dados.nome);
        printf("Tipo: %s\n", atual->dados.tipo);
        printf("Quantidade: %d\n", atual->dados.quantidade);
        printf("----------------------------------------\n");

        atual = atual->proximo;
        i++;
    }
}

// Busca SEQUENCIAL de item na mochila-lista por nome

No* buscarSequencialLista(No* inicio, char nomeBusca[]) {

    No* atual = inicio;
    comparacoesSequencialLista = 0;

    while (atual != NULL) {
        comparacoesSequencialLista++;

        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
}

// Libera toda a memoria alocada pela lista encadeada.

void liberarLista(No* inicio) {

    No* atual = inicio;
    No* proximoNo;

    while (atual != NULL) {
        proximoNo = atual->proximo;
        free(atual);
        atual = proximoNo;
    }
}

/* ============================================================
 * ================  COMPARACAO DE DESEMPENHO  ================
 * ============================================================
*/

void compararDesempenho(Item vetor[], int quantidadeItens, No* inicioLista) {

    char nomeBusca[30];
    clock_t inicioTempo, fimTempo;
    double tempoSequencialVetor, tempoSequencialLista, tempoBinariaVetor;
    int indiceVetor, indiceBinario;
    No* noEncontrado;

    printf("\n========================================\n");
    printf("     COMPARAR DESEMPENHO DAS ESTRUTURAS\n");
    printf("==========================================\n");

    if (quantidadeItens == 0 && inicioLista == NULL) {
        printf("As mochilas estao vazias. Cadastre itens antes de comparar.\n");
        return;
    }

    limparBuffer();

    printf("Digite o nome do item critico a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    // ----- BUSCA SEQUENCIAL NO VETOR -----

    inicioTempo = clock();
    indiceVetor = buscarSequencialVetor(vetor, quantidadeItens, nomeBusca);
    fimTempo = clock();
    tempoSequencialVetor = ((double) (fimTempo - inicioTempo)) / CLOCKS_PER_SEC * 1000.0;

    // ----- BUSCA SEQUENCIAL NA LISTA -----

    inicioTempo = clock();
    noEncontrado = buscarSequencialLista(inicioLista, nomeBusca);
    fimTempo = clock();
    tempoSequencialLista = ((double) (fimTempo - inicioTempo)) / CLOCKS_PER_SEC * 1000.0;

    printf("\n----------------------------------------\n");
    printf("BUSCA SEQUENCIAL - VETOR\n");
    printf("Item encontrado: %s\n", (indiceVetor != -1) ? "SIM" : "NAO");
    printf("Comparacoes realizadas: %d\n", comparacoesSequencialVetor);
    printf("Tempo gasto: %.5f ms\n", tempoSequencialVetor);

    printf("\nBUSCA SEQUENCIAL - LISTA ENCADEADA\n");
    printf("Item encontrado: %s\n", (noEncontrado != NULL) ? "SIM" : "NAO");
    printf("Comparacoes realizadas: %d\n", comparacoesSequencialLista);
    printf("Tempo gasto: %.5f ms\n", tempoSequencialLista);

    // ----- BUSCA BINARIA NO VETOR (SO SE ESTIVER ORDENADO) -----

    if (vetorOrdenado) {

        inicioTempo = clock();
        indiceBinario = buscarBinariaVetor(vetor, quantidadeItens, nomeBusca);
        fimTempo = clock();
        tempoBinariaVetor = ((double) (fimTempo - inicioTempo)) / CLOCKS_PER_SEC * 1000.0;

        printf("\nBUSCA BINARIA - VETOR (ORDENADO)\n");
        printf("Item encontrado: %s\n", (indiceBinario != -1) ? "SIM" : "NAO");
        printf("Comparacoes realizadas: %d\n", comparacoesBinariaVetor);
        printf("Tempo gasto: %.5f ms\n", tempoBinariaVetor);
    }
    else {
        printf("\nBUSCA BINARIA - VETOR\n");
        printf("Vetor ainda nao esta ordenado. Utilize a opcao\n");
        printf("'Ordenar vetor por nome' para habilitar a busca binaria.\n");
    }

    printf("----------------------------------------\n");
    printf("\nCONCLUSAO:\n");
    printf("A busca binaria no vetor ordenado tende a exigir muito\n");
    printf("menos comparacoes que as buscas sequenciais, especialmente\n");
    printf("a medida que o inventario cresce. Ja a lista encadeada evita\n");
    printf("deslocamento de elementos ao inserir/remover, mas nao permite\n");
    printf("busca binaria, pois nao ha acesso direto por indice.\n");
}

/* ============================================================
 * FUNCAO PRINCIPAL - MAIN
 * ============================================================
*/

int main() {

    // Vetor de structs - capacidade fixa para MAX_ITENS itens

    Item inventarioVetor[MAX_ITENS];
    int quantidadeItens = 0;

    // Ponteiro para o inicio da lista encadeada

    No* inventarioLista = NULL;

    int opcao;

    do {

        printf("\n\n");
        printf("========================================\n");
        printf(" MOCHILA DE LOOT - NIVEL AVENTUREIRO\n");
        printf("========================================\n");

        printf("Itens no vetor: %d/%d | Vetor ordenado: %s\n",
               quantidadeItens,
               MAX_ITENS,
               vetorOrdenado ? "SIM" : "NAO");

        printf("----------------------------------------\n");

        printf("1 - Cadastrar item (vetor e lista)\n");
        printf("2 - Remover item (vetor e lista)\n");
        printf("3 - Listar itens (vetor e lista)\n");
        printf("4 - Buscar item - sequencial (vetor e lista)\n");
        printf("5 - Ordenar vetor por nome (Bubble Sort)\n");
        printf("6 - Buscar item - busca binaria (somente vetor)\n");
        printf("7 - Comparar desempenho das estruturas\n");
        printf("0 - Sair\n");

        printf("----------------------------------------\n");

        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {

            /* =================================================
             * OPCAO 1 - CADASTRAR
             * =================================================
             */

            case 1: {

                Item novoItem;

                printf("\n========================================\n");
                printf("       CADASTRO DE ITEM\n");
                printf("==========================================\n");

                limparBuffer();

                printf("Digite o nome do item: ");
                fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
                novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

                printf("Digite o tipo do item (arma, municao, cura, ferramenta): ");
                fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
                novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

                printf("Digite a quantidade: ");
                scanf("%d", &novoItem.quantidade);

                quantidadeItens = inserirItemVetor(inventarioVetor, quantidadeItens, novoItem);
                inventarioLista = inserirItemLista(inventarioLista, novoItem);

                listarItensVetor(inventarioVetor, quantidadeItens);
                listarItensLista(inventarioLista);

                break;
            }

            /* =================================================
             * OPCAO 2 - REMOVER
             * =================================================
             */

            case 2: {

                char nomeRemover[30];

                printf("\n========================================\n");
                printf("            REMOVER ITEM\n");
                printf("==========================================\n");

                limparBuffer();

                printf("Digite o nome do item que deseja remover: ");
                fgets(nomeRemover, sizeof(nomeRemover), stdin);
                nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

                quantidadeItens = removerItemVetor(inventarioVetor, quantidadeItens, nomeRemover);
                inventarioLista = removerItemLista(inventarioLista, nomeRemover);

                listarItensVetor(inventarioVetor, quantidadeItens);
                listarItensLista(inventarioLista);

                break;
            }

            /* =================================================
             * OPCAO 3 - LISTAR
             * =================================================
             */

            case 3:

                listarItensVetor(inventarioVetor, quantidadeItens);
                listarItensLista(inventarioLista);

                break;

            /* =================================================
             * OPCAO 4 - BUSCAR SEQUENCIAL
             * =================================================
             */

            case 4: {

                char nomeBusca[30];
                int indiceVetor;
                No* noEncontrado;

                printf("\n========================================\n");
                printf("       BUSCAR ITEM - SEQUENCIAL\n");
                printf("==========================================\n");

                limparBuffer();

                printf("Digite o nome do item: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                indiceVetor = buscarSequencialVetor(inventarioVetor, quantidadeItens, nomeBusca);

                printf("\n--- Resultado no VETOR ---\n");
                if (indiceVetor != -1) {
                    printf("Item encontrado!\n");
                    printf("Nome: %s\n", inventarioVetor[indiceVetor].nome);
                    printf("Tipo: %s\n", inventarioVetor[indiceVetor].tipo);
                    printf("Quantidade: %d\n", inventarioVetor[indiceVetor].quantidade);
                }
                else {
                    printf("Item nao encontrado no vetor.\n");
                }
                printf("Comparacoes realizadas (vetor): %d\n", comparacoesSequencialVetor);

                noEncontrado = buscarSequencialLista(inventarioLista, nomeBusca);

                printf("\n--- Resultado na LISTA ---\n");
                if (noEncontrado != NULL) {
                    printf("Item encontrado!\n");
                    printf("Nome: %s\n", noEncontrado->dados.nome);
                    printf("Tipo: %s\n", noEncontrado->dados.tipo);
                    printf("Quantidade: %d\n", noEncontrado->dados.quantidade);
                }
                else {
                    printf("Item nao encontrado na lista.\n");
                }
                printf("Comparacoes realizadas (lista): %d\n", comparacoesSequencialLista);

                break;
            }

            /* =================================================
             * OPCAO 5 - ORDENAR VETOR
             * =================================================
             */

            case 5:

                if (quantidadeItens == 0) {
                    printf("\nA mochila-VETOR esta vazia. Nada a ordenar.\n");
                }
                else {
                    ordenarVetor(inventarioVetor, quantidadeItens);
                    listarItensVetor(inventarioVetor, quantidadeItens);
                }

                break;

            /* =================================================
             * OPCAO 6 - BUSCA BINARIA
             * =================================================
             */

            case 6: {

                char nomeBusca[30];
                int indiceBinario;

                if (!vetorOrdenado) {
                    printf("\nO vetor precisa estar ordenado para a busca binaria.\n");
                    printf("Utilize a opcao 5 antes de tentar novamente.\n");
                    break;
                }

                printf("\n========================================\n");
                printf("       BUSCAR ITEM - BUSCA BINARIA\n");
                printf("==========================================\n");

                limparBuffer();

                printf("Digite o nome do item: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                indiceBinario = buscarBinariaVetor(inventarioVetor, quantidadeItens, nomeBusca);

                if (indiceBinario != -1) {
                    printf("\nItem encontrado!\n");
                    printf("Nome: %s\n", inventarioVetor[indiceBinario].nome);
                    printf("Tipo: %s\n", inventarioVetor[indiceBinario].tipo);
                    printf("Quantidade: %d\n", inventarioVetor[indiceBinario].quantidade);
                }
                else {
                    printf("\nItem nao encontrado no vetor.\n");
                }
                printf("Comparacoes realizadas (busca binaria): %d\n", comparacoesBinariaVetor);

                break;
            }

            /* =================================================
             * OPCAO 7 - COMPARAR DESEMPENHO
             * =================================================
             */

            case 7:

                compararDesempenho(inventarioVetor, quantidadeItens, inventarioLista);

                break;

            /* =================================================
             * OPCAO 0 - SAIR
             * =================================================
             */

            case 0:

                printf("\n========================================\n");
                printf("     Encerrando o inventario...\n");
                printf("     Obrigado por jogar!\n");
                printf("========================================\n");

                break;

            /* =================================================
             * OPCAO INVALIDA
             * =================================================
             */

            default:

                printf("\nOpcao invalida!\n");
                printf("Escolha uma opcao entre 0 e 7.\n");

                break;
        }

    } while (opcao != 0);

    // Libera a memoria alocada dinamicamente pela lista encadeada.

    liberarLista(inventarioLista);

    return 0;
}