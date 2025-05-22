#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include "mapas.h"

#define FIFO1 "fifo1to2"
#define FIFO2 "fifo2to1"

int main() {
    Mapa meu_mapa, mapa_inimigo;
    inicializar_mapa(&meu_mapa);
    inicializar_mapa(&mapa_inimigo);
    colocar_navios_exemplo(&meu_mapa);

    char jogada[10], resposta[10];
    int fd_envia, fd_recebe;
    int linha, coluna;

    printf("== Jogador 2 ==\n");

    while (1) {
        mostrar_mapa(&mapa_inimigo, "Mapa do Inimigo");
        mostrar_mapa(&meu_mapa, "O Meu Mapa");

        // Recebe jogada
        fd_recebe = open(FIFO1, O_RDONLY);
        read(fd_recebe, jogada, sizeof(jogada));
        close(fd_recebe);

        printf("\nJogada do inimigo: %s\n", jogada);
        if (!coordenada_para_indices(jogada, &linha, &coluna)) {
            printf("Coordenada inválida recebida.\n");
            continue;
        }

        char resultado = (meu_mapa.grelha[linha][coluna] == 'N') ? 'X' : 'O';

        if (meu_mapa.grelha[linha][coluna] == 'N')
            meu_mapa.grelha[linha][coluna] = 'X';
        else
            meu_mapa.grelha[linha][coluna] = 'O';

        strcpy(resposta, &resultado);
        fd_envia = open(FIFO2, O_WRONLY);
        write(fd_envia, resposta, sizeof(resposta));
        close(fd_envia);

        if (verificar_derrota(&meu_mapa)) {
            printf("Perdeste!\n");
            break;
        }

        // Jogador 2 envia jogada
        printf("\nTua jogada (ex: C10): ");
        fgets(jogada, sizeof(jogada), stdin);
        jogada[strcspn(jogada, "\n")] = '\0';

        if (!coordenada_para_indices(jogada, &linha, &coluna)) {
            printf("Coordenada inválida.\n");
            continue;
        }

        fd_envia = open(FIFO1, O_WRONLY);
        write(fd_envia, jogada, sizeof(jogada));
        close(fd_envia);

        fd_recebe = open(FIFO2, O_RDONLY);
        read(fd_recebe, resposta, sizeof(resposta));
        close(fd_recebe);

        printf("Resultado: %s\n", resposta);
        aplicar_jogada(&mapa_inimigo, jogada, resposta[0]);

        if (strcmp(resposta, "G") == 0) {
            printf("Ganhaste!\n");
            break;
        }
    }

    return 0;
}
