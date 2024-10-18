#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/* 
    Laboratório de Programação I / 2024-2
    T3 - Programa com repetição (Trick or treats)
    Profª Patrícia Pitthan
    
    Aluno: Thiago Miller de Campos Viana
    Matrícula: 202312133
    Data: 18/10/2024 
*/

int escolherDados();
int escolherTrick1();
int escolherTrick2(int trick1);
int escolherTreat(int trick1, int trick2);
int rolarDado();
int jogarDados(int dados, int trick1, int trick2, int treat);
int jogarRodada(int rodada, char nome_jogador[], int dados, int trick1, int trick2, int treat);
void jogarPartida(char nome_jogador[]);
void determinarVencedor(char nome_jogador[], int pontos_jogador, int pontos_computador);
bool jogarNovamente();

#define MAX_CHAR 10     // Quantidade máxima de caracteres do nome do jogador
#define MIN_DADOS 1     // Número mínimo de dados que um jogador pode escolher
#define MAX_RODADAS 3   // Numero máximo de rodadas por partida
#define MIN_DADO 1      // Menor valor de um dado
#define MAX_DADO 6      // Maior valor de um dado

int main(){

    // Imprime o título do jogo
    printf("*** Trick or Treat ***\n");
    
    // Lê o nome do jogador
    char nome_jogador[MAX_CHAR];
    printf("Digite seu nome: ");
    scanf("%s", &nome_jogador);

    // Gera a seed para geração de números aleatórios
    srand(time(NULL));

    // Inicializa a variável que determina se haverá um novo jogo
    bool jogar = true;

    // Laço principal de jogo
    while(jogar) {

        // Inicializa uma partida, passando o nome do jogador
        jogarPartida(nome_jogador);

        // Pede ao usuário que informe se jogará novamente após o término de uma partida
        jogar = jogarNovamente();
    }

    // Encerra a execução do programa
    return 0;
}

int escolherDados(){
    // Retorna quantos dados cada jogador irá ter no início de cada rodada, respeitando o limite mínimo de 1 dado
    
    int dados;
    
    do {
        printf("Digite quantidade de dados maior que 0 (d): ");
        scanf("%d", &dados);
    } while (dados < MIN_DADOS);

    return dados;   
}

int escolherTrick1(){
    // Retorna o primeiro valor do dado correspondente à travessura, respeitando os valores mínimo e máximo do dado 
   
    int trick1; 

    do {
        printf("Digite valor entre 1 e 6 para trick1 (x): ");
        scanf("%d", &trick1);
    } while (trick1 < MIN_DADO || trick1 > MAX_DADO);

    return trick1;
}
 
int escolherTrick2(int trick1){
    // Retorna o segundo valor do dado correspondente à travessura, respeitando os valores mínimo e máximo do dado e outros valores já selecionados

    int trick2; 

    do {
        printf("Digite valor diferente entre 1 e 6 para trick2 (y): ");
        scanf("%d", &trick2);
    } while (trick2 < MIN_DADO || trick2 > MAX_DADO || trick2 == trick1);

    return trick2;
}

int escolherTreat(int trick1, int trick2){
    // Retorna o valor do dado correspondente à gostosura, respeitando os valores mínimo e máximo do dado e outros valores já selecionados

    int treat; 

    do {
        printf("Digite valor diferente entre 1 e 6 para treat (z): ");
        scanf("%d", &treat);
    } while (treat < MIN_DADO || treat > MAX_DADO || treat == trick1 || treat == trick2);

    return treat;
}

int rolarDado(){
    // Retorna um dado de tantas faces quanto o valor máximo do dado, de acordo com a seed gerada na função main

    int resultado = rand() % MAX_DADO + 1;

    return resultado;
}

int jogarDados(int dados, int trick1, int trick2, int treat){
    // Retorna a pontuação do jogador após esgotar todos os seus dados

    int dados_restantes = dados;    // Dados restantes após cada jogada
    int pontos_dados = 0;           // Pontuação total obtida até o jogador perder todos os dados
    int pontos_temp = 0;            // Pontuação temporária após cada jogada
    int tricks_total = 0;           // Quantidade de travessuras obtidas até o jogador perder todos os dados
    int treats_total = 0;           // Quantidade de gostosuras obtidas até o jogador perder todos os dados

    bool resultou_trick = false;            // Informa se houve travessuras até o jogador perder todos os dados
    bool resultou_treat = false;            // Informa se houve gostosuras até o jogador perder todos os dados

    while(dados_restantes > 0){
    // Realiza jogadas até que o jogador não tenha mais dados restantes

        printf("Dados: \n");
        
        for (int dado = 1; dado <= dados_restantes; dado++){
            // Joga dados de acordo com os dados restantes

            int resultado = rolarDado();
            printf("dado %d = %d; ", dado, resultado);

            // Testa se o resultado do dado é travessura
            if (resultado == trick1 || resultado == trick2){
                tricks_total++;
                if(!resultou_trick)
                    resultou_trick = true;
            }

            // Testa se o resultado do dado é gostosura
            if (resultado == treat){
                treats_total++;
                if(!resultou_treat)
                    resultou_treat = true;
            }

            // Guarda a pontuação temporária dependendo dos valores dos dados jogados
            if (!resultou_trick){
                pontos_temp += resultado;
            } else if (resultou_treat){
                pontos_temp = treats_total * 3;
            } else {
                pontos_temp = 0;
            }       
        }

        // Adiciona a pontuação temporária obtida à pontuação total dos dados jogados
        pontos_dados += pontos_temp;

        printf("\nPontos: %d\n\n", pontos_dados);

        // Diminui o número de dados restantes de acordo com o número de travessuras obtidas em uma jogada
        dados_restantes -= tricks_total;

        // Restaura os valores das variáveis para a próxima jogada
        pontos_temp = 0;
        tricks_total = 0;
        treats_total = 0;
        resultou_trick = false;
        resultou_treat = false;
    }

    return pontos_dados;
}

int jogarRodada(int rodada, char nome_jogador[], int dados, int trick1, int trick2, int treat){
    // Retorna os pontos obtidos por um jogador em uma rodada
    
    printf("\n%s - Rodada %d\n", nome_jogador, rodada);

	int pontos_rodada = jogarDados(dados, trick1, trick2, treat);

	printf("Pontuacao da rodada: %d\n", pontos_rodada);
    printf("-----------------------\n");

	return pontos_rodada;
}

void determinarVencedor(char nome_jogador[], int pontos_jogador, int pontos_computador){
    // Imprime o vencedor da partida após comparar a pontuação total de cada jogador
    
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
    // Inicializa uma partida de Trick or Treat
    
    // Lê a quantidade de dados e valores de travessura e gostosura
    int dados = escolherDados();
    int trick1 = escolherTrick1();
    int trick2 = escolherTrick2(trick1);
    int treat = escolherTreat(trick1, trick2);

    // Pontuação total de cada jogador
    int pontos_jogador = 0;
    int pontos_computador = 0;

    // Realiza as rodadas de jogo para cada jogador, até o limite máximo de rodadas
    for(int rodada = 1; rodada <= MAX_RODADAS; rodada++){

        pontos_jogador += jogarRodada(rodada, nome_jogador, dados, trick1, trick2, treat);

        pontos_computador += jogarRodada(rodada, "Computador", dados, trick1, trick2, treat);

    }

    // Determina o vencedor
    determinarVencedor(nome_jogador, pontos_jogador, pontos_computador);

}

bool jogarNovamente(){
    // Retorna se o jogador irá iniciar uma nova partida
    
    char novo_jogo = 'n'; 
    bool jogar;

    // Valida a entrada do jogador
    while(novo_jogo != 's' && novo_jogo != 'n'){ 
        // printf("Gostaria de jogar novamente? (s/n): ");
        // scanf(" %c", &novo_jogo);
    }

    // Altera o valor da variável booleana de acordo com a resposta do jogador
    switch(novo_jogo){
        case 's' : 
            jogar = true;
            break;
        case 'n' : 
            jogar = false;
            break;
    }

    return jogar;
}
