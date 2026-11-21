
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

#define FILEIRAS 4
#define COLUNAS 5
#define CAPACIDADE_INICIAL 2
#define LIMITE_VEICULOS 20

typedef struct {
    char identificador[8];
    char descricao[61];
    int categoria;
    int fileira;
    int coluna;
} Veiculo;

/* Prototipos */
void inicializarMapa(int mapa[FILEIRAS][COLUNAS]);
void exibirMapa(int mapa[FILEIRAS][COLUNAS]);
void exibirMenu(void);
int lerTexto(char texto[], int tamanho);
int lerInteiro(const char mensagem[], int *valor);
int validarIdentificador(char identificador[]);
int buscarVeiculo(Veiculo veiculos[], int quantidade, const char identificador[]);
int aumentarCapacidade(Veiculo **veiculos, int *capacidade);

void cadastrarVeiculo(
    Veiculo **veiculos,
    int *quantidade,
    int *capacidade,
    int mapa[FILEIRAS][COLUNAS]
);

void consultarVeiculo(Veiculo veiculos[], int quantidade);
void listarVeiculos(Veiculo veiculos[], int quantidade);
void atualizarVeiculo(Veiculo veiculos[], int quantidade);

void moverVeiculo(
    Veiculo veiculos[],
    int quantidade,
    int mapa[FILEIRAS][COLUNAS]
);

/* Inicializa o mapa */
void inicializarMapa(int mapa[FILEIRAS][COLUNAS]) {
    int i, j;

    for (i = 0; i < FILEIRAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            mapa[i][j] = 0;
        }
    }
}

/* Exibe o mapa */
void exibirMapa(int mapa[FILEIRAS][COLUNAS]) {
    int i, j;

    printf("\n===== MAPA DO ESTACIONAMENTO =====\n");
    printf("    ");

    for (j = 0; j < COLUNAS; j++) {
        printf("C%d ", j + 1);
    }

    printf("\n");

    for (i = 0; i < FILEIRAS; i++) {
        printf("F%d  ", i + 1);

        for (j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == 1) {
                printf("X  ");
            } else {
                printf(".  ");
            }
        }

        printf("\n");
    }
}

/* Exibe o menu */
void exibirMenu(void) {
    printf("\n===== SISTEMA DE ESTACIONAMENTO =====\n");
    printf("1 - Cadastrar veiculo\n");
    printf("2 - Consultar veiculo\n");
    printf("3 - Atualizar veiculo\n");
    printf("4 - Mover veiculo\n");
    printf("5 - Remover veiculo\n");
    printf("6 - Listar veiculos\n");
    printf("7 - Exibir mapa\n");
    printf("8 - Relatorio de ocupacao\n");
    printf("0 - Sair\n");
}

/* Le texto caractere por caractere */
int lerTexto(char texto[], int tamanho) {
    int caractere;
    int quantidade = 0;
    int entradaLonga = 0;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        if (quantidade < tamanho - 1) {
            texto[quantidade] = (char)caractere;
            quantidade++;
        } else {
            entradaLonga = 1;
        }
    }

    texto[quantidade] = '\0';

    if (caractere == EOF && quantidade == 0 && !entradaLonga) {
        return 0;
    }

    if (entradaLonga) {
        printf("Entrada muito longa!\n");
        return -1;
    }

    return 1;
}

/* Le um numero inteiro */
int lerInteiro(const char mensagem[], int *valor) {
    char entrada[100];
    char *fim;
    long numero;
    int resultado;

    printf("%s", mensagem);

    resultado = lerTexto(entrada, sizeof(entrada));

    if (resultado != 1) {
        return 0;
    }

    errno = 0;
    numero = strtol(entrada, &fim, 10);

    if (entrada == fim || errno == ERANGE ||
        numero < INT_MIN || numero > INT_MAX) {
        printf("Valor invalido!\n");
        return 0;
    }

    while (isspace((unsigned char)*fim)) {
        fim++;
    }

    if (*fim != '\0') {
        printf("Digite somente numeros inteiros!\n");
        return 0;
    }

    *valor = (int)numero;
    return 1;
}

/* Valida o identificador */
int validarIdentificador(char identificador[]) {
    int i;

    if (strlen(identificador) != 7) {
        return 0;
    }

    for (i = 0; i < 7; i++) {
        identificador[i] = (char)toupper(
            (unsigned char)identificador[i]
        );

        if (!isalnum((unsigned char)identificador[i])) {
            return 0;
        }
    }

    return 1;
}

/* Busca um veiculo pelo identificador */
int buscarVeiculo(
    Veiculo veiculos[],
    int quantidade,
    const char identificador[]
) {
    int i;

    for (i = 0; i < quantidade; i++) {
        if (strcmp(veiculos[i].identificador, identificador) == 0) {
            return i;
        }
    }

    return -1;
}

/* Aumenta a capacidade do vetor */
int aumentarCapacidade(Veiculo **veiculos, int *capacidade) {
    int novaCapacidade;
    Veiculo *temporario;

    if (*capacidade >= LIMITE_VEICULOS) {
        return 0;
    }

    novaCapacidade = *capacidade * 2;

    if (novaCapacidade > LIMITE_VEICULOS) {
        novaCapacidade = LIMITE_VEICULOS;
    }

    temporario = realloc(
        *veiculos,
        novaCapacidade * sizeof(Veiculo)
    );

    if (temporario == NULL) {
        printf("Erro ao aumentar a memoria!\n");
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
    char identificadorTemp[100];
    char descricaoTemp[100];
    int resultado;

    if (*quantidade >= LIMITE_VEICULOS) {
        printf("\nEstacionamento sem vagas para novos cadastros!\n");
        return;
    }

    printf("\nDigite o identificador (7 caracteres): ");

    resultado = lerTexto(identificadorTemp, sizeof(identificadorTemp));

    if (resultado != 1) {
        printf("Cadastro cancelado.\n");
        return;
    }

    if (!validarIdentificador(identificadorTemp)) {
        printf("Identificador invalido! Use exatamente 7 letras ou numeros.\n");
        return;
    }

    strcpy(novoVeiculo.identificador, identificadorTemp);

    if (buscarVeiculo(
        *veiculos,
        *quantidade,
        novoVeiculo.identificador
    ) != -1) {
        printf("Esse identificador ja esta cadastrado!\n");
        return;
    }

    printf("Digite a descricao do veiculo: ");

    resultado = lerTexto(descricaoTemp, sizeof(descricaoTemp));

    if (resultado != 1) {
        printf("Cadastro cancelado.\n");
        return;
    }

    if (strlen(descricaoTemp) == 0) {
        printf("A descricao nao pode ficar vazia!\n");
        return;
    }

    if (strlen(descricaoTemp) > 60) {
        printf("A descricao deve ter no maximo 60 caracteres!\n");
        return;
    }

    strcpy(novoVeiculo.descricao, descricaoTemp);

    if (!lerInteiro(
        "Categoria (1 - Carro / 2 - Moto): ",
        &novoVeiculo.categoria
    )) {
        printf("Cadastro cancelado.\n");
        return;
    }

    if (novoVeiculo.categoria != 1 && novoVeiculo.categoria != 2) {
        printf("Categoria invalida!\n");
        return;
    }

    if (!lerInteiro("Fileira (1 a 4): ", &novoVeiculo.fileira)) {
        printf("Cadastro cancelado.\n");
        return;
    }

    if (novoVeiculo.fileira < 1 || novoVeiculo.fileira > FILEIRAS) {
        printf("Fileira invalida!\n");
        return;
    }

    if (!lerInteiro("Coluna (1 a 5): ", &novoVeiculo.coluna)) {
        printf("Cadastro cancelado.\n");
        return;
    }

    if (novoVeiculo.coluna < 1 || novoVeiculo.coluna > COLUNAS) {
        printf("Coluna invalida!\n");
        return;
    }

    if (mapa[novoVeiculo.fileira - 1][novoVeiculo.coluna - 1] == 1) {
        printf("Essa vaga ja esta ocupada!\n");
        return;
    }

    if (*quantidade == *capacidade) {
        if (!aumentarCapacidade(veiculos, capacidade)) {
            printf("Nao foi possivel realizar o cadastro.\n");
            return;
        }
    }

    (*veiculos)[*quantidade] = novoVeiculo;

    mapa[novoVeiculo.fileira - 1][novoVeiculo.coluna - 1] = 1;

    (*quantidade)++;

    printf("\nVeiculo cadastrado com sucesso!\n");
}

/* Consulta um veiculo pelo identificador */
void consultarVeiculo(Veiculo veiculos[], int quantidade) {
    char identificador[100];
    int resultado;
    int indice;

    if (quantidade == 0) {
        printf("\nNao existem veiculos cadastrados.\n");
        return;
    }

    printf("\nDigite o identificador do veiculo: ");

    resultado = lerTexto(identificador, sizeof(identificador));

    if (resultado != 1) {
        printf("Consulta cancelada.\n");
        return;
    }

    if (!validarIdentificador(identificador)) {
        printf("Identificador invalido! Use exatamente 7 letras ou numeros.\n");
        return;
    }

    indice = buscarVeiculo(veiculos, quantidade, identificador);

    if (indice == -1) {
        printf("\nVeiculo nao encontrado!\n");
        return;
    }

    printf("\n===== VEICULO ENCONTRADO =====\n");
    printf("Identificador: %s\n", veiculos[indice].identificador);
    printf("Descricao: %s\n", veiculos[indice].descricao);

    if (veiculos[indice].categoria == 1) {
        printf("Categoria: Carro\n");
    } else {
        printf("Categoria: Moto\n");
    }

    printf("Fileira: %d\n", veiculos[indice].fileira);
    printf("Coluna: %d\n", veiculos[indice].coluna);
}

/* Lista todos os veiculos */
void listarVeiculos(Veiculo veiculos[], int quantidade) {
    int i;

    if (quantidade == 0) {
        printf("\nNao existem veiculos cadastrados.\n");
        return;
    }

    printf("\n===== VEICULOS CADASTRADOS =====\n");

    for (i = 0; i < quantidade; i++) {
        printf("\nVeiculo %d\n", i + 1);
        printf("Identificador: %s\n", veiculos[i].identificador);
        printf("Descricao: %s\n", veiculos[i].descricao);

        if (veiculos[i].categoria == 1) {
            printf("Categoria: Carro\n");
        } else {
            printf("Categoria: Moto\n");
        }

        printf("Fileira: %d\n", veiculos[i].fileira);
        printf("Coluna: %d\n", veiculos[i].coluna);
    }

    printf("\nTotal de veiculos: %d\n", quantidade);
}

/* Atualiza a descricao ou categoria de um veiculo */
void atualizarVeiculo(Veiculo veiculos[], int quantidade) {
    char identificador[100];
    char novaDescricao[100];
    int resultado;
    int indice;
    int opcao;
    int novaCategoria;

    if (quantidade == 0) {
        printf("\nNao existem veiculos cadastrados.\n");
        return;
    }

    printf("\nDigite o identificador do veiculo: ");

    resultado = lerTexto(identificador, sizeof(identificador));

    if (resultado != 1) {
        printf("Atualizacao cancelada.\n");
        return;
    }

    if (!validarIdentificador(identificador)) {
        printf("Identificador invalido! Use exatamente 7 letras ou numeros.\n");
        return;
    }

    indice = buscarVeiculo(veiculos, quantidade, identificador);

    if (indice == -1) {
        printf("\nVeiculo nao encontrado!\n");
        return;
    }

    printf("\n===== ATUALIZAR VEICULO =====\n");
    printf("1 - Alterar descricao\n");
    printf("2 - Alterar categoria\n");

    if (!lerInteiro("Escolha o que deseja alterar: ", &opcao)) {
        printf("Atualizacao cancelada.\n");
        return;
    }

    switch (opcao) {
        case 1:
            printf("Descricao atual: %s\n", veiculos[indice].descricao);
            printf("Digite a nova descricao: ");

            resultado = lerTexto(novaDescricao, sizeof(novaDescricao));

            if (resultado != 1) {
                printf("Atualizacao cancelada.\n");
                return;
            }

            if (strlen(novaDescricao) == 0) {
                printf("A descricao nao pode ficar vazia!\n");
                return;
            }

            if (strlen(novaDescricao) > 60) {
                printf("A descricao deve ter no maximo 60 caracteres!\n");
                return;
            }

            strcpy(veiculos[indice].descricao, novaDescricao);

            printf("\nDescricao atualizada com sucesso!\n");
            break;

        case 2:
            printf("Categoria atual: %s\n",
                   veiculos[indice].categoria == 1 ? "Carro" : "Moto");

            if (!lerInteiro(
                "Digite a nova categoria (1 - Carro / 2 - Moto): ",
                &novaCategoria
            )) {
                printf("Atualizacao cancelada.\n");
                return;
            }

            if (novaCategoria != 1 && novaCategoria != 2) {
                printf("Categoria invalida! Digite 1 ou 2.\n");
                return;
            }

            veiculos[indice].categoria = novaCategoria;

            printf("\nCategoria atualizada com sucesso!\n");
            break;

        default:
            printf("\nOpcao de atualizacao invalida!\n");
    }
}

/* Move um veiculo para outra vaga */
void moverVeiculo(
    Veiculo veiculos[],
    int quantidade,
    int mapa[FILEIRAS][COLUNAS]
) {
    char identificador[100];
    int resultado;
    int indice;
    int novaFileira;
    int novaColuna;
    int fileiraAtual;
    int colunaAtual;

    if (quantidade == 0) {
        printf("\nNao existem veiculos cadastrados.\n");
        return;
    }

    printf("\nDigite o identificador do veiculo: ");

    resultado = lerTexto(identificador, sizeof(identificador));

    if (resultado != 1) {
        printf("Movimentacao cancelada.\n");
        return;
    }

    if (!validarIdentificador(identificador)) {
        printf("Identificador invalido! Use exatamente 7 letras ou numeros.\n");
        return;
    }

    indice = buscarVeiculo(veiculos, quantidade, identificador);

    if (indice == -1) {
        printf("\nVeiculo nao encontrado!\n");
        return;
    }

    fileiraAtual = veiculos[indice].fileira;
    colunaAtual = veiculos[indice].coluna;

    printf("\nVeiculo encontrado!\n");
    printf("Posicao atual: Fileira %d, Coluna %d\n",
           fileiraAtual, colunaAtual);

    if (!lerInteiro("Nova fileira (1 a 4): ", &novaFileira)) {
        printf("Movimentacao cancelada.\n");
        return;
    }

    if (novaFileira < 1 || novaFileira > FILEIRAS) {
        printf("Fileira invalida!\n");
        return;
    }

    if (!lerInteiro("Nova coluna (1 a 5): ", &novaColuna)) {
        printf("Movimentacao cancelada.\n");
        return;
    }

    if (novaColuna < 1 || novaColuna > COLUNAS) {
        printf("Coluna invalida!\n");
        return;
    }

    /* Verifica se escolheu a mesma vaga */
    if (novaFileira == fileiraAtual &&
        novaColuna == colunaAtual) {
        printf("\nO veiculo ja esta nessa vaga!\n");
        return;
    }

    /* Verifica se a nova vaga esta ocupada */
    if (mapa[novaFileira - 1][novaColuna - 1] == 1) {
        printf("\nEssa vaga ja esta ocupada!\n");
        return;
    }

    /* Libera a vaga antiga */
    mapa[fileiraAtual - 1][colunaAtual - 1] = 0;

    /* Ocupa a nova vaga */
    mapa[novaFileira - 1][novaColuna - 1] = 1;

    /* Atualiza a posicao no vetor */
    veiculos[indice].fileira = novaFileira;
    veiculos[indice].coluna = novaColuna;

    printf("\nVeiculo movimentado com sucesso!\n");
    printf("Nova posicao: Fileira %d, Coluna %d\n",
           novaFileira, novaColuna);
}

/* Funcao principal */
int main(void) {
    int mapa[FILEIRAS][COLUNAS];
    int opcao = -1;
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

        if (!lerInteiro("\nEscolha uma opcao: ", &opcao)) {
            printf("Opcao invalida!\n");
            continue;
        }

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
                printf("\nFuncao de remocao sera implementada.\n");
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
                printf("\nOpcao inexistente!\n");
        }

    } while (opcao != 0);

    free(veiculos);
    veiculos = NULL;

    return 0;
}
