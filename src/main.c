
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// Limpa caracteres restantes da entrada
void limparBufferEntrada() {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

// Inicializa todas as vagas como livres
void inicializarMapa(int mapa[FILEIRAS][COLUNAS]) {
    for (int i = 0; i < FILEIRAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            mapa[i][j] = 0;
        }
    }
}

// Exibe o mapa do estacionamento
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

// Exibe as opções do sistema
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

// Valida e padroniza o identificador
int validarIdentificador(char identificador[]) {

    if (strlen(identificador) != 7) {
        return 0;
    }

    for (int i = 0; i < 7; i++) {

        if (!isalnum((unsigned char)identificador[i])) {
            return 0;
        }

        identificador[i] = toupper((unsigned char)identificador[i]);
    }

    return 1;
}

// Procura um veículo pelo identificador
int buscarVeiculo(Veiculo veiculos[], int quantidade,
                  char identificador[]) {

    for (int i = 0; i < quantidade; i++) {

        if (strcmp(veiculos[i].identificador, identificador) == 0) {
            return i;
        }
    }

    return -1;
}

// Aumenta a capacidade do vetor dinâmico
int aumentarCapacidade(Veiculo **veiculos, int *capacidade) {

    int novaCapacidade = *capacidade * 2;

    Veiculo *temporario = realloc(
        *veiculos,
        novaCapacidade * sizeof(Veiculo)
    );

    if (temporario == NULL) {
        return 0;
    }

    *veiculos = temporario;
    *capacidade = novaCapacidade;

    return 1;
}

// Cadastra um veículo
void cadastrarVeiculo(Veiculo **veiculos, int *quantidade,
                      int *capacidade,
                      int mapa[FILEIRAS][COLUNAS]) {

    Veiculo novo;

    printf("\n===== CADASTRO DE VEICULO =====\n");

    // Leitura e validação do identificador
    int identificadorValido = 0;

while (!identificadorValido) {

    printf("Identificador (7 caracteres): ");

    if (fgets(novo.identificador,
              sizeof(novo.identificador), stdin) == NULL) {
        return;
    }

    limparBufferEntrada();

    novo.identificador[
        strcspn(novo.identificador, "\n")
    ] = '\0';

    if (!validarIdentificador(novo.identificador)) {
        printf("Identificador invalido! Digite exatamente 7 caracteres.\n");
        continue;
    }

    if (buscarVeiculo(*veiculos, *quantidade,
                      novo.identificador) != -1) {
        printf("Esse identificador ja esta cadastrado!\n");
        continue;
    }

    identificadorValido = 1;
}

    // Leitura da descrição
    printf("Descricao do veiculo: ");

    if (fgets(novo.descricao, sizeof(novo.descricao), stdin) == NULL) {
        return;
    }

    novo.descricao[strcspn(novo.descricao, "\n")] = '\0';

    // Leitura da categoria
    do {
        printf("Categoria (1 - Carro | 2 - Moto): ");
        scanf("%d", &novo.categoria);
        limparBufferEntrada();

        if (novo.categoria != 1 && novo.categoria != 2) {
            printf("Categoria invalida!\n");
        }

    } while (novo.categoria != 1 && novo.categoria != 2);

    // Escolha e validação da vaga
    do {
        printf("Fileira (1 a %d): ", FILEIRAS);
        scanf("%d", &novo.fileira);

        printf("Coluna (1 a %d): ", COLUNAS);
        scanf("%d", &novo.coluna);

        limparBufferEntrada();

        if (novo.fileira < 1 || novo.fileira > FILEIRAS ||
            novo.coluna < 1 || novo.coluna > COLUNAS) {

            printf("Posicao invalida!\n");

        } else if (mapa[novo.fileira - 1][novo.coluna - 1] == 1) {

            printf("Essa vaga ja esta ocupada!\n");
            novo.fileira = 0;

        }

    } while (novo.fileira < 1 || novo.fileira > FILEIRAS ||
             novo.coluna < 1 || novo.coluna > COLUNAS);

    // Verifica se o vetor precisa crescer
    if (*quantidade == *capacidade) {

        if (!aumentarCapacidade(veiculos, capacidade)) {
            printf("Erro ao aumentar a memoria!\n");
            return;
        }

        printf("Capacidade do vetor aumentada para %d veiculos!\n",
               *capacidade);
    }

    // Armazena o veículo no vetor
    (*veiculos)[*quantidade] = novo;

    // Marca a vaga como ocupada
    mapa[novo.fileira - 1][novo.coluna - 1] = 1;

    // Atualiza a quantidade de veículos
    (*quantidade)++;

    printf("\nVeiculo cadastrado com sucesso!\n");
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

    do {
        exibirMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarVeiculo(&veiculos, &quantidade,
                                 &capacidade, mapa);
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
