/*
 *  JOGO DA VELHA USANDO UMA VARIAVEL INTEIRA COMO ESTRUTURA DE DADOS
 *  OU SEJA, UMA VARIÁVEL QUE GUARDA A MATRIZ VETORIZADA EM BITS.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
enum{ O, X };


void mostrar(void){
    uint k = 0ul, aux, op;
    for(uint i=0; i<TAM; i++){
        for(uint j=0; j<TAM; j++){
            aux = (i*TAM+j)<<1;
            k = 1ul<<(aux+1) & velha;
            if(k){
                op = 1ul<<(aux) & velha;
                if(op)
                    printf("X ");
                else
                    printf("O ");
            }
            else
                printf(" | ");
        }
        printf("\n");

    }
}

void jogar(uchar player){
    usint casa;
    uint aux = 2;
    while(true){
        printf("Jogue em uma casa: ");
        scanf("%hd%*c", &casa);
        if(!(aux << ((casa-1)*2) & velha)) break; // VERIFICA SE A JOGADA É LEGAL
        printf("Célula já ocupada! Tente novamente, jogador %c!\n\n", (player == X) ? 'X':'O');
    }
    if(player == X)
        aux |= 1;
    velha |= (aux << ((casa-1)*2));
    mostrar();
}

bool ganhou(uint x){
    if(x == TAM){
        puts("Jogador 2 (X) ganhou!");
        return true;
    }
    else if(!x){
        puts("Jogador 1 (O) ganhou!");
        return true;
    }
    return false;
}

bool vitoria(void){//condições de vitoria
    return linha() || coluna() || diagonal();
}

bool linha(void){
    for(uint i=0, sum=0u; i<TAM; i++, sum=0u){
        for(uint j=0; j<TAM; j++)
            sum += (1ul<<((i*TAM+j)*2+1) & velha)?1:0;

        if(sum == TAM){
            sum = 0u;
            for(uint j=0; j<TAM; j++)
                sum += (1ul<<((i*TAM+j)*2) & velha)?1:0;
            if(ganhou(sum)) return true;
        }
    }
    return false;
}

bool coluna(void){
    for(uint i=0, sum=0; i<TAM; i++, sum=0){
        for(uint j=0; j<TAM; j++)
            sum += (1ul<<((1+i+j*TAM)*2-1) & velha)?1:0;
        
        if(sum == TAM){
            sum = 0;
            for(uint j=0; j<TAM; j++)
                sum += (1ul<<((1+i+j*TAM)*2-2) & velha)?1:0;
            if(ganhou(sum)) return true;
        }
    }
    return false;
}

bool diagonal(void){
    uint sum_sd=0, sum_pd=0;
    for(uint j=0; j<TAM; j++){
        sum_pd += (1ull<<((j*(TAM+1))*2+1) & velha)?1:0;
        sum_sd += (1ull<<((TAM+j*(TAM+1)+2)) & velha)?1:0;
    }

    if(sum_pd == TAM || sum_sd == TAM){
        sum_pd = (sum_pd == TAM) ? 0:TAM+TAM;
        sum_sd = (sum_sd == TAM) ? 0:TAM+TAM;
        for(uint j=0; j<TAM; j++){
            sum_pd += (1ull<<((j*(TAM+1))*2) & velha)?1:0;
            sum_sd += (1ull<<((TAM+j*(TAM+1)+1)) & velha)?1:0;
        }
        if(ganhou(sum_pd) || ganhou(sum_sd)) return true;
    }
    return false;
}

int main(){
    for(uint i=0; i<TAM*TAM; i++){
        jogar(i%2);
        if(i>=2)
            if(vitoria())
                return 0;
    }
    return 1;
}
