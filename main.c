
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define FILEIRAS 4
#define COLUNAS 5
#define TOTAL_VAGAS 20
#define CAPACIDADE_INICIAL 2
#define CAPACIDADE_MAXIMA 20

typedef struct {
    char identificador[8];
    char descricao[61];
    int categoria;
    int fileira;
    int coluna;
} Veiculo;

/* ================= ENTRADA DE DADOS ================= */

int lerTexto(char texto[], int tamanho) {
    if (fgets(texto, tamanho, stdin) == NULL) {
        return 0;
    }

    size_t comprimento = strlen(texto);

    if (comprimento > 0 && texto[comprimento - 1] == '\n') {
        texto[comprimento - 1] = '\0';
        return 1;
    }

    int caractere;

    while ((caractere = getchar()) != '\n' &&
           caractere != EOF) {
        /* Descarta o restante da entrada */
    }

    if (comprimento == (size_t)tamanho - 1) {
        printf("Entrada muito longa!\n");
        return -1;
    }

    return 1;
}

int lerInteiro(const char mensagem[], int minimo, int maximo) {
    char entrada[100];
    char *fim;
    long valor;

    while (1) {
        printf("%s", mensagem);

        int resultado = lerTexto(entrada, sizeof(entrada));

        if (resultado == 0) {
            printf("\nEntrada encerrada.\n");
            exit(0);
        }

        if (resultado == -1) {
            continue;
        }

        errno = 0;
        valor = strtol(entrada, &fim, 10);

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (entrada[0] == '\0' ||
            errno == ERANGE ||
            *fim != '\0' ||
            valor < minimo ||
            valor > maximo) {

            printf("Valor invalido! Digite entre %d e %d.\n",
                   minimo, maximo);
        } else {
            return (int)valor;
        }
    }
}

/* ================= MATRIZ ================= */

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
        printf("C%d  ", j + 1);
    }

    printf("\n");

    for (int i = 0; i < FILEIRAS; i++) {
        printf("F%d   ", i + 1);

        for (int j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == 1) {
                printf("[X] ");
            } else {
                printf("[.] ");
            }
        }

        printf("\n");
    }

    printf("\n[X] Ocupada | [.] Livre\n");
}

/* ================= VETOR DINAMICO ================= */

int buscarVeiculo(Veiculo veiculos[], int quantidade,
                  const char identificador[]) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(veiculos[i].identificador,
                   identificador) == 0) {
            return i;
        }
    }

    return -1;
}

int aumentarCapacidade(Veiculo **veiculos, int *capacidade) {
    if (*capacidade >= CAPACIDADE_MAXIMA) {
        return 0;
    }

    int novaCapacidade = (*capacidade) * 2;

    if (novaCapacidade > CAPACIDADE_MAXIMA) {
        novaCapacidade = CAPACIDADE_MAXIMA;
    }

    Veiculo *novoVetor = realloc(
        *veiculos,
        novaCapacidade * sizeof(Veiculo)
    );

    if (novoVetor == NULL) {
        printf("Erro ao aumentar memoria!\n");
        return 0;
    }

    *veiculos = novoVetor;
    *capacidade = novaCapacidade;

    printf("Capacidade do vetor aumentada para %d.\n",
           novaCapacidade);

    return 1;
}

/* ================= VALIDACOES ================= */

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

int validarDescricao(const char descricao[]) {
    return strlen(descricao) > 0 &&
           strlen(descricao) <= 60;
}

/* ================= CADASTRO ================= */

void cadastrarVeiculo(Veiculo **veiculos, int *quantidade,
                      int *capacidade,
                      int mapa[FILEIRAS][COLUNAS]) {

    if (*quantidade >= TOTAL_VAGAS) {
        printf("\nEstacionamento lotado!\n");
        return;
    }

    Veiculo novo;
    char identificadorTemp[100];
    char descricaoTemp[100];

    printf("\n===== CADASTRO DE VEICULO =====\n");

    int resultado;

    do {
        printf("Identificador (7 caracteres): ");

        resultado = lerTexto(identificadorTemp,
                             sizeof(identificadorTemp));

        if (resultado == 0) {
            return;
        }

        if (resultado == -1) {
            continue;
        }

        if (!validarIdentificador(identificadorTemp)) {
            printf("Identificador invalido! "
                   "Digite exatamente 7 caracteres alfanumericos.\n");
            continue;
        }

        if (buscarVeiculo(*veiculos, *quantidade,
                          identificadorTemp) != -1) {
            printf("Identificador ja cadastrado!\n");
            continue;
        }

        break;

    } while (1);

    strcpy(novo.identificador, identificadorTemp);

    do {
        printf("Descricao do veiculo: ");

        resultado = lerTexto(descricaoTemp,
                             sizeof(descricaoTemp));

        if (resultado == 0) {
            return;
        }

        if (resultado == -1) {
            continue;
        }

        if (!validarDescricao(descricaoTemp)) {
            printf("Descricao invalida! "
                   "Digite de 1 a 60 caracteres.\n");
        } else {
            break;
        }

    } while (1);

    strcpy(novo.descricao, descricaoTemp);

    novo.categoria = lerInteiro(
        "Categoria (1-Carro / 2-Moto): ", 1, 2
    );

    novo.fileira = lerInteiro("Fileira (1 a 4): ", 1, 4);
    novo.coluna = lerInteiro("Coluna (1 a 5): ", 1, 5);

    if (mapa[novo.fileira - 1][novo.coluna - 1] == 1) {
        printf("Vaga ocupada! Cadastro cancelado.\n");
        return;
    }

    if (*quantidade >= *capacidade) {
        if (!aumentarCapacidade(veiculos, capacidade)) {
            return;
        }
    }

    (*veiculos)[*quantidade] = novo;

    mapa[novo.fileira - 1][novo.coluna - 1] = 1;

    (*quantidade)++;

    printf("\nVeiculo cadastrado com sucesso!\n");
}

/* ================= CONSULTA ================= */

void consultarVeiculo(Veiculo veiculos[], int quantidade) {
    char identificador[100];

    printf("\n===== CONSULTA DE VEICULO =====\n");
    printf("Digite o identificador: ");

    int resultado = lerTexto(identificador,
                             sizeof(identificador));

    if (resultado != 1) {
        return;
    }

    if (!validarIdentificador(identificador)) {
        printf("Identificador invalido!\n");
        return;
    }

    int indice = buscarVeiculo(veiculos, quantidade,
                               identificador);

    if (indice == -1) {
        printf("Veiculo nao encontrado!\n");
        return;
    }

    Veiculo v = veiculos[indice];

    printf("\n===== VEICULO ENCONTRADO =====\n");
    printf("ID: %s\n", v.identificador);
    printf("Descricao: %s\n", v.descricao);

    if (v.categoria == 1) {
        printf("Categoria: Carro\n");
    } else {
        printf("Categoria: Moto\n");
    }

    printf("Fileira: %d\n", v.fileira);
    printf("Coluna: %d\n", v.coluna);
}

/* ================= LISTAGEM ================= */

void listarVeiculos(Veiculo veiculos[], int quantidade) {
    printf("\n===== LISTA DE VEICULOS =====\n");

    if (quantidade == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("\nVeiculo %d\n", i + 1);
        printf("ID: %s\n", veiculos[i].identificador);
        printf("Descricao: %s\n", veiculos[i].descricao);

        if (veiculos[i].categoria == 1) {
            printf("Categoria: Carro\n");
        } else {
            printf("Categoria: Moto\n");
        }

        printf("Vaga: F%d / C%d\n",
               veiculos[i].fileira,
               veiculos[i].coluna);
    }

    printf("\nTotal de veiculos: %d\n", quantidade);
}

/* ================= ATUALIZACAO ================= */

void atualizarVeiculo(Veiculo veiculos[], int quantidade) {
    char identificador[100];
    char novaDescricao[100];

    printf("\n===== ATUALIZAR VEICULO =====\n");
    printf("Identificador: ");

    int resultado = lerTexto(identificador,
                             sizeof(identificador));

    if (resultado != 1) {
        return;
    }

    if (!validarIdentificador(identificador)) {
        printf("Identificador invalido!\n");
        return;
    }

    int indice = buscarVeiculo(veiculos, quantidade,
                               identificador);

    if (indice == -1) {
        printf("Veiculo nao encontrado!\n");
        return;
    }

    printf("\nDescricao atual: %s\n",
           veiculos[indice].descricao);

    printf("Nova descricao: ");

    resultado = lerTexto(novaDescricao,
                         sizeof(novaDescricao));

    if (resultado != 1) {
        return;
    }

    if (!validarDescricao(novaDescricao)) {
        printf("Descricao invalida!\n");
        return;
    }

    strcpy(veiculos[indice].descricao, novaDescricao);

    veiculos[indice].categoria = lerInteiro(
        "Nova categoria (1-Carro / 2-Moto): ", 1, 2
    );

    printf("Veiculo atualizado com sucesso!\n");
}

/* ================= MOVIMENTACAO ================= */

void moverVeiculo(Veiculo veiculos[], int quantidade,
                  int mapa[FILEIRAS][COLUNAS]) {

    char identificador[100];

    printf("\n===== MOVIMENTAR VEICULO =====\n");
    printf("Identificador: ");

    int resultado = lerTexto(identificador,
                             sizeof(identificador));

    if (resultado != 1) {
        return;
    }

    if (!validarIdentificador(identificador)) {
        printf("Identificador invalido!\n");
        return;
    }

    int indice = buscarVeiculo(veiculos, quantidade,
                               identificador);

    if (indice == -1) {
        printf("Veiculo nao encontrado!\n");
        return;
    }

    printf("Local atual: F%d / C%d\n",
           veiculos[indice].fileira,
           veiculos[indice].coluna);

    int novaFileira = lerInteiro("Nova fileira (1 a 4): ", 1, 4);
    int novaColuna = lerInteiro("Nova coluna (1 a 5): ", 1, 5);

    int linhaAtual = veiculos[indice].fileira - 1;
    int colunaAtual = veiculos[indice].coluna - 1;

    int linhaNova = novaFileira - 1;
    int colunaNova = novaColuna - 1;

    if (linhaAtual == linhaNova &&
        colunaAtual == colunaNova) {
        printf("O veiculo ja esta nessa vaga!\n");
        return;
    }

    if (mapa[linhaNova][colunaNova] == 1) {
        printf("Vaga ocupada! Movimentacao cancelada.\n");
        return;
    }

    mapa[linhaAtual][colunaAtual] = 0;
    mapa[linhaNova][colunaNova] = 1;

    veiculos[indice].fileira = novaFileira;
    veiculos[indice].coluna = novaColuna;

    printf("Veiculo movimentado com sucesso!\n");
}

/* ================= REMOCAO ================= */

void removerVeiculo(Veiculo veiculos[], int *quantidade,
                    int mapa[FILEIRAS][COLUNAS]) {

    char identificador[100];

    printf("\n===== REMOVER VEICULO =====\n");

    if (*quantidade == 0) {
        printf("Nao existem veiculos cadastrados.\n");
        return;
    }

    printf("Identificador: ");

    int resultado = lerTexto(identificador,
                             sizeof(identificador));

    if (resultado != 1) {
        return;
    }

    if (!validarIdentificador(identificador)) {
        printf("Identificador invalido!\n");
        return;
    }

    int indice = buscarVeiculo(veiculos, *quantidade,
                               identificador);

    if (indice == -1) {
        printf("Veiculo nao encontrado!\n");
        return;
    }

    int linha = veiculos[indice].fileira - 1;
    int coluna = veiculos[indice].coluna - 1;

    mapa[linha][coluna] = 0;

    for (int i = indice; i < *quantidade - 1; i++) {
        veiculos[i] = veiculos[i + 1];
    }

    (*quantidade)--;

    printf("Veiculo removido com sucesso!\n");
}

/* ================= RELATORIO ================= */

void relatorioOcupacao(Veiculo veiculos[], int quantidade,
                       int mapa[FILEIRAS][COLUNAS]) {

    int ocupadas = 0;
    int carros = 0;
    int motos = 0;

    for (int i = 0; i < FILEIRAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == 1) {
                ocupadas++;
            }
        }
    }

    for (int i = 0; i < quantidade; i++) {
        if (veiculos[i].categoria == 1) {
            carros++;
        } else if (veiculos[i].categoria == 2) {
            motos++;
        }
    }

    int livres = TOTAL_VAGAS - ocupadas;

    float percentual =
        (ocupadas / (float)TOTAL_VAGAS) * 100.0f;

    printf("\n===== RELATORIO DE OCUPACAO =====\n");
    printf("Total de vagas: %d\n", TOTAL_VAGAS);
    printf("Vagas ocupadas: %d\n", ocupadas);
    printf("Vagas livres: %d\n", livres);
    printf("Ocupacao: %.2f%%\n", percentual);
    printf("Carros cadastrados: %d\n", carros);
    printf("Motos cadastradas: %d\n", motos);
    printf("Veiculos no vetor: %d\n", quantidade);

    if (ocupadas != quantidade) {
        printf("ATENCAO: matriz e vetor possuem "
               "quantidades diferentes!\n");
    }
}

/* ================= VERIFICACAO DE CONSISTENCIA ================= */

int verificarConsistencia(Veiculo veiculos[], int quantidade,
                          int mapa[FILEIRAS][COLUNAS]) {

    int ocupadas = 0;

    for (int i = 0; i < FILEIRAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == 1) {
                ocupadas++;
            } else if (mapa[i][j] != 0) {
                return 0;
            }
        }
    }

    if (ocupadas != quantidade) {
        return 0;
    }

    for (int i = 0; i < quantidade; i++) {
        int linha = veiculos[i].fileira - 1;
        int coluna = veiculos[i].coluna - 1;

        if (linha < 0 || linha >= FILEIRAS ||
            coluna < 0 || coluna >= COLUNAS) {
            return 0;
        }

        if (mapa[linha][coluna] != 1) {
            return 0;
        }

        for (int j = i + 1; j < quantidade; j++) {
            if (strcmp(veiculos[i].identificador,
                       veiculos[j].identificador) == 0) {
                return 0;
            }

            if (veiculos[i].fileira == veiculos[j].fileira &&
                veiculos[i].coluna == veiculos[j].coluna) {
                return 0;
            }
        }
    }

    return 1;
}

/* ================= MENU ================= */

void exibirMenu(void) {
    printf("\n");
    printf("====================================\n");
    printf("   SISTEMA DE GESTAO ESTACIONAMENTO\n");
    printf("====================================\n");
    printf("1 - Cadastrar veiculo\n");
    printf("2 - Consultar veiculo\n");
    printf("3 - Atualizar veiculo\n");
    printf("4 - Movimentar veiculo\n");
    printf("5 - Remover veiculo\n");
    printf("6 - Listar veiculos\n");
    printf("7 - Exibir mapa\n");
    printf("8 - Relatorio de ocupacao\n");
    printf("0 - Sair\n");
    printf("====================================\n");
}

/* ================= MAIN ================= */

int main(void) {
    int mapa[FILEIRAS][COLUNAS];

    int quantidade = 0;
    int capacidade = CAPACIDADE_INICIAL;

    Veiculo *veiculos = malloc(
        capacidade * sizeof(Veiculo)
    );

    if (veiculos == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    inicializarMapa(mapa);

    int opcao;

    do {
        exibirMenu();

        opcao = lerInteiro("Escolha uma opcao: ", 0, 8);

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
                moverVeiculo(veiculos, quantidade, mapa);
                break;

            case 5:
                removerVeiculo(veiculos, &quantidade, mapa);
                break;

            case 6:
                listarVeiculos(veiculos, quantidade);
                break;

            case 7:
                exibirMapa(mapa);
                break;

            case 8:
                relatorioOcupacao(veiculos, quantidade, mapa);
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
        }

        if (opcao != 0) {
            if (!verificarConsistencia(veiculos,
                                       quantidade, mapa)) {
                printf("\nERRO: inconsistencias detectadas "
                       "no estacionamento!\n");
            }
        }

    } while (opcao != 0);

    free(veiculos);
    veiculos = NULL;

    printf("Memoria liberada. Programa encerrado.\n");

    return 0;
}
