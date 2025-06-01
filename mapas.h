// --- Includes Globais ---
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

// --- Constantes de Jogo ---
#define LINHAS 16  // Linhas A-P
#define COLUNAS 15 // Colunas 1-15
#define FIFO1 "fifo1to2"
#define FIFO2 "fifo2to1"

// --- Estrutura do Mapa ---
typedef struct {
    char grelha[LINHAS][COLUNAS];
} Mapa;

// --- Funções do jogo ---
void inicializar_mapa(Mapa *mapa);
void mostrar_mapa(Mapa *mapa, const char *titulo);
void colocar_navios_interativamente(Mapa *mapa);
int coordenada_valida(const char *coord);
int coordenada_para_indices(const char *coord, int *linha, int *coluna);
void aplicar_jogada(Mapa *mapa, const char *coord, char resultado);
int verificar_derrota(Mapa *mapa);

