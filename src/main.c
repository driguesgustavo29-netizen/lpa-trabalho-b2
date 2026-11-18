#include <stdio.h>
#include <stdlib.h>

#define FILEIRAS 4
#define COLUNAS 5
#define CAPACIDADE_INICIAL 2

typedef struct {
    char identificador[8];
    char descricao[61];
    int categoria;
    int fileira;
    int coluna;
} Veiculo;

void inicializarMapa(int mapa[FILEIRAS][COLUNAS]) {
    for (int i = 0; i < FILEIRAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            mapa[i][j] = 0;
        }
    }
}

void exibirMapa(int mapa[FILEIRAS][COLUNAS]) {
    printf("\n===== MAPA DO ESTACIONAMENTO =====\n\n");

    printf("     ");
    for (int j = 0; j < COLUNAS; j++) {
        printf("C%d ", j + 1);
    }

    printf("\n");

    for (int i = 0; i < FILEIRAS; i++) {
        printf("F%d   ", i + 1);

        for (int j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == 0) {
                printf(".  ");
            } else {
                printf("X  ");
            }
        }

        printf("\n");
    }

    printf("\nLegenda: X = ocupada | . = livre\n");
}

void exibirMenu() {
    printf("\n===== SISTEMA DE ESTACIONAMENTO =====\n");
    printf("1 - Cadastrar veiculo\n");
    printf("2 - Consultar veiculo\n");
    printf("3 - Atualizar veiculo\n");
    printf("4 - Mover veiculo\n");
    printf("5 - Remover veiculo\n");
    printf("6 - Listar veiculos\n");
    printf("7 - Exibir mapa de vagas\n");
    printf("8 - Relatorio de ocupacao\n");
    printf("0 - Encerrar\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int mapa[FILEIRAS][COLUNAS];
    int opcao;

    int quantidade = 0;
    int capacidade = CAPACIDADE_INICIAL;

    Veiculo *veiculos = malloc(capacidade * sizeof(Veiculo));

    if (veiculos == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    inicializarMapa(mapa);

    printf("Memoria inicializada para %d veiculos.\n", capacidade);

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nCadastro sera implementado.\n");
                break;

            case 2:
                printf("\nConsulta sera implementada.\n");
                break;

            case 3:
                printf("\nAtualizacao sera implementada.\n");
                break;

            case 4:
                printf("\nMovimentacao sera implementada.\n");
                break;

            case 5:
                printf("\nRemocao sera implementada.\n");
                break;

            case 6:
                printf("\nListagem sera implementada.\n");
                break;

            case 7:
                exibirMapa(mapa);
                break;

            case 8:
                printf("\nRelatorio sera implementado.\n");
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    free(veiculos);

    printf("Memoria liberada com sucesso!\n");

    return 0;
}
