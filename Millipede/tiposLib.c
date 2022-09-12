#include <raylib.h>
#include "consGlobaisLib.c"

// DIRECAO
typedef enum
{
ESQ,
DIR,
CIMA,
BAIXO,
DIR_CIMA,
DIR_BAIXO,
ESQ_CIMA,
ESQ_BAIXO,
} DIRECAO;

// ARANHA
typedef struct aranha{
    Vector2 pos;
    int dir;
} ARANHA;

// Fazendeiro
typedef struct
{
    char NomeJogador[TAMNOME];
    Vector2 posicao;
    int vidas;
    DIRECAO direcao;
    int cogumelos_colhidos; //inicializa em zero
    int tiros; //inicializa em 200
    DIRECAO dirTiro;
    int doente; //qtos cogumelos para curar, zero se estiver sao
    int status; // Livre, Paralisado, ou Morto. Pode definir enumeracao
} FAZENDEIRO;
