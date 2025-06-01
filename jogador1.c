#include "mapas.h"

int main() {
    Mapa meu_mapa, mapa_inimigo;
    inicializar_mapa(&meu_mapa);
    inicializar_mapa(&mapa_inimigo);
    colocar_navios_interativamente(&meu_mapa);

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    char jogada[10], resposta[10];
    int linha, coluna;
    int fd_envia, fd_recebe;
    int minha_vez = 1;
    int repetir_jogada = 0;

    printf("== Jogador 1 ==\n");

    // Sincronização
    fd_envia = open(FIFO1, O_WRONLY);
    write(fd_envia, "READY", 6);
    close(fd_envia);

    fd_recebe = open(FIFO2, O_RDONLY);
    read(fd_recebe, resposta, sizeof(resposta));
    close(fd_recebe);

    if (strcmp(resposta, "READY") != 0) {
        printf("Erro na sincronização\n");
        exit(1);
    }

    while (1) {
        if (minha_vez) {
            while (1) {
                mostrar_mapa(&mapa_inimigo, "Mapa do Inimigo");
                mostrar_mapa(&meu_mapa, "O Meu Mapa");

                if (repetir_jogada == 1) {
                    printf("\nJá jogaste nesta coordenada. Tenta outra.\n");
                    repetir_jogada = 0;
                }

                printf("\nTua jogada (ex: A5): ");
                fgets(jogada, sizeof(jogada), stdin);
                jogada[strcspn(jogada, "\n")] = '\0';

                if (!coordenada_para_indices(jogada, &linha, &coluna)) {
                    printf("Coordenada inválida.\n");
                    strcpy(jogada, "INVALID");
                    fd_envia = open(FIFO1, O_WRONLY);
                    write(fd_envia, jogada, sizeof(jogada));
                    close(fd_envia);
                    continue;
                }

                if (mapa_inimigo.grelha[linha][coluna] == 'X' || mapa_inimigo.grelha[linha][coluna] == 'O') {
                    repetir_jogada = 1;
                    continue;
                }

                fd_envia = open(FIFO1, O_WRONLY);
                write(fd_envia, jogada, sizeof(jogada));
                close(fd_envia);

                fd_recebe = open(FIFO2, O_RDONLY);
                read(fd_recebe, resposta, sizeof(resposta));
                close(fd_recebe);

                if (strcmp(resposta, "G") == 0) {
                    printf("Ganhaste!\n");
                    unlink(FIFO1);
                    unlink(FIFO2);
                    return 0;
                }

                aplicar_jogada(&mapa_inimigo, jogada, resposta[0]);
                printf("Resultado: %s\n", resposta);

                if (resposta[0] != 'X')
                    break;

            }

            minha_vez = 0;
        } else {
            fd_recebe = open(FIFO1, O_RDONLY);
            read(fd_recebe, jogada, sizeof(jogada));
            close(fd_recebe);

            if (strcmp(jogada, "INVALID") == 0) {
                printf("Jogada inválida recebida (erro do adversário).\n");
                continue;
            }

            printf("\nJogada do inimigo: %s\n", jogada);

            if (!coordenada_para_indices(jogada, &linha, &coluna)) {
                printf("Coordenada inválida recebida.\n");
                strcpy(resposta, "O");
                fd_envia = open(FIFO2, O_WRONLY);
                write(fd_envia, resposta, sizeof(resposta));
                close(fd_envia);
                continue;
            }

            char resultado;
            if (meu_mapa.grelha[linha][coluna] == 'N') {
                meu_mapa.grelha[linha][coluna] = 'X';
                resultado = 'X';
            } else if (meu_mapa.grelha[linha][coluna] == 'X' || meu_mapa.grelha[linha][coluna] == 'O') {
                resultado = 'O';
            } else {
                meu_mapa.grelha[linha][coluna] = 'O';
                resultado = 'O';
            }

            if (verificar_derrota(&meu_mapa)) {
                strcpy(resposta, "G");
            } else {
                strcpy(resposta, &resultado);
            }

            fd_envia = open(FIFO2, O_WRONLY);
            write(fd_envia, resposta, sizeof(resposta));
            close(fd_envia);

            if (strcmp(resposta, "G") == 0) {
                printf("Perdeste!\n");
                unlink(FIFO1);
                unlink(FIFO2);
                return 0;
            }

            if (resultado == 'O')
                minha_vez = 1;
        }
    }
}
