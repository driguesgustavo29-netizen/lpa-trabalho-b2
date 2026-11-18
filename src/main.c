
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

void limparBufferEntrada() {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

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
            printf("%c  ", mapa[i][j] == 1 ? 'X' : '.');
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
}

int validarIdentificador(char identificador[]) {
    if (strlen(identificador) != 7) {
        return 0;
    }

    for (int i = 0; identificador[i] != '\0'; i++) {
        if (!isalnum((unsigned char)identificador[i])) {
            return 0;
        }

        identificador[i] =
            (char)toupper((unsigned char)identificador[i]);
    }

    return 1;
}

int buscarVeiculo(Veiculo veiculos[], int quantidade,
                  char identificador[]) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(veiculos[i].identificador, identificador) == 0) {
            return i;
        }
    }

    return -1;
}

int aumentarCapacidade(Veiculo **veiculos, int *capacidade) {
    int novaCapacidade = (*capacidade) * 2;

    Veiculo *temporario = realloc(
        *veiculos,
        novaCapacidade * sizeof(Veiculo)
    );

    if (temporario == NULL) {
        printf("\nErro ao aumentar a memoria!\n");
        return 0;
    }

    *veiculos = temporario;
    *capacidade = novaCapacidade;

    printf("\nCapacidade do vetor aumentada para %d veiculos!\n",
           novaCapacidade);

    return 1;
}

void cadastrarVeiculo(Veiculo **veiculos, int *quantidade,
                      int *capacidade,
                      int mapa[FILEIRAS][COLUNAS]) {
    Veiculo novo;
    int identificadorValido = 0;

    printf("\n===== CADASTRO DE VEICULO =====\n");

    while (!identificadorValido) {
        printf("Identificador (7 caracteres): ");

        if (fgets(novo.identificador,
                  sizeof(novo.identificador), stdin) == NULL) {
            return;
        }

        if (strchr(novo.identificador, '\n') == NULL) {
            limparBufferEntrada();
        }

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

    printf("Descricao do veiculo: ");

    if (fgets(novo.descricao, sizeof(novo.descricao), stdin) == NULL) {
        return;
    }

    if (strchr(novo.descricao, '\n') == NULL) {
        limparBufferEntrada();
    }

    novo.descricao[strcspn(novo.descricao, "\n")] = '\0';

    do {
        printf("Categoria (1 - Carro | 2 - Moto): ");

        if (scanf("%d", &novo.categoria) != 1) {
            limparBufferEntrada();
            novo.categoria = 0;
        } else {
            limparBufferEntrada();
        }

        if (novo.categoria != 1 && novo.categoria != 2) {
            printf("Categoria invalida!\n");
        }

    } while (novo.categoria != 1 && novo.categoria != 2);

    do {
        printf("Fileira (1 a 4): ");

        if (scanf("%d", &novo.fileira) != 1) {
            limparBufferEntrada();
            novo.fileira = 0;
        } else {
            limparBufferEntrada();
        }

        if (novo.fileira < 1 || novo.fileira > FILEIRAS) {
            printf("Fileira invalida!\n");
        }

    } while (novo.fileira < 1 || novo.fileira > FILEIRAS);

    do {
        printf("Coluna (1 a 5): ");

        if (scanf("%d", &novo.coluna) != 1) {
            limparBufferEntrada();
            novo.coluna = 0;
        } else {
            limparBufferEntrada();
        }

        if (novo.coluna < 1 || novo.coluna > COLUNAS) {
            printf("Coluna invalida!\n");
        } else if (mapa[novo.fileira - 1][novo.coluna - 1] == 1) {
            printf("Essa vaga ja esta ocupada!\n");
            novo.coluna = 0;
        }

    } while (novo.coluna < 1 || novo.coluna > COLUNAS);

    if (*quantidade == *capacidade) {
        if (!aumentarCapacidade(veiculos, capacidade)) {
            return;
        }
    }

    (*veiculos)[*quantidade] = novo;
    mapa[novo.fileira - 1][novo.coluna - 1] = 1;
    (*quantidade)++;

    printf("\nVeiculo cadastrado com sucesso!\n");
}

void listarVeiculos(Veiculo veiculos[], int quantidade) {
    if (quantidade == 0) {
        printf("\nNenhum veiculo cadastrado!\n");
        return;
    }

    printf("\n===== VEICULOS CADASTRADOS =====\n");

    for (int i = 0; i < quantidade; i++) {
        printf("\nIdentificador: %s\n", veiculos[i].identificador);
        printf("Descricao: %s\n", veiculos[i].descricao);
        printf("Categoria: %s\n",
               veiculos[i].categoria == 1 ? "Carro" : "Moto");
        printf("Fileira: %d\n", veiculos[i].fileira);
        printf("Coluna: %d\n", veiculos[i].coluna);
        printf("-----------------------------\n");
    }
}

void consultarVeiculo(Veiculo veiculos[], int quantidade) {
    char identificador[50];

    printf("\n===== CONSULTAR VEICULO =====\n");
    printf("Digite o identificador: ");

    if (fgets(identificador, sizeof(identificador), stdin) == NULL) {
        return;
    }

    if (strchr(identificador, '\n') == NULL) {
        limparBufferEntrada();
    }

    identificador[strcspn(identificador, "\n")] = '\0';

    if (!validarIdentificador(identificador)) {
        printf("\nIdentificador invalido!\n");
        return;
    }

    int posicao = buscarVeiculo(veiculos, quantidade, identificador);

    if (posicao == -1) {
        printf("\nVeiculo nao encontrado!\n");
        return;
    }

    printf("\n===== DADOS DO VEICULO =====\n");
    printf("Identificador: %s\n", veiculos[posicao].identificador);
    printf("Descricao: %s\n", veiculos[posicao].descricao);
    printf("Categoria: %s\n",
           veiculos[posicao].categoria == 1 ? "Carro" : "Moto");
    printf("Fileira: %d\n", veiculos[posicao].fileira);
    printf("Coluna: %d\n", veiculos[posicao].coluna);
}

void atualizarVeiculo(Veiculo veiculos[], int quantidade) {
    char identificador[50];
    int posicao;
    int novaCategoria;

    printf("\n===== ATUALIZAR VEICULO =====\n");
    printf("Digite o identificador: ");

    if (fgets(identificador, sizeof(identificador), stdin) == NULL) {
        return;
    }

    if (strchr(identificador, '\n') == NULL) {
        limparBufferEntrada();
    }

    identificador[strcspn(identificador, "\n")] = '\0';

    if (!validarIdentificador(identificador)) {
        printf("\nIdentificador invalido!\n");
        return;
    }

    posicao = buscarVeiculo(veiculos, quantidade, identificador);

    if (posicao == -1) {
        printf("\nVeiculo nao encontrado!\n");
        return;
    }

    printf("Nova descricao: ");

    if (fgets(veiculos[posicao].descricao,
              sizeof(veiculos[posicao].descricao), stdin) == NULL) {
        return;
    }

    if (strchr(veiculos[posicao].descricao, '\n') == NULL) {
        limparBufferEntrada();
    }

    veiculos[posicao].descricao[
        strcspn(veiculos[posicao].descricao, "\n")
    ] = '\0';

    do {
        printf("Nova categoria (1 - Carro | 2 - Moto): ");

        if (scanf("%d", &novaCategoria) != 1) {
            limparBufferEntrada();
            novaCategoria = 0;
        } else {
            limparBufferEntrada();
        }

        if (novaCategoria != 1 && novaCategoria != 2) {
            printf("Categoria invalida!\n");
        }

    } while (novaCategoria != 1 && novaCategoria != 2);

    veiculos[posicao].categoria = novaCategoria;

    printf("\nVeiculo atualizado com sucesso!\n");
}

int main() {
    int mapa[FILEIRAS][COLUNAS];
    int quantidade = 0;
    int capacidade = CAPACIDADE_INICIAL;
    int opcao = -1;

    Veiculo *veiculos = malloc(capacidade * sizeof(Veiculo));

    if (veiculos == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    inicializarMapa(mapa);

    do {
        exibirMenu();
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparBufferEntrada();
            printf("\nOpcao invalida!\n");
            opcao = -1;
            continue;
        }

        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarVeiculo(&veiculos, &quantidade,
                                 &capacidade, mapa);
                break;

            case 2:
                consultarVeiculo(veiculos, quantidade);
                break;

            case 3:
                atualizarVeiculo(veiculos, quantidade);
                break;

            case 4:
                printf("\nMovimentacao sera implementada.\n");
                break;

            case 5:
                printf("\nRemocao sera implementada.\n");
                break;

            case 6:
                listarVeiculos(veiculos, quantidade);
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
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    free(veiculos);

    return 0;
}

