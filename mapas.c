// mapas.c
#include "mapas.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void inicializar_mapa(Mapa *mapa) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            mapa->grelha[i][j] = '-'; // mar
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

void colocar_navios_exemplo(Mapa *mapa) {
    // Exemplo: coloca 3 navios em posições fixas
    mapa->grelha[0][0] = 'N';
    mapa->grelha[0][1] = 'N';
    mapa->grelha[0][2] = 'N';
    mapa->grelha[5][5] = 'N';
    mapa->grelha[9][10] = 'N';
}

int coordenada_valida(const char *coord) {
    if (strlen(coord) < 2 || strlen(coord) > 3)
        return 0;
    char letra = toupper(coord[0]);
    int numero = atoi(coord + 1);
    return (letra >= 'A' && letra <= 'P' && numero >= 1 && numero <= 15);
}

int coordenada_para_indices(const char *coord, int *linha, int *coluna) {
    if (!coordenada_valida(coord))
        return 0;

    *linha = toupper(coord[0]) - 'A';
    *coluna = atoi(coord + 1) - 1;
    return 1;
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
