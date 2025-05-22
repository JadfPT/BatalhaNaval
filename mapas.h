// mapas.h
#ifndef MAPAS_H
#define MAPAS_H

#define LINHAS 16 // A a P
#define COLUNAS 15 // 1 a 15

typedef struct {
    char grelha[LINHAS][COLUNAS];
} Mapa;

// Funções para inicializar e mostrar o mapa
void inicializar_mapa(Mapa *mapa);
void mostrar_mapa(Mapa *mapa, const char *titulo);
void colocar_navios_interativamente(Mapa *mapa);
int coordenada_valida(const char *coord);
int coordenada_para_indices(const char *coord, int *linha, int *coluna);
void aplicar_jogada(Mapa *mapa, const char *coord, char resultado);
int verificar_derrota(Mapa *mapa);

#endif
