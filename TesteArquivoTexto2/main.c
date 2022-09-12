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
            ranking[count].pontuacao = atoi(strtok(NULL,"\n"));
            //printf("n: %s, p: %i\n", ranking[count].nome, ranking[count].pontuacao);
            count++;
       }
       fclose(arq);
    }
    return count;
}

void ordenaJogadores(JOGADOR ranking[]){
    int ordenado, i, j, numsDesord = TAMRANK;
    JOGADOR aux;
    do{
        ordenado = 1;
        for(i = 0; i < numsDesord; i++, numsDesord--){
            for(j = 0; j < TAMRANK-1; j++){
                if(ranking[j].pontuacao < ranking[j+1].pontuacao){
                    //printf("\npont1: %s pont2: %s\n", ranking[j].nome, ranking[j+1].nome);
                    aux = ranking[j+1];
                    ranking[j+1] = ranking[j];
                    ranking[j] = aux;
                    ordenado = 0;
                }
            }
            //printf("\nOrdenaJogadores \n");
            //imprimeRanking(ranking);
        }
    } while (!ordenado);
    printf("\n");
}

void imprimeRanking(JOGADOR ranking[]){
    int i;
    for(i = 0; i < TAMRANK; i++)
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

int checaDuplicata(JOGADOR ranking[], JOGADOR jog){
    int count = 0, modificou = 0;

    while(count < TAMRANK-1){
        if(strcmp(jog.nome, ranking[count].nome) == 0){
           if(jog.pontuacao > ranking[count].pontuacao){
            ranking[count] = jog;
            modificou = 1;
           }
        }
        count++;
    }
    return modificou;
}

int insereJog(JOGADOR ranking[], JOGADOR jog){
    int count=0, jogadorCount = 0, inserido = 0;

    if (!checaDuplicata(ranking, jog)){
        do{
            if(ranking[count].pontuacao == 0){
                ranking[count] = jog;
                inserido = 1;
            }
            count++;
        } while (inserido == 0 && count < TAMRANK);
        if(inserido == 0)
            ranking[TAMRANK-1] = jog;
    }
    //printf("\n!!! INSERE JOGADOR %s %d\n", ranking[TAMRANK-1].nome, ranking[TAMRANK-1].pontuacao);

    return jogadorCount;
}

int main()
{
    JOGADOR ranking[TAMRANK] = {0}, teste;
    strcpy(teste.nome, "teste");
    teste.pontuacao = 700;

    leRanking(ranking, "Teste.txt");
    imprimeRanking(ranking);

    insereJog(ranking, teste);
    ordenaJogadores(ranking);
    imprimeRanking(ranking);

    saveRanking(ranking, "TesteOrdenado.txt");
    leRanking(ranking, "TesteOrdenado.txt");
    imprimeRanking(ranking);

    return 0;
}
