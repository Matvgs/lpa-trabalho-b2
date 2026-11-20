
#include <stdio.h>

#define FILEIRAS 4
#define COLUNAS 5

void inicializarMapa(int mapa[FILEIRAS][COLUNAS]);
void exibirMapa(int mapa[FILEIRAS][COLUNAS]);
void exibirMenu(void);

int main(void) {
    int mapa[FILEIRAS][COLUNAS];
    int opcao;

    inicializarMapa(mapa);

    do {
        exibirMenu();

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

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
                printf("\nListagem ainda nao implementada.\n");
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
