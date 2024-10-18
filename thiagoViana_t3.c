#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int escolherDados();
int escolherTrick1(int jogador);
int escolherTrick2(int jogador, int trick1);
int escolherTreat(int jogador, int trick1, int trick2);
int rolarDado();
int jogarDados(int dados, int trick1, int trick2, int treat);
int jogarRodada(int rodada, char nome_jogador[], int dados, int trick1, int trick2, int treat);
void jogarPartida(char nome_jogador[]);
void determinarVencedor(char nome_jogador[], int pontos_jogador, int pontos_computador);
bool jogarNovamente();

#define MAX_CHAR 10
#define MIN_DADOS 1
#define MAX_RODADAS 3
#define JOGADOR 0
#define COMPUTADOR 1


int main(){

    printf("*** Trick or Treat ***\n");
    
    char nome_jogador[MAX_CHAR];
    printf("Digite seu nome: ");
    scanf("%s", &nome_jogador);

    srand(time(NULL));

    bool jogar = true;

    while(jogar) {    
        jogarPartida(nome_jogador);
        jogar = jogarNovamente();
    }

    return 0;
}

int escolherDados(){
    
    int dados;
    
    do {
        printf("Digite quantidade de dados maior que 0 (d): ");
        scanf("%d", &dados);
    } while (dados < MIN_DADOS);

    return dados;   
}

int escolherTrick1(int jogador){
   
    int trick1;

    do {
        printf("Digite valor entre 1 e 6 para trick1 (x): ");

        switch(jogador){
            case JOGADOR : scanf("%d", &trick1);
                break;
            case COMPUTADOR : trick1 = rolarDado();
                break;
        }
        
    } while (trick1 < 1 || trick1 > 6);

    return trick1;
}
 
int escolherTrick2(int jogador, int trick1){

    int trick2;

    do {
        printf("Digite valor diferente entre 1 e 6 para trick2 (y): ");

        switch(jogador){
            case JOGADOR : scanf("%d", &trick2);
                break;
            case COMPUTADOR : trick2 = rolarDado();
                break;
        }

    } while (trick2 < 1 || trick2 > 6 || trick2 == trick1);

    return trick2;
}

int escolherTreat(int jogador, int trick1, int trick2){

    int treat;

    do{
        printf("Digite valor diferente entre 1 e 6 para treat (z): ");

        switch(jogador){
            case JOGADOR : scanf("%d", &treat);
                break;
            case COMPUTADOR : treat = rolarDado();
                break;
        }

    } while (treat < 1 || treat > 6 || treat == trick1 || treat == trick2);

    return treat;
}

int rolarDado(){

    int resultado = rand() % 6 + 1;

    return resultado;
}

int jogarDados(int dados, int trick1, int trick2, int treat){

    int dados_restantes = dados;
    int pontos = 0;
    int pontos_temp = 0;
    int tricks_total = 0;
    int treats_total = 0;

    bool resultou_trick;
    bool resultou_treat;

    while(dados_restantes > 0){

        printf("Dados: \n");
        
        for (int dado = 1; dado <= dados_restantes; dado++){
            int resultado = rolarDado();
            printf("dado %d = %d; ", dado, resultado);

            if (resultado == trick1 || resultado == trick2){
                tricks_total++;
                if(!resultou_trick)
                    resultou_trick = true;
            }

            if (resultado == treat){
                treats_total++;
                if(!resultou_treat)
                    resultou_treat = true;
            }

            if (!resultou_trick){
                pontos_temp += resultado;
            } else if (resultou_treat){
                pontos_temp = treats_total * 3;
            } else {
                pontos_temp = 0;
            }       
        }

        pontos += pontos_temp;
        printf("\nPontos: %d\n\n", pontos);

        dados_restantes -= tricks_total;

        pontos_temp = 0;
        tricks_total = 0;
        treats_total = 0;
        resultou_trick = false;
        resultou_treat = false;
    }

    return pontos;
}

int jogarRodada(int rodada, char nome_jogador[], int dados, int trick1, int trick2, int treat){
    
    printf("\n%s - Rodada %d\n", nome_jogador, rodada);

	int pontos_rodada = jogarDados(dados, trick1, trick2, treat);

	printf("Pontuacao da rodada: %d\n", pontos_rodada);
    printf("-----------------------\n\n");

	return pontos_rodada;
}

void determinarVencedor(char nome_jogador[], int pontos_jogador, int pontos_computador){
    
    printf("%s: %d\n", nome_jogador, pontos_jogador);
    printf("Computador: %d\n\n", pontos_computador);

    if (pontos_jogador > pontos_computador){
        printf("%s venceu!\n\n", nome_jogador);
    } else if (pontos_computador > pontos_jogador){
        printf("Computador venceu!\n\n");
    } else {
        printf("Empate!\n\n");
    }

}

void jogarPartida (char nome_jogador[]){

    int dados = escolherDados();
    int trick1_jogador = escolherTrick1(JOGADOR);
    int trick2_jogador = escolherTrick2(JOGADOR, trick1_jogador);
    int treat_jogador = escolherTreat(JOGADOR, trick1_jogador, trick2_jogador);

    int trick1_computador = escolherTrick1(COMPUTADOR);
    int trick2_computador = escolherTrick2(COMPUTADOR, trick1_computador);
    int treat_computador = escolherTreat(COMPUTADOR, trick1_computador, trick2_computador);

    int pontos_jogador = 0;
    int pontos_computador = 0;

    for(int rodada = 1; rodada <= MAX_RODADAS; rodada++){

        pontos_jogador += jogarRodada(rodada, nome_jogador, dados, trick1_jogador, trick2_jogador, treat_jogador);

        pontos_computador += jogarRodada(rodada, "Computador", dados, trick1_computador, trick2_computador, treat_computador);

    }

    determinarVencedor(nome_jogador, pontos_jogador, pontos_computador);

}

bool jogarNovamente(){
    
    char novo_jogo;
    bool jogar;


    while(novo_jogo != 's' && novo_jogo != 'n'){
        printf("Gostaria de jogar novamente? (s/n): ");
        scanf("%c", &novo_jogo);
    }

    switch(novo_jogo){
        case 's' : jogar = true;
            break;
        case 'n' : jogar = false;
            break;
    }

    return jogar;
}