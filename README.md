# Sistema de Gestão de Estacionamento

**Disciplina:** Lógica de Programação e Algoritmos  
**Semestre:** 2026/2  
**Trabalho:** Trabalho do 2º Bimestre – Sistema de Gestão de Estacionamento

## 1. Autor

- **Nome:** Gustavo da Silva Rodrigues
- **GitHub:** [driguesgustavo29-netizen](https://github.com/driguesgustavo29-netizen)
- **Repositório:** https://github.com/driguesgustavo29-netizen/lpa-trabalho-b2

**Modalidade:** Desenvolvimento individual.

## 2. Descrição do projeto

O Sistema de Gestão de Estacionamento foi desenvolvido em linguagem C para administrar as vagas de um estacionamento com capacidade para 20 veículos, distribuídos em quatro fileiras e cinco colunas.

O programa funciona pelo terminal e permite cadastrar, consultar, atualizar, movimentar, remover e listar veículos, além de apresentar o mapa das vagas e um relatório de ocupação.

Os dados são mantidos em memória durante a execução do programa, sem utilização de banco de dados ou armazenamento permanente.

## 3. Funcionalidades implementadas

1. Cadastro de veículos.
2. Consulta de veículos pelo identificador.
3. Atualização da descrição e categoria.
4. Movimentação de veículos entre vagas.
5. Remoção de veículos e liberação da vaga.
6. Listagem dos veículos cadastrados.
7. Exibição do mapa de vagas.
8. Relatório de ocupação do estacionamento.
9. Encerramento do programa com liberação da memória.

## 4. Estruturas de dados utilizadas

### 4.1 Struct

Foi utilizada a estrutura `struct` para representar os dados de cada veículo:

- Identificador de sete caracteres;
- Descrição de até 60 caracteres;
- Categoria do veículo;
- Número da fileira;
- Número da coluna.

### 4.2 Matriz

Foi utilizada uma matriz de inteiros com quatro linhas e cinco colunas para representar as vagas.

- `0`: vaga livre;
- `1`: vaga ocupada.

A matriz é atualizada sempre que um veículo é cadastrado, movimentado ou removido.

### 4.3 Vetor dinâmico

Os veículos são armazenados em um vetor dinâmico, utilizando alocação de memória com `malloc`, ampliação com `realloc` e liberação com `free`.

A capacidade inicial do vetor é de dois veículos. Quando essa capacidade é atingida, o sistema dobra o espaço disponível.

A quantidade representa o número de veículos cadastrados, enquanto a capacidade representa o espaço atualmente reservado na memória.

## 5. Organização do código

O projeto possui a seguinte organização:

```text
lpa-trabalho-b2/
│
├── src/
│   └── main.c
│
└── README.md
```

O código está organizado nas seguintes funções:

- `lerTexto()` e `lerInteiro()`: leitura e validação de entradas.
- `inicializarMapa()`: inicialização das vagas.
- `exibirMapa()`: apresentação do mapa.
- `exibirMenu()`: apresentação das opções.
- `validarIdentificador()`: validação e padronização do identificador.
- `buscarVeiculo()`: localização de veículos.
- `aumentarCapacidade()`: ampliação do vetor dinâmico.
- `cadastrarVeiculo()`: cadastro de veículos.
- `consultarVeiculo()`: consulta de registros.
- `atualizarVeiculo()`: atualização de informações.
- `moverVeiculo()`: movimentação entre vagas.
- `removerVeiculo()`: remoção de registros.
- `listarVeiculos()`: listagem dos veículos.
- `relatorioOcupacao()`: cálculo dos dados de ocupação.
- `main()`: controle principal do programa.

## 6. Como compilar e executar

É necessário possuir um compilador GCC instalado.

Na pasta principal do projeto, execute:

**Compilação:**

```bash
gcc -std=c11 -Wall -Wextra -pedantic src/main.c -o estacionamento
```

**Execução:**

```bash
./estacionamento
```

## 7. Testes realizados

Os testes foram executados manualmente no terminal.

| Teste | Operação | Resultado observado | Status |
|---|---|---|---|
| T01 | Exibir estacionamento vazio | 20 vagas livres e mapa correto | Aprovado |
| T02 | Cadastrar veículo válido | Veículo cadastrado e vaga ocupada | Aprovado |
| T03 | Cadastrar identificador duplicado em letras minúsculas | Cadastro recusado por duplicidade | Aprovado |
| T04 | Tentar utilizar vaga ocupada ou índice inválido | Operação recusada sem alteração indevida | Aprovado |
| T05 | Cadastrar o terceiro veículo | Vetor ampliado de capacidade 2 para 4 | Aprovado |
| T06 | Atualizar informações de veículo | Descrição e categoria atualizadas | Aprovado |
| T07 | Mover veículo para outra vaga livre | Origem liberada e destino ocupado | Aprovado |
| T08 | Remover veículo | Registro removido e vaga liberada | Aprovado |
| T09 | Tentar cadastrar o 21º veículo | Cadastro recusado com estacionamento lotado | Aprovado |

### 7.1 Verificação de ocupação máxima

No teste de lotação, foram cadastrados 20 veículos.

O relatório apresentou:

- Total de vagas: 20;
- Vagas ocupadas: 20;
- Vagas disponíveis: 0;
- Percentual de ocupação: 100,00%;
- Total de veículos cadastrados: 20.

A tentativa de cadastrar o 21º veículo foi recusada corretamente.

## 8. Responsabilidade pelo desenvolvimento

O desenvolvimento do projeto foi realizado individualmente por Gustavo da Silva Rodrigues.

As atividades envolveram a implementação das funcionalidades, organização do código, compilação, execução e testes do sistema.

O repositório foi utilizado para registrar a evolução do projeto. Não houve integração de branches de outros integrantes, pois o desenvolvimento foi individual.

## 9. Utilização de inteligência artificial

O ChatGPT foi utilizado como ferramenta de apoio durante o desenvolvimento.

Sua utilização teve como objetivos auxiliar na compreensão dos conceitos de programação em C, identificar e corrigir erros de compilação, revisar funções, orientar a implementação de estruturas de dados e sugerir procedimentos de teste.

Entre os exemplos de solicitações realizadas estão:

- Solicitação de explicação e correção de erros de compilação em C.
- Orientação para implementar e revisar cadastro, consulta, atualização, movimentação e remoção de veículos.
- Apoio na utilização de `struct`, matriz, ponteiros e alocação dinâmica de memória.
- Orientação para testar duplicidade de identificadores, expansão do vetor e lotação máxima.

O código
