#include "mapas.h"

void inicializar_mapa(Mapa *mapa) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            mapa->grelha[i][j] = '-';
}

void mostrar_mapa(Mapa *mapa, const char *titulo) {
    printf("\n%s\n    ", titulo);
    for (int j = 1; j <= COLUNAS; j++)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < LINHAS; i++) {
        printf(" %c |", 'A' + i);
        for (int j = 0; j < COLUNAS; j++) {
            printf(" %c ", mapa->grelha[i][j]);
        }
        printf("\n");
    }
}

int coordenada_valida(const char *coord) {
    if (strlen(coord) < 2 || strlen(coord) > 3)
        return 0;
    char letra = toupper(coord[0]);
    int numero = atoi(coord + 1);
    return (letra >= 'A' && letra <= 'K' && numero >= 1 && numero <= 10);
}

int coordenada_para_indices(const char *coord, int *linha, int *coluna) {
    if (!coordenada_valida(coord))
        return 0;

    *linha = toupper(coord[0]) - 'A';
    *coluna = atoi(coord + 1) - 1;
    return 1;
}

int pode_colocar(Mapa *mapa, int linha, int coluna, int tamanho, char direcao) {
    if (direcao == 'H') {
        if (coluna + tamanho > COLUNAS) return 0;
        for (int j = 0; j < tamanho; j++) {
            if (mapa->grelha[linha][coluna + j] == 'N') return 0;
        }
    } else {
        if (linha + tamanho > LINHAS) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa->grelha[linha + i][coluna] == 'N') return 0;
        }
    }
    return 1;
}

void colocar_navios_interativamente(Mapa *mapa) {
    int tamanhos[] = {4, 3, 3, 2, 2, 1};
    int total_navios = sizeof(tamanhos) / sizeof(int);
    char input[10], dir_input[10];
    int linha, coluna;
    char direcao;

    printf("\n--- Colocação de navios ---\n");

    for (int i = 0; i < total_navios; ) {
        int tamanho = tamanhos[i];
        mostrar_mapa(mapa, "Mapa Atual\n");        
        printf("\nNavio de tamanho %d (%d/%d):\n", tamanho, i + 1, total_navios);
        printf("  Posição inicial (ex: B5): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (!coordenada_para_indices(input, &linha, &coluna)) {
            printf("  Coordenada inválida. Tente novamente.\n");
            continue;
        }

        if (tamanho > 1) {
            printf("  Direção (H para horizontal, V para vertical): ");
            fgets(dir_input, sizeof(dir_input), stdin);
            direcao = toupper(dir_input[0]);
            if (direcao != 'H' && direcao != 'V') {
                printf("  Direção inválida.\n");
                continue;
            }
        } else {
            direcao = 'H'; // direção irrelevante para navio de 1 célula
        }

        if (!pode_colocar(mapa, linha, coluna, tamanho, direcao)) {
            printf("  Não é possível colocar o navio nessa posição.\n");
            continue;
        }

        // Colocar o navio
        if (direcao == 'H') {
            for (int j = 0; j < tamanho; j++)
                mapa->grelha[linha][coluna + j] = 'N';
        } else {
            for (int j = 0; j < tamanho; j++)
                mapa->grelha[linha + j][coluna] = 'N';
        }

        i++;
    }
}

void aplicar_jogada(Mapa *mapa, const char *coord, char resultado) {
    int linha = toupper(coord[0]) - 'A';
    int coluna = atoi(coord + 1) - 1;
    mapa->grelha[linha][coluna] = resultado;
}

int verificar_derrota(Mapa *mapa) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            if (mapa->grelha[i][j] == 'N')
                return 0;
    return 1;
}
