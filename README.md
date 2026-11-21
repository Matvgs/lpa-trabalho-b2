# Sistema de Gestão de Estacionamento

**Disciplina:** Lógica de Programação e Algoritmos
**Semestre:** 2026/2
**Trabalho:** Trabalho do 2º Bimestre – Sistema de Gestão de Estacionamento

## 1. Integrante

| Nome | Perfil GitHub |
| ---- | ------------- |
| Matheus Victor Galvão da Silva | [@Matvgs](https://github.com/Matvgs) |

## 2. Descrição do cenário e escopo

Sistema de terminal, escrito em C, que controla vagas e veículos de um estacionamento fictício com **4 fileiras e 5 colunas (20 vagas)**.

O programa começa sem veículos cadastrados, recebe operações por um menu e conserva os dados somente enquanto estiver aberto. Não há persistência em arquivos. Os identificadores e as descrições usados nos testes são fictícios.

## 3. Funcionalidades e menu

| Opção | Funcionalidade |
| ----- | -------------- |
| 1 | Cadastrar veículo |
| 2 | Consultar veículo por identificador |
| 3 | Atualizar descrição ou categoria |
| 4 | Mover veículo para outra vaga |
| 5 | Remover veículo |
| 6 | Listar veículos cadastrados |
| 7 | Exibir mapa de vagas |
| 8 | Exibir relatório da ocupação |
| 0 | Encerrar (libera a memória dinâmica) |

Regras de validação implementadas:

- Identificador com exatamente 7 caracteres alfanuméricos (A–Z e 0–9). Letras minúsculas são convertidas para maiúsculas, portanto `abc1d23` e `ABC1D23` são o mesmo veículo (duplicidade recusada).
- Descrição não vazia, com até 60 caracteres (não é truncada silenciosamente).
- Categoria: 1 = carro, 2 = moto.
- Fileira de 1 a 4 e coluna de 1 a 5, validadas antes de acessar a matriz.
- Vaga ocupada recusa cadastro e movimentação sem alterar o estado.
- Identificador inexistente em consulta, atualização, movimentação ou remoção: informa "não localizado" e mantém o estado.
- Estacionamento lotado (20 vagas): novos cadastros são recusados.
- Falha em `realloc`: o cadastro é cancelado e a coleção e o mapa continuam íntegros.
- Opção de menu inexistente: avisa e exibe o menu novamente.
- Leitura de strings com tamanho limitado (sem `gets`).

## 4. Estruturas utilizadas

### 4.1 Matriz 4 × 5

Matriz de inteiros que representa o mapa de vagas: `0` = livre e `1` = ocupada. Todas as posições começam em `0`. É percorrida com laços aninhados na exibição do mapa e na contagem de ocupação.

No mapa exibido ao usuário, `.` indica vaga livre e `X` indica vaga ocupada. A identificação começa em 1 (F1 a F4 e C1 a C5), e o programa converte para os índices internos 0 a 3 e 0 a 4.

### 4.2 Struct `Veiculo`

| Campo | Descrição |
| ----- | --------- |
| `identificador` | 7 caracteres alfanuméricos, único e não alterável após o cadastro |
| `descricao` | texto de 1 a 60 caracteres |
| `categoria` | 1 = carro, 2 = moto |
| `fileira` | fileira da vaga ocupada |
| `coluna` | coluna da vaga ocupada |

### 4.3 Coleção dinâmica (quantidade e capacidade)

Vetor de `Veiculo` alocado com `malloc`, com **capacidade inicial de 2 registros**. O programa mantém a **quantidade** de registros em uso e a **capacidade** total reservada.

Quando a coleção está cheia, a capacidade é **duplicada** com `realloc`, usando um ponteiro temporário para não perder a referência original em caso de falha. Na remoção, os registros seguintes são deslocados, sem deixar lacunas. No encerramento, o bloco é liberado com `free`.

A capacidade do vetor não altera o número de vagas físicas, que é sempre 20.

**Consistência:** a qualquer momento, o número de registros ativos é igual ao número de células com valor 1 na matriz e ao número de vagas ocupadas no relatório.

## 5. Modularização

O projeto usa um único arquivo-fonte, `main.c`, com as responsabilidades divididas em funções:

| Função | Responsabilidade |
| ------ | ---------------- |
| `exibirMenu()` | Apresenta as opções do menu |
| `inicializarMapa()` | Inicializa todas as vagas como livres |
| `lerTexto()` / `lerInteiro()` | Leitura segura e validação das entradas |
| `validarIdentificador()` | Valida os 7 caracteres e converte para maiúsculas |
| `validarDescricao()` | Valida o tamanho da descrição |
| `buscarVeiculo()` | Procura um veículo pelo identificador e retorna sua posição no vetor |
| `aumentarCapacidade()` | Duplica a capacidade do vetor com `realloc` verificado |
| `cadastrarVeiculo()` | Cadastro com todas as validações |
| `consultarVeiculo()` | Exibe os dados de um veículo |
| `atualizarVeiculo()` | Altera descrição e/ou categoria |
| `moverVeiculo()` | Move o veículo e sincroniza matriz e registro |
| `removerVeiculo()` | Libera a vaga e remove o registro sem lacunas |
| `listarVeiculos()` | Lista os veículos ativos |
| `exibirMapa()` | Mostra a matriz com legenda |
| `relatorioOcupacao()` | Total, ocupadas, livres, percentual, carros e motos |
| `verificarConsistencia()` | Confere se matriz e vetor estão sincronizados |

## 6. Compilação e execução

Pré-requisitos: GCC (com suporte a C11) e um terminal.

Compilação (na pasta do projeto, que contém o `main.c`):

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o estacionamento
```

Execução no Linux ou macOS:

```bash
./estacionamento
```

Execução no Windows (PowerShell ou Prompt de Comando):

```powershell
.\estacionamento.exe
```

No Windows o GCC gera `estacionamento.exe`. Os executáveis não fazem parte do repositório e são ignorados pelo `.gitignore`.

## 7. Casos de teste

| Nº | Teste | Entrada / operação | Resultado esperado | Resultado observado | Situação |
| -- | ----- | ------------------ | ------------------ | ------------------- | -------- |
| 1 | T01 – Estacionamento vazio | Iniciar o programa e usar as opções 6, 7 e 8 | Listagem vazia, mapa todo livre e ocupação de 0,00% | Listagem vazia, mapa todo livre e ocupação de 0,00% | Aprovado |
| 2 | T02 – Cadastro válido | Cadastrar `ABC1D23`, "Carro azul", categoria 1, F1/C1 | Registro aparece na consulta e na listagem; F1/C1 ocupada | Registro aparece na consulta e na listagem; F1/C1 ocupada | Aprovado |
| 3 | T03 – Duplicidade sem distinção de caixa | Com `ABC1D23` cadastrado, tentar cadastrar `abc1d23` | Cadastro recusado por duplicidade; contagem e mapa inalterados | Cadastro recusado por duplicidade; contagem e mapa inalterados | Aprovado |
| 4 | T04 – Vaga ocupada / índice inválido | Cadastrar em vaga já ocupada; informar fileira 5 ou coluna 0 | Recusa sem alteração do estado | Recusa sem alteração do estado | Aprovado |
| 5 | T05 – Crescimento dinâmico | Cadastrar 3 veículos seguidos | Capacidade passa de 2 para 4 e os registros anteriores são preservados | Capacidade passa de 2 para 4 e os registros anteriores são preservados | Aprovado |
| 6 | T06 – Atualização | Alterar descrição e/ou categoria de `ABC1D23` | Dados alterados, sem criar um segundo registro | Dados alterados, sem criar um segundo registro | Aprovado |
| 7 | T07 – Movimentação | Mover `ABC1D23` de F1/C1 para F2/C3 (livre) | F1/C1 fica livre e F2/C3 ocupada; registro atualizado | F1/C1 fica livre e F2/C3 ocupada; registro atualizado | Aprovado |
| 8 | T07b – Movimentação para vaga ocupada | Mover `ABC1D23` para uma vaga ocupada | Operação recusada; veículo e mapa inalterados | Operação recusada; veículo e mapa inalterados | Aprovado |
| 9 | T08 – Remoção | Remover `XYZ9K87` | Registro some da listagem e a vaga é liberada | Registro some da listagem e a vaga é liberada | Aprovado |
| 10 | T09 – Lotação | Ocupar as 20 vagas e tentar a 21ª inclusão | 21º cadastro recusado por lotação | 21º cadastro recusado por lotação | Aprovado |
| 11 | T10 – Encerramento | Escolher a opção 0 | Programa encerra normalmente, com a memória da coleção liberada | Programa encerra normalmente, com a memória da coleção liberada | Aprovado |
| 12 | Relatório | Cenário do roteiro: 2 carros e 0 motos após as operações | 20 vagas; 2 ocupadas; 18 livres; 10,00%; 2 carros; 0 motos | 20 vagas; 2 ocupadas; 18 livres; 10,00%; 2 carros; 0 motos | Aprovado/Falhou>` |

## 8. Responsabilidades e integração

O trabalho foi realizado individualmente por Matheus Victor Galvão da Silva, que ficou responsável por todas as etapas: planejamento, implementação, validações, gerenciamento de memória dinâmica, testes e documentação.

**Branches e integração:** Desenvolvimento foi feito direto na main

## 9. Limitações conhecidas

Nenhuma limitação conhecida até o momento da entrega.

## 10. Declaração individual de autoria e uso de IA

**Matheus Victor Galvão da Silva**

- **(a) Funcionalidades em que atuei:** todas as funcionalidades do sistema.
- **(b) Usei IA generativa?** Sim.
- **(c) Ferramentas, finalidade e sugestões incorporadas:**
  - Ferramenta: Claude
  - Finalidade: concertar pequenos erros de codigo e lógica
  - Exemplos de solicitações: "nessa parte o ponteiro deve ser = ou =>?", "posso colocar colocar as funçoes antei de declarar o int main?", "posso declarar variaveis dentro da operação?".
  - Sugestões incorporadas: aproveitei a resposta das peguntas e incrementtei ao código

## 11. Referências

- Materiais didáticos da disciplina.
