
# Sistema de Gestão de Estacionamento

Projeto desenvolvido em linguagem C para a disciplina de Linguagem de Programação e Algoritmos (LPA).

## Descrição

O sistema permite gerenciar um estacionamento com capacidade para 20 veículos, distribuídos em 4 fileiras e 5 colunas.

O programa oferece funcionalidades para cadastrar, consultar, atualizar, mover e remover veículos, além de apresentar o mapa de vagas e um relatório de ocupação.

## Funcionalidades

1. Cadastrar veículo;
2. Consultar veículo pelo identificador;
3. Atualizar descrição e categoria;
4. Mover veículo para outra vaga;
5. Remover veículo;
6. Listar veículos cadastrados;
7. Exibir mapa de vagas;
8. Gerar relatório de ocupação.

## Regras do sistema

- O estacionamento possui 20 vagas.
- Cada veículo possui um identificador de 7 caracteres alfanuméricos.
- A descrição do veículo aceita até 60 caracteres.
- As categorias são:
  - 1 – Carro
  - 2 – Moto
- Não é permitido cadastrar identificadores duplicados.
- Não é permitido ocupar uma vaga que já esteja preenchida.
- O sistema valida as fileiras e colunas disponíveis.

## Estruturas utilizadas

O projeto utiliza:

- `struct` para representar os veículos;
- Vetor dinâmico para armazenar os veículos cadastrados;
- `malloc`, `realloc` e `free` para gerenciamento de memória;
- Matriz para representar as vagas do estacionamento;
- Funções para organizar as operações do sistema;
- Ponteiros para manipulação dos dados.

## Compilação

Para compilar o programa utilizando GCC:

```bash
gcc -std=c11 -Wall -Wextra -pedantic src/main.c -o estacionamento
```

## Execução

Após a compilação, execute:

```bash
./estacionamento
```

## Organização do projeto

```text
lpa-trabalho-b2/
├── src/
│   └── main.c
└── README.md
```

## Capacidade do estacionamento

| Informação | Quantidade |
|---|---:|
| Fileiras | 4 |
| Colunas | 5 |
| Total de vagas | 20 |
