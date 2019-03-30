/*
 *  JOGO DA VELHA USANDO UMA VARIAVEL INTEIRA COMO ESTRUTURA DE DADOS
 *  OU SEJA, UMA VARIÁVEL QUE GUARDA A MATRIZ VETORIZADA EM BITS.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM 3

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short int usint;

bool vitoria(void);
bool linha(void);
bool coluna(void);
bool diagonal(void);
bool ganhou(uint);
void jogar(uchar player);
void mostrar(void);

uint velha;
enum { O, X };

void mostrar(void) {
  uint k = 0u, aux, op;
  for (uchar i = 0; i < TAM; i++) {
    for (uchar j = 0; j < TAM; j++) {
      aux = (i * TAM + j) << 1;
      k = 1u << (aux + 1) & velha;
      if (k) {
        op = 1u << (aux)&velha;
        if (op)
          printf("X ");
        else
          printf("O ");
      } else
        printf(" | ");
    }
    printf("\n");
  }
}

void jogar(uchar player) {
  usint casa;
  uint aux = 2;
  while (true) {
    printf("Jogue em uma casa: ");
    scanf("%hd%*c", &casa);
    if (casa >= 1 && casa <= 9) {
      if (!(aux << ((casa - 1) * 2) & velha))
        break; // VERIFICA SE A JOGADA É LEGAL
      printf("Célula já ocupada! Tente novamente, jogador %c!\n\n",
             (player == X) ? 'X' : 'O');
    } else {
      printf("Célula inválida. Insira no intervalo: [1, 9].\n");
    }
  }
  if (player == X)
    aux |= 1;
  velha |= (aux << ((casa - 1) * 2));
  mostrar();
}

bool ganhou(uint x) {
  if (x == TAM) {
    puts("Jogador 2 (X) ganhou!");
    return true;
  } else if (!x) {
    puts("Jogador 1 (O) ganhou!");
    return true;
  }
  return false;
}

bool vitoria(void) { // condições de vitoria
  return linha() || coluna() || diagonal();
}

bool linha(void) {
  uint sum = 0u;
  for (uchar i = 0; i < TAM; i++, sum = 0u) {
    for (uchar j = 0; j < TAM; j++)
      sum += (1u << ((i * TAM + j) * 2 + 1) & velha) ? 1 : 0;

    if (sum == TAM) {
      sum = 0u;
      for (uchar j = 0; j < TAM; j++)
        sum += (1u << ((i * TAM + j) * 2) & velha) ? 1 : 0;
      if (ganhou(sum))
        return true;
    }
  }
  return false;
}

bool coluna(void) {
  uint sum = 0u;
  for (uchar i = 0; i < TAM; i++, sum = 0u) {
    for (uchar j = 0; j < TAM; j++)
      sum += (1u << ((1 + i + j * TAM) * 2 - 1) & velha) ? 1 : 0;

    if (sum == TAM) {
      sum = 0;
      for (uchar j = 0; j < TAM; j++)
        sum += (1u << ((1 + i + j * TAM) * 2 - 2) & velha) ? 1 : 0;
      if (ganhou(sum))
        return true;
    }
  }
  return false;
}

bool diagonal(void) {
  uint sum_sd = 0, sum_pd = 0;
  for (uchar j = 0; j < TAM; j++) {
    sum_pd += (1u << ((j * (TAM + 1)) * 2 + 1) & velha) ? 1 : 0;
    sum_sd += (1u << ((TAM + j * (TAM + 1) + 2)) & velha) ? 1 : 0;
  }

  if (sum_pd == TAM || sum_sd == TAM) {
    sum_pd = (sum_pd == TAM) ? 0 : TAM + TAM;
    sum_sd = (sum_sd == TAM) ? 0 : TAM + TAM;
    for (uchar j = 0; j < TAM; j++) {
      sum_pd += (1u << ((j * (TAM + 1)) * 2) & velha) ? 1 : 0;
      sum_sd += (1u << ((TAM + j * (TAM + 1) + 1)) & velha) ? 1 : 0;
    }
    if (ganhou(sum_pd) || ganhou(sum_sd))
      return true;
  }
  return false;
}

int main() {
  for (uchar i = 0; i < TAM * TAM; i++) {
    jogar(i % 2);
    if (i >= 2)
      if (vitoria())
        return 0;
  }
  return 1;
}
