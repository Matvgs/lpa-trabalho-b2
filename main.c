
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

void inicializarMapa(int mapa[FILEIRAS][COLUNAS]);
void exibirMapa(int mapa[FILEIRAS][COLUNAS]);
void exibirMenu(void);

int main(void) {
    int mapa[FILEIRAS][COLUNAS];
    int opcao;

    Veiculo *veiculos;
    int quantidade = 0;
    int capacidade = CAPACIDADE_INICIAL;

    /* Alocacao inicial do vetor dinamico */
    veiculos = malloc(capacidade * sizeof(Veiculo));

    if (veiculos == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    inicializarMapa(mapa);

    printf("Sistema iniciado com sucesso!\n");
    printf("Capacidade inicial: %d veiculos.\n", capacidade);

    do {
        exibirMenu();

        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida!\n");

            while (getchar() != '\n');

            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
                printf("\nCadastro ainda nao implementado.\n");
                break;

            case 2:
                printf("\nConsulta ainda nao implementada.\n");
                break;

            case 3:
                printf("\nAtualizacao ainda nao implementada.\n");
                break;

            case 4:
                printf("\nMovimentacao ainda nao implementada.\n");
                break;

            case 5:
                printf("\nRemocao ainda nao implementada.\n");
                break;

            case 6:
                printf("\n===== CONTROLE DA COLECAO =====\n");
                printf("Veiculos cadastrados: %d\n", quantidade);
                printf("Capacidade do vetor: %d\n", capacidade);
                break;

            case 7:
                exibirMapa(mapa);
                break;

            case 8:
                printf("\nRelatorio ainda nao implementado.\n");
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    /* Liberacao da memoria alocada */
    free(veiculos);

    veiculos = NULL;

    printf("Memoria liberada com sucesso!\n");

    return 0;
}

void inicializarMapa(int mapa[FILEIRAS][COLUNAS]) {
    int i, j;

    for (i = 0; i < FILEIRAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            mapa[i][j] = 0;
        }
    }
}

void exibirMapa(int mapa[FILEIRAS][COLUNAS]) {
    int i, j;

    printf("\n===== MAPA DO ESTACIONAMENTO =====\n\n");

    printf("      ");

    for (j = 0; j < COLUNAS; j++) {
        printf("C%d  ", j + 1);
    }

    printf("\n");

    for (i = 0; i < FILEIRAS; i++) {
        printf("F%d    ", i + 1);

        for (j = 0; j < COLUNAS; j++) {
            if (mapa[i][j] == 0) {
                printf(".   ");
            } else {
                printf("X   ");
            }
        }

        printf("\n");
    }

    printf("\nLegenda: X = ocupada | . = livre\n");
}

void exibirMenu(void) {
    printf("\n");
    printf("===== SISTEMA DE ESTACIONAMENTO =====\n");
    printf("1 - Cadastrar veiculo\n");
    printf("2 - Consultar veiculo\n");
    printf("3 - Atualizar veiculo\n");
    printf("4 - Mover veiculo\n");
    printf("5 - Remover veiculo\n");
    printf("6 - Listar veiculos\n");
    printf("7 - Exibir mapa de vagas\n");
    printf("8 - Relatorio de ocupacao\n");
    printf("0 - Encerrar\n");
    printf("===================================\n");
}
