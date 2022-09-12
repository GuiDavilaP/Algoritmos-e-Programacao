#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMNOME 31
#define TAMRANK 6
#define TAMPONT 10

typedef struct jogador{
    char nome[TAMNOME];
    int pontuacao;
} JOGADOR;

int leRanking(JOGADOR ranking[TAMRANK], char nomeArq[]){
    FILE *arq;
    char linhaRank[TAMNOME + TAMPONT];
    int count = 0;

    if((arq = fopen(nomeArq, "r")) == NULL)
        printf(" Arquivo nao existe ou nao pode ser aberto!");
    else{
       printf(" Arquivo aberto leitura\n");

       while(fgets(linhaRank, sizeof(linhaRank), arq)){
            strcpy(ranking[count].nome, strtok(linhaRank,";"));
            ranking[count].pontuacao = atoi(strtok(NULL,";"));
            //printf("n: %s, p: %i\n", ranking[count].nome, ranking[count].pontuacao);
            count++;
       }
       fclose(arq);
    }
    return count;
}

void ordenaJogadores(JOGADOR ranking[]){
    int ordenado, i, numsDesord = TAMRANK - 1;
    JOGADOR aux;
    do{
        ordenado = 1;
        for(i = 0; i < numsDesord; i++, numsDesord--){
            if(ranking[i].pontuacao < ranking[i+1].pontuacao){
                aux = ranking[i+1];
                ranking[i+1] = ranking[i];
                ranking[i] = aux;
                ordenado = 0;
            }
        }
    } while (!ordenado);
}

void imprimeRanking(JOGADOR ranking[]){
    int i;
    for(i = 0; i < TAMRANK-1 && ranking[i].pontuacao != 0; i++)
        printf(" %i -- %6i -- %s\n",i+1, ranking[i].pontuacao, ranking[i].nome);
    printf("\n");
}

int saveRanking(JOGADOR ranking[], char nomeArq[]){
    FILE *arq;
    char linhaRank[TAMNOME + TAMPONT], pontuacaoStr[TAMPONT];
    int count = 0;

    if((arq = fopen(nomeArq, "w")) == NULL)
        printf(" Arquivo nao existe ou nao pode ser aberto!");
    else{
       printf(" Arquivo aberto escrita\n");

       while(ranking[count].pontuacao != 0){
            strcpy(linhaRank, strcat(ranking[count].nome, ";"));
            itoa(ranking[count].pontuacao, pontuacaoStr, 10);
            strcpy(linhaRank, strcat(linhaRank, pontuacaoStr));
            strcpy(linhaRank, strcat(linhaRank, ";"));
            //printf("Salvo: %s \n", linhaRank);
            fputs(linhaRank, arq);
            // Vai para a próxima linha.
            fputc('\n', arq);
            count++;
       }
       fclose(arq);
    }
    return count;
}

int main()
{
    JOGADOR ranking[TAMRANK] = {0};

    leRanking(ranking, "Teste.txt");
    imprimeRanking(ranking);

    ordenaJogadores(ranking);
    saveRanking(ranking, "TesteOrdenado.txt");
    leRanking(ranking, "TesteOrdenado.txt");
    imprimeRanking(ranking);

    return 0;
}
