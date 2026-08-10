#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item mochila[MAX_ITENS]; // Vetor de itens da mochila
int totalItens = 0;      // Controla quantos itens estao cadastrados

void limparBuffer();
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

int main() {
    int opcao;

    do {
        printf("\n=== INVENTARIO INICIAL ===\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida! Digite apenas numeros.\n");
            limparBuffer();
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do inventario...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// Remove o '\n' que sobra no buffer apos o scanf
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Cadastra um novo item na mochila
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel cadastrar mais itens.\n");
        return;
    }

    Item novo;

    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo (arma, municao, cura): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();

    mochila[totalItens] = novo;
    totalItens++;

    printf("Item cadastrado com sucesso!\n");
}

// Remove um item da mochila pelo nome
void removerItem() {
    char nome[30];
    int pos = -1;

    printf("Nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    // Busca sequencial pelo nome
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item nao encontrado na mochila.\n");
        return;
    }

    // Desloca os itens seguintes uma posicao para tras
    for (int i = pos; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    totalItens--;

    printf("Item removido com sucesso!\n");
}

// Lista todos os itens cadastrados na mochila
void listarItens() {
    if (totalItens == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n--- Itens na mochila ---\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Nome: %-15s Tipo: %-10s Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Busca sequencial: localiza um item pelo nome e exibe seus dados
void buscarItem() {
    char nome[30];

    printf("Nome do item a buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Encontrado -> Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("Item nao encontrado na mochila.\n");
}