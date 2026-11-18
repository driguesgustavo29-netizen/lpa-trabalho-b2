
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

/* Le uma linha de texto */
int lerTexto(const char *mensagem, char destino[], size_t tamanho) {
    char entrada[256];

    printf("%s", mensagem);

    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return 0;
    }

    if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
        int caractere;
        while ((caractere = getchar()) != '\n' && caractere != EOF) {
        }
        return 0;
    }

    entrada[strcspn(entrada, "\n")] = '\0';

    if (strlen(entrada) >= tamanho) {
        return 0;
    }

    strcpy(destino, entrada);
    return 1;
}

/* Le um numero inteiro */
int lerInteiro(const char *mensagem) {
    char entrada[100];
    char *fim;
    long valor;

    printf("%s", mensagem);

    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return -1;
    }

    valor = strtol(entrada, &fim, 10);

    while (isspace((unsigned char)*fim)) {
        fim++;
    }

    if (fim == entrada || *fim != '\0' || valor < INT_MIN || valor > INT_MAX) {
        return -1;
    }

    return (int)valor;
}

/* Inicializa o mapa */
void inicializarMapa(int mapa[FILEIRAS][COLUNAS]) {
    for (int i = 0; i < FILEIRAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            mapa[i][j] = 0;
        }
    }
}

/* Exibe o mapa do estacionamento */
void exibirMapa(int mapa[FILEIRAS][COLUNAS]) {
    printf("\n===== MAPA DO ESTACIONAMENTO =====\n");
    printf("     ");

    for (int j = 0; j < COLUNAS; j++) {
        printf("C%d  ", j + 1);
    }

    printf("\n");

    for (int i = 0; i < FILEIRAS; i++) {
        printf("F%d   ", i + 1);

        for (int j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == 1) {
                printf("[X] ");
            } else {
                printf("[ ] ");
            }
        }

        printf("\n");
    }
}

/* Exibe o menu */
void exibirMenu(void) {
    printf("\n===== SISTEMA DE GESTAO DE ESTACIONAMENTO =====\n");
    printf("1 - Cadastrar veiculo\n");
    printf("2 - Consultar veiculo\n");
    printf("3 - Atualizar veiculo\n");
    printf("4 - Mover veiculo\n");
    printf("5 - Remover veiculo\n");
    printf("6 - Listar veiculos\n");
    printf("7 - Exibir mapa de vagas\n");
    printf("8 - Relatorio de ocupacao\n");
    printf("0 - Sair\n");
}

/* Valida e padroniza o identificador */
int validarIdentificador(char identificador[]) {
    if (strlen(identificador) != 7) {
        return 0;
    }

    for (int i = 0; i < 7; i++) {
        if (!isalnum((unsigned char)identificador[i])) {
            return 0;
        }

        identificador[i] = (char)toupper((unsigned char)identificador[i]);
    }

    return 1;
}

/* Busca um veiculo pelo identificador */
int buscarVeiculo(Veiculo veiculos[], int quantidade, const char identificador[]) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(veiculos[i].identificador, identificador) == 0) {
            return i;
        }
    }

    return -1;
}

/* Aumenta a capacidade do vetor */
int aumentarCapacidade(Veiculo **veiculos, int *capacidade) {
    int novaCapacidade = (*capacidade) * 2;

    Veiculo *temporario = realloc(
        *veiculos,
        novaCapacidade * sizeof(Veiculo)
    );

    if (temporario == NULL) {
        printf("Erro ao aumentar a capacidade de memoria.\n");
        return 0;
    }

    *veiculos = temporario;
    *capacidade = novaCapacidade;

    printf("Capacidade do vetor aumentada para %d veiculos.\n",
           novaCapacidade);

    return 1;
}

/* Cadastra um veiculo */
void cadastrarVeiculo(
    Veiculo **veiculos,
    int *quantidade,
    int *capacidade,
    int mapa[FILEIRAS][COLUNAS]
) {
    Veiculo novoVeiculo;
    char identificador[100];
    int valido = 0;

    printf("\n===== CADASTRO DE VEICULO =====\n");

    while (!valido) {
        if (!lerTexto("Identificador (7 caracteres): ",
                      identificador, sizeof(identificador))) {
            printf("Entrada muito longa. Tente novamente.\n");
            continue;
        }

        if (!validarIdentificador(identificador)) {
            printf("Identificador invalido. Digite exatamente 7 caracteres alfanumericos.\n");
            continue;
        }

        if (buscarVeiculo(*veiculos, *quantidade, identificador) != -1) {
            printf("Ja existe um veiculo com esse identificador.\n");
            continue;
        }

        valido = 1;
    }

    strcpy(novoVeiculo.identificador, identificador);

    while (!lerTexto("Descricao do veiculo (maximo 60 caracteres): ",
                     novoVeiculo.descricao,
                     sizeof(novoVeiculo.descricao))) {
        printf("Descricao muito longa. Tente novamente.\n");
    }

    do {
        novoVeiculo.categoria = lerInteiro(
            "Categoria (1 - Carro / 2 - Moto): "
        );

        if (novoVeiculo.categoria != 1 &&
            novoVeiculo.categoria != 2) {
            printf("Categoria invalida.\n");
        }
    } while (novoVeiculo.categoria != 1 &&
             novoVeiculo.categoria != 2);

    do {
        novoVeiculo.fileira = lerInteiro("Fileira (1 a 4): ");

        if (novoVeiculo.fileira < 1 || novoVeiculo.fileira > FILEIRAS) {
            printf("Fileira invalida.\n");
        }
    } while (novoVeiculo.fileira < 1 ||
             novoVeiculo.fileira > FILEIRAS);

    do {
        novoVeiculo.coluna = lerInteiro("Coluna (1 a 5): ");

        if (novoVeiculo.coluna < 1 || novoVeiculo.coluna > COLUNAS) {
            printf("Coluna invalida.\n");
        } else if (mapa[novoVeiculo.fileira - 1]
                       [novoVeiculo.coluna - 1] == 1) {
            printf("Essa vaga ja esta ocupada.\n");
            novoVeiculo.coluna = -1;
        }
    } while (novoVeiculo.coluna < 1 ||
             novoVeiculo.coluna > COLUNAS);

    if (*quantidade == *capacidade) {
        if (!aumentarCapacidade(veiculos, capacidade)) {
            return;
        }
    }

    (*veiculos)[*quantidade] = novoVeiculo;

    mapa[novoVeiculo.fileira - 1][novoVeiculo.coluna - 1] = 1;

    (*quantidade)++;

    printf("\nVeiculo cadastrado com sucesso!\n");
}

/* Lista todos os veiculos */
void listarVeiculos(Veiculo veiculos[], int quantidade) {
    printf("\n===== LISTA DE VEICULOS =====\n");

    if (quantidade == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("\nVeiculo %d\n", i + 1);
        printf("Identificador: %s\n", veiculos[i].identificador);
        printf("Descricao: %s\n", veiculos[i].descricao);
        printf("Categoria: %s\n",
               veiculos[i].categoria == 1 ? "Carro" : "Moto");
        printf("Fileira: %d\n", veiculos[i].fileira);
        printf("Coluna: %d\n", veiculos[i].coluna);
    }
}

/* Consulta um veiculo */
void consultarVeiculo(Veiculo veiculos[], int quantidade) {
    char identificador[100];

    printf("\n===== CONSULTAR VEICULO =====\n");

    if (quantidade == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        return;
    }

    if (!lerTexto("Digite o identificador: ",
                  identificador, sizeof(identificador)) ||
        !validarIdentificador(identificador)) {
        printf("Identificador invalido.\n");
        return;
    }

    int posicao = buscarVeiculo(veiculos, quantidade, identificador);

    if (posicao == -1) {
        printf("Veiculo nao encontrado.\n");
        return;
    }

    printf("\nVeiculo encontrado!\n");
    printf("Identificador: %s\n", veiculos[posicao].identificador);
    printf("Descricao: %s\n", veiculos[posicao].descricao);
    printf("Categoria: %s\n",
           veiculos[posicao].categoria == 1 ? "Carro" : "Moto");
    printf("Fileira: %d\n", veiculos[posicao].fileira);
    printf("Coluna: %d\n", veiculos[posicao].coluna);
}

/* Atualiza a descricao e a categoria */
void atualizarVeiculo(Veiculo veiculos[], int quantidade) {
    char identificador[100];
    char novaDescricao[61];
    int novaCategoria;

    printf("\n===== ATUALIZAR VEICULO =====\n");

    if (quantidade == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        return;
    }

    if (!lerTexto("Digite o identificador: ",
                  identificador, sizeof(identificador)) ||
        !validarIdentificador(identificador)) {
        printf("Identificador invalido.\n");
        return;
    }

    int posicao = buscarVeiculo(veiculos, quantidade, identificador);

    if (posicao == -1) {
        printf("Veiculo nao encontrado.\n");
        return;
    }

    while (!lerTexto("Nova descricao: ",
                     novaDescricao, sizeof(novaDescricao))) {
        printf("Descricao muito longa. Tente novamente.\n");
    }

    do {
        novaCategoria = lerInteiro(
            "Nova categoria (1 - Carro / 2 - Moto): "
        );

        if (novaCategoria != 1 && novaCategoria != 2) {
            printf("Categoria invalida.\n");
        }
    } while (novaCategoria != 1 && novaCategoria != 2);

    strcpy(veiculos[posicao].descricao, novaDescricao);
    veiculos[posicao].categoria = novaCategoria;

    printf("Veiculo atualizado com sucesso!\n");
}

/* Move um veiculo para outra vaga */
void moverVeiculo(
    Veiculo veiculos[],
    int quantidade,
    int mapa[FILEIRAS][COLUNAS]
) {
    char identificador[100];
    int novaFileira;
    int novaColuna;

    printf("\n===== MOVER VEICULO =====\n");

    if (quantidade == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        return;
    }

    if (!lerTexto("Digite o identificador do veiculo: ",
                  identificador, sizeof(identificador)) ||
        !validarIdentificador(identificador)) {
        printf("Identificador invalido.\n");
        return;
    }

    int posicao = buscarVeiculo(veiculos, quantidade, identificador);

    if (posicao == -1) {
        printf("Veiculo nao encontrado.\n");
        return;
    }

    printf("Veiculo encontrado: %s\n", veiculos[posicao].descricao);
    printf("Localizacao atual: Fileira %d, Coluna %d\n",
           veiculos[posicao].fileira,
           veiculos[posicao].coluna);

    do {
        novaFileira = lerInteiro("Nova fileira (1 a 4): ");

        if (novaFileira < 1 || novaFileira > FILEIRAS) {
            printf("Fileira invalida.\n");
        }
    } while (novaFileira < 1 || novaFileira > FILEIRAS);

    do {
        novaColuna = lerInteiro("Nova coluna (1 a 5): ");

        if (novaColuna < 1 || novaColuna > COLUNAS) {
            printf("Coluna invalida.\n");
        } else if (
            novaFileira == veiculos[posicao].fileira &&
            novaColuna == veiculos[posicao].coluna
        ) {
            printf("O veiculo ja esta nessa vaga.\n");
            return;
        } else if (mapa[novaFileira - 1][novaColuna - 1] == 1) {
            printf("Essa vaga ja esta ocupada. Escolha outra.\n");
            novaColuna = -1;
        }
    } while (novaColuna < 1 || novaColuna > COLUNAS);

    /* Libera a vaga antiga */
    mapa[veiculos[posicao].fileira - 1]
        [veiculos[posicao].coluna - 1] = 0;

    /* Ocupa a nova vaga */
    mapa[novaFileira - 1][novaColuna - 1] = 1;

    /* Atualiza a localizacao do veiculo */
    veiculos[posicao].fileira = novaFileira;
    veiculos[posicao].coluna = novaColuna;

    printf("\nVeiculo movido com sucesso!\n");
    printf("Nova localizacao: Fileira %d, Coluna %d\n",
           novaFileira, novaColuna);
}

int main(void) {
    Veiculo *veiculos = malloc(
        CAPACIDADE_INICIAL * sizeof(Veiculo)
    );

    if (veiculos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    int quantidade = 0;
    int capacidade = CAPACIDADE_INICIAL;
    int mapa[FILEIRAS][COLUNAS];

    inicializarMapa(mapa);

    int opcao;

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                cadastrarVeiculo(
                    &veiculos,
                    &quantidade,
                    &capacidade,
                    mapa
                );
                break;

            case 2:
                consultarVeiculo(veiculos, quantidade);
                break;

            case 3:
                atualizarVeiculo(veiculos, quantidade);
                break;

            case 4:
                moverVeiculo(veiculos, quantidade, mapa);
                break;

            case 5:
                printf("Remocao sera implementada.\n");
                break;

            case 6:
                listarVeiculos(veiculos, quantidade);
                break;

            case 7:
                exibirMapa(mapa);
                break;

            case 8:
                printf("Relatorio sera implementado.\n");
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    free(veiculos);

    return 0;
}
