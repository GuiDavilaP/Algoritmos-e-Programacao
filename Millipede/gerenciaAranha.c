#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tiposLib.c"
#include "consGlobaisLib.c"



void gera_aranhas(ARANHA aranha[]){
    int i;

    for(i = 0; i < NUM_ARANHA; i++){
        aranha[i].pos.x = rand()%T_LARGURA;
        aranha[i].pos.y = rand()%T_ALTURA;
        aranha[i].dir = rand()%DIRECOES;
    }
}

void desenha_aranhas(ARANHA aranha[]){
    int i;
    for(i = 0; i < NUM_ARANHA; i++)
        DrawCircle(aranha[i].pos.x, aranha[i].pos.y, 10, BLUE);
}

void inverte_movimento(ARANHA *aranha, DIRECAO lado){
    int moveEsquerda[3] = {7,6,5};
    int moveBaixo[3] = {5,4,3};
    int moveDireita[3] = {1,2,3};
    int moveCima[3] = {7,0,1};

    switch(lado){
    //Esquerda
    case ESQ:
        aranha->dir = moveDireita[rand()%2];
        break;
    //Direita
    case DIR:
        aranha->dir = moveEsquerda[rand()%2];
        break;
    //Cima
    case CIMA:
        aranha->dir = moveBaixo[rand()%2];
        break;
    //Baixo
    case BAIXO:
        aranha->dir = moveCima[rand()%2];
        break;
    }
}

int testaColisaoAranha(ARANHA ar, FAZENDEIRO jog){
    if( abs(ar.pos.x - jog.posicao.x) < 20 && abs(ar.pos.y - jog.posicao.y) < 20)
        return 1;
    else
        return 0;
}

void move_aranhas(ARANHA aranha[NUM_ARANHA], float velocidade, FAZENDEIRO *jogador){
    int i;
    float velocidade_diagonal = velocidade * 0.707;
    for(i = 0; i < NUM_ARANHA; i++){
        switch(aranha[i].dir){
        // Pra cima.
        case 0:
            aranha[i].pos.y -= velocidade;
            break;
        // Diagonal para cima e direita.
        case 1:
            aranha[i].pos.x += velocidade_diagonal;
            aranha[i].pos.y -= velocidade_diagonal;
            break;
        case 2:
            aranha[i].pos.x += velocidade;
            break;
        case 3:
            aranha[i].pos.x += velocidade_diagonal;
            aranha[i].pos.y += velocidade_diagonal;
            break;
        case 4:
            aranha[i].pos.y += velocidade;
            break;
        case 5:
            aranha[i].pos.x -= velocidade_diagonal;
            aranha[i].pos.y += velocidade_diagonal;
            break;
        case 6:
            aranha[i].pos.x -= velocidade;
            break;
        case 7:
            aranha[i].pos.x -= velocidade_diagonal;
            aranha[i].pos.y -= velocidade_diagonal;
            break;
        }

        jogador->doente += testaColisaoAranha(aranha[i], *jogador);

        // Inverte direção caso aranha encoste na parede.
        if(aranha[i].pos.x < 0){
            inverte_movimento(&aranha[i], ESQ);
        }
        if(aranha[i].pos.y > T_ALTURA){
            inverte_movimento(&aranha[i], BAIXO);
        }
        if(aranha[i].pos.x > T_LARGURA){
            inverte_movimento(&aranha[i], DIR);
        }
        if(aranha[i].pos.y < 0){
            inverte_movimento(&aranha[i], CIMA);
        }

    }
}
