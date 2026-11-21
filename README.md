# lpa-trabalho-b2

# Sistema de Gestão de Estacionamento

## 1. Sobre o projeto

Este projeto foi desenvolvido para a disciplina de Linguagem de Programação, utilizando a linguagem C.

O sistema tem como finalidade realizar o gerenciamento de um estacionamento, permitindo controlar os veículos cadastrados, suas respectivas vagas e a ocupação do espaço.

O estacionamento possui capacidade para até 20 veículos, organizados em uma matriz de 4 fileiras por 5 colunas.

## 2. Objetivo

Desenvolver uma aplicação em linguagem C que permita gerenciar as operações de um estacionamento, aplicando conceitos de programação estruturada, funções, structs, matrizes, vetores dinâmicos e gerenciamento de memória.

## 3. Funcionalidades

O sistema possui as seguintes funcionalidades:

- Cadastro de veículos.
- Busca de veículos pelo identificador.
- Consulta dos dados de veículos cadastrados.
- Atualização da descrição e categoria.
- Movimentação de veículos entre vagas.
- Remoção de veículos cadastrados.
- Listagem de todos os veículos.
- Exibição do mapa do estacionamento.
- Relatório de ocupação.
- Validação das informações fornecidas pelo usuário.
- Verificação de consistência entre a matriz e o vetor de veículos.
- Aumento automático da capacidade do vetor dinâmico.

## 4. Organização do estacionamento

O estacionamento possui:

- 4 fileiras.
- 5 colunas.
- 20 vagas disponíveis.

O mapa utiliza os seguintes símbolos:

| Símbolo | Significado |
|---|---|
| `.` | Vaga livre |
| `X` | Vaga ocupada |

## 5. Tecnologias utilizadas

- Linguagem C.
- Padrão C11.
- Compilador GCC.
- Git.
- GitHub.

## 6. Estruturas de dados utilizadas

### 6.1 Matriz

Foi utilizada uma matriz de inteiros com 4 linhas e 5 colunas para representar as vagas do estacionamento.

- `0`: vaga livre.
- `1`: vaga ocupada.

### 6.2 Struct

Foi criada uma estrutura chamada `Veiculo`, responsável por armazenar as informações de cada veículo:

- `identificador`: código de identificação com 7 caracteres alfanuméricos.
- `descricao`: descrição do veículo, com até 60 caracteres.
- `categoria`: identifica o tipo de veículo.
- `fileira`: representa a fileira onde o veículo está estacionado.
- `coluna`: representa a coluna onde o veículo está estacionado.

As categorias disponíveis são:

- `1`: Carro.
- `2`: Moto.

### 6.3 Vetor dinâmico

O sistema utiliza um vetor dinâmico de estruturas `Veiculo`, iniciado com capacidade para 2 registros.

Quando a capacidade é atingida, o sistema aumenta automaticamente o espaço disponível utilizando `realloc`, respeitando o limite máximo de 20 veículos.

Para o gerenciamento da memória dinâmica, são utilizadas as funções `malloc`, `realloc` e `free`.

## 7. Principais funções do sistema

As funções são responsáveis por organizar as operações do programa e facilitar a manutenção do código.

| Função | Responsabilidade |
|---|---|
| `cadastrarVeiculo()` | Realiza o cadastro de um novo veículo. |
| `buscarVeiculo()` | Procura um veículo pelo seu identificador e retorna sua posição no vetor. |
| `consultarVeiculo()` | Consulta e apresenta os dados de um veículo cadastrado. |
| `atualizarVeiculo()` | Modifica a descrição ou categoria de um veículo. |
| `moverVeiculo()` | Altera a posição de um veículo no estacionamento. |
| `removerVeiculo()` | Remove um veículo e libera sua vaga. |
| `listarVeiculos()` | Exibe todos os veículos cadastrados. |
| `exibirMapa()` | Apresenta visualmente a situação das vagas. |
| `relatorioOcupacao()` | Apresenta informações sobre a ocupação do estacionamento. |
| `verificarConsistencia()` | Verifica se os dados da matriz e do vetor estão sincronizados. |
| `inicializarMapa()` | Inicializa todas as vagas como livres. |
| `aumentarCapacidade()` | Aumenta a capacidade do vetor dinâmico quando necessário. |
| `validarIdentificador()` | Verifica se o identificador possui sete caracteres alfanuméricos e converte as letras para maiúsculas. |
| `validarDescricao()` | Verifica se a descrição possui entre 1 e 60 caracteres. |
| `lerTexto()` | Realiza a leitura de textos pelo teclado. |
| `lerInteiro()` | Lê e valida valores inteiros informados pelo usuário. |
| `exibirMenu()` | Apresenta as opções disponíveis no sistema. |

## 8. Menu do sistema

O sistema disponibiliza as seguintes opções:

1. Cadastrar veículo.
2. Consultar veículo.
3. Atualizar veículo.
4. Movimentar veículo.
5. Remover veículo.
6. Listar veículos.
7. Exibir mapa do estacionamento.
8. Relatório de ocupação.
0. Sair.

## 9. Como executar

### 9.1 Pré-requisitos

É necessário possuir:

- GCC instalado.
- Terminal ou prompt de comando.
- Arquivo `main.c` do projeto.

### 9.2 Compilação

Dentro da pasta do projeto, execute:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o estacionamento.exe
```

### 9.3 Execução no Windows

```bash
.\estacionamento.exe
```

### 9.4 Execução no Linux

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o estacionamento
./estacionamento
```

## 10. Testes do sistema

Os seguintes cenários foram definidos para verificar o funcionamento das funcionalidades do sistema.

| Nº | Cenário | Dados e procedimento | Resultado esperado |
|---|---|---|---|
| 1 | Cadastro válido | Informar ID válido, descrição, categoria e vaga livre. | Veículo cadastrado corretamente. |
| 2 | ID duplicado | Tentar cadastrar outro veículo com um ID já existente. | Cadastro recusado. |
| 3 | ID inválido | Informar um ID com quantidade ou formato incorreto. | Entrada recusada. |
| 4 | Descrição inválida | Informar uma descrição vazia ou acima de 60 caracteres. | Entrada recusada. |
| 5 | Crescimento do vetor | Cadastrar mais de dois veículos. | Capacidade do vetor aumentada automaticamente. |
| 6 | Busca de veículo | Informar o ID de um veículo cadastrado. | Dados do veículo apresentados. |
| 7 | Busca inexistente | Informar um ID que não está cadastrado. | Mensagem informando que o veículo não foi encontrado. |
| 8 | Atualização | Alterar a descrição ou categoria de um veículo. | Informações atualizadas corretamente. |
| 9 | Movimentação | Transferir um veículo para uma vaga livre. | Nova posição registrada corretamente. |
| 10 | Vaga ocupada | Tentar movimentar um veículo para uma vaga já ocupada. | Operação recusada. |
| 11 | Remoção | Remover um veículo pelo ID. | Veículo excluído e vaga liberada. |
| 12 | Estacionamento cheio | Tentar cadastrar um veículo com as 20 vagas ocupadas. | Cadastro recusado. |
| 13 | Relatório | Consultar o relatório com veículos cadastrados. | Quantidades e percentual de ocupação apresentados corretamente. |
| 14 | Consistência | Realizar operações de cadastro, movimentação e remoção. | Matriz e vetor permanecem sincronizados. |

## 11. Integrante

- **Nome:** Matheus Victor Galvão da Silva

## 12. Desenvolvimento

O projeto foi desenvolvido individualmente, abrangendo as etapas de planejamento, implementação, organização das estruturas de dados, criação das funcionalidades, validação das entradas, gerenciamento de memória dinâmica, testes e documentação.

## 13. Fontes e ferramentas de apoio

Durante o desenvolvimento, foram utilizados materiais didáticos disponibilizados na disciplina, pesquisas e ferramentas de apoio para consulta e esclarecimento de dúvidas.

Também foi utilizada inteligência artificial generativa como ferramenta de apoio para compreender conceitos de programação, auxiliar na implementação de funcionalidades, revisar trechos de código e identificar possíveis erros.

A implementação, os testes e as decisões finais do projeto devem ser conferidos pelo responsável antes da entrega.

## 14. Informações acadêmicas

**Disciplina:** Lógica de Programação

**Trabalho:** Sistema de Gestão de Estacionamento

**Semestre:** 2026/2
