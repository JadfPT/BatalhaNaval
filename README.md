# Batalha Naval - SO

Este é um jogo de Batalha Naval desenvolvido em C para a disciplina de Sistemas Operativos. Utiliza comunicação entre processos via FIFOs (named pipes) e suporta múltiplos tipos de navios e interações em tempo real entre dois jogadores.

## Como Jogar

1. Compile o projeto:
   ```bash
   make
   ```

2. Abra dois terminais.

3. No primeiro terminal, execute:
   ```bash
   ./jogador1
   ```

4. No segundo terminal, execute:
   ```bash
   ./jogador2
   ```

5. Siga as instruções para colocar os navios e alternar os turnos.

## Regras

- Cada jogador coloca os seguintes navios:
  - 1 navio de 4 células
  - 2 navios de 3 células
  - 2 navios de 2 células
  - 1 navio de 1 célula
- O jogador que acerta continua a jogar.
- O primeiro a destruir todos os navios do adversário vence.
- É indicado quando uma coordenada já foi jogada.

## Arquitetura

- Comunicação entre jogadores é feita por FIFO (`fifo1to2`, `fifo2to1`)
- Os mapas são estruturas de 16x15
- Os jogadores alternam turnos com verificação de acertos (`X`) e falhas (`O`)
- Os mapas são atualizados e mostrados ao longo do jogo

## Ficheiros

- `jogador1.c` – Lógica do primeiro jogador
- `jogador2.c` – Lógica do segundo jogador
- `mapas.c` – Funções utilitárias para os mapas
- `mapas.h` – Cabeçalho com definições e funções
- `Makefile` – Para compilar facilmente
- `README.md` – Este ficheiro

## Autor
- **Daniel Cardoso**
- **Fábio Horta**
- **Francisco Pereira**
- **João Freire**

Feito com dedicação para a disciplina de Sistemas Operativos.
