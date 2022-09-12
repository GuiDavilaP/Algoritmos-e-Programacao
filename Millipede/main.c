#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tiposLib.c"
#include "consGlobaisLib.c"



//FUNCOES
void gera_milipede (int posicao[], int *segmentos, int *DIR, int tamanho){
    int direcoes[2] = {6, 2};
    posicao[0] = rand()%T_LARGURA;
    posicao[1] = tamanho;
    *DIR = direcoes[rand()%2];
    *segmentos = rand()%6;
}

void gera_fazendeiro (FAZENDEIRO *fazendeiro){
    fazendeiro->doente = 0;
    fazendeiro->cogumelos_colhidos = 0;
    fazendeiro->tiros = 200;
    fazendeiro->vidas = 3;
    fazendeiro->posicao.x = (int)(rand()/(double)RAND_MAX*T_LARGURA);
    fazendeiro->posicao.y = (int)(rand()/(double)RAND_MAX*T_ALTURA);
}

void gera_aranhas(ARANHA aranha[]);
void desenha_aranhas(ARANHA aranha[]);
void move_aranhas(ARANHA aranha[NUM_ARANHA], float velocidade, FAZENDEIRO *jogador);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int SizePlayer = 20;
    const float SpeedPlayer = 5;

    int score = 675;
    int ammo = 124;

    //Aranha
    ARANHA aranha[3];
    int vel_aranha = 3;

    //Milipede
    int coord_mili [2]; // coordenada da cabeça da milípede
    int segmentos; // numero de segmentos da milípede
    int dir_mili ; // direção de movimentação da milípede , um valor de 6 ou de 2
    int tam_mili = 15;

    //Fazendeiro
    FAZENDEIRO fazendeiro;

    srand(time(0));

    // Gera elementos
    gera_aranhas(aranha);
    gera_milipede(coord_mili, &segmentos, &dir_mili, tam_mili);
    gera_fazendeiro(&fazendeiro);

    //Inicia janela.
    InitWindow(T_LARGURA, T_ALTURA, "raylib [core] example - keyboard input");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_RIGHT) && fazendeiro.posicao.x < T_LARGURA - SizePlayer) fazendeiro.posicao.x += SpeedPlayer;
        if (IsKeyDown(KEY_LEFT) && fazendeiro.posicao.x >  SizePlayer) fazendeiro.posicao.x -= SpeedPlayer;
        if (IsKeyDown(KEY_UP) && fazendeiro.posicao.y > SizePlayer) fazendeiro.posicao.y -= SpeedPlayer;
        if (IsKeyDown(KEY_DOWN) && fazendeiro.posicao.y < T_ALTURA -  SizePlayer) fazendeiro.posicao.y += SpeedPlayer;

        move_aranhas(aranha, vel_aranha, &fazendeiro);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            DrawText(TextFormat("%i",coord_mili[0]), 200, 20, 50, MAROON);
            DrawText(TextFormat("%i",segmentos), 50, 20, 50, MAROON);
            DrawCircle(coord_mili[0], coord_mili[1], 15, GREEN);

            ClearBackground(BLACK);

            if(fazendeiro.doente > 0)
                DrawCircle(fazendeiro.posicao.x, fazendeiro.posicao.y, SizePlayer, GREEN);
            else
                DrawCircle(fazendeiro.posicao.x, fazendeiro.posicao.y, SizePlayer, RED);
            desenha_aranhas(aranha);

            //DrawText(TextFormat("%i",ammo), 50, 20, 50, MAROON);
            //DrawText(TextFormat("%i",score), 200, 20, 50, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
