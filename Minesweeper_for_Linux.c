#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int exibirmenu ();   //Exibe a parte grafica do menu principal
int start ();        //codigo do jogo em si
int inicializar (int matrizint[][9], char matrizchar[][9], char type);
int bombasedicas(int, int matriz[][9]); //distribui as dicas e as bombas dentro da matriz de respostas
int somardicas (int bombai, int bombaj, int matriz[][9]);
int imprimirtela (int matrizint[][9], char matrizchar[][9], int);
int fimpartida (int, int, time_t, int matriz[][9]);
int rules ();
int ranking ();

int main (void) {

    int control;

    do {
      int input;

      system("clear");
      exibirmenu();

      do 
      {
          printf("Digite a opção desejada: ");
          scanf("%d", &input);
      }
      while (input < 0 && input > 5);

      switch (input) {
          case 1: control = start();   //inicio do jogo
              break;
          case 2: control = rules();   //mostra as regras
              break;
          case 3: control = ranking(); //exibe o ranking
              break;
          case 4: control = 1;         //encerra o jogo 
              break;

          default: control = 0;        //para input errado
      }
      
    }
    while (control == 0); //As funcoes retornam 0 por padrao. Caso elas retornarem 1 o jogo encerra. 

    system("clear");
    printf("\nJogo encerrado.\n");

    return 0; //programa finalizado
}


int exibirmenu () { //Exibe a parte grafica do menu principal

    printf("Olá, bem vindo ao campo minado!\n\n\n");
    printf("--------------------------------\n\n\n");
    printf(" [1] para iniciar o jogo\n\n\n");
    printf(" [2] para ver as regras de como jogar\n\n\n");
    printf(" [3] para acessar o ranking\n\n\n");
    printf(" [4] para sair\n\n\n");

    return 0;
}


int start () { // Codigo do jogo

    int matriz[9][9];                                  //tabela com os valores de dicas e bombas (oculta)
    char matrizjogador[9][9];                          //tabela vista pelo usuario
    int linhainput, colunainput;                       //variaveis de input durante o jogo 
    int bomba, checagem, tentativas=70, numbombas=11;  //variaveis de controle
    time_t start_t, end_t;                                      //A determinar

    /* utilizado caso preferissemos adicionar niveis de dificuldade
    #include <gambiarra.h>

    int linha, coluna;
    int/char matriz[linha][coluna];
    numbombas=11;
    tentativas = ((linha*coluna) - numbombas);
    */

    inicializar(matriz, NULL, 'i');        //inicializar tabela int
    inicializar(NULL, matrizjogador, 'c'); //inicializar tabela char

    bombasedicas(numbombas, matriz);

    time(&start_t);
    

    do {
        system("clear");

        printf("\n\t\t\t\t   CAMPO MINADO\n\n");
        printf("\n\t\t\t\t\t\t\t\tTentativas restantes: %d.\n", tentativas);

        //remova o comentario para ver a tabela oculta
        //imprimirtela(matriz, matrizjogador, 1); 

        imprimirtela(NULL, matrizjogador, 2); 
        printf("Escolha a coordenada da casa para revelar.\nDigite 33 para voltar ao menu principal.\n_________________________________\n");
        
        do { //Foi optado por nao modularizar para o case 33 sair do jogo diretamente.

            printf ("\nInsira o valor da linha: ");
            scanf ("%d", &linhainput);

            switch (linhainput) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                    checagem = 0;
                    break;
                case 33:
                    return 0;
                    break;
                default:
                    checagem = 1;
            }

            printf("Insira o valor da coluna: ");
            scanf ("%d", &colunainput);

            switch (colunainput) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                    checagem = 0;
                    break;
                case 33:
                    return 0;
                    break;
                default:
                    checagem = 1;
            }
        } 
        while (checagem == 1);

        //corrigir o input do usuario para vetor multidimensional
        linhainput--; 
        colunainput--;

        if(matrizjogador[linhainput][colunainput] != '~') //checar se casa ainda nao foi revelada
            bomba = 0;

        else {

            tentativas--; //casa ainda nao revelada (ok), descontar tentativa 

            if (matriz[linhainput][colunainput] >= 10) //é bomba, perdeu!
              bomba = 1;

            else {
              bomba = 0;
              matrizjogador[linhainput][colunainput] = (matriz[linhainput][colunainput] + 48); //segundo ASCII
            }
          }
    }
    while (bomba == 0 && tentativas != 0);

    time(&end_t);

    return fimpartida (bomba, tentativas, end_t-start_t, matriz);
    //bomba para saber se ganhou ou perdeu; 
    //tentativas para ranking; 
    //tempo para ranking; 
    //matriz para exibir.
}


int inicializar (int matrizint[][9], char matrizchar[][9], char type) {
    //inicializar com zero ou espaco, os vetores multid. de tipo int e char
    
    if (type == 'i') {

        for (int i=0; i<9; i++ ){

            for (int j=0; j<9; j++ ){
                matrizint[i][j]=0;
            }
        }
    }
    else {
        if (type == 'c') {

            for (int i = 0; i<9; i++) { //inicializar como ?
            
                for (int j=0; j<9; j++) {
                    matrizchar[i][j] = '~';
                }
            }
        }
        else {
            printf("Erro de parametro.");
        }
    }

    return 0;
}


int bombasedicas (int numbombas, int matriz[][9]) {
    //distribuir as bombas e as dicas

    srand(time(NULL)); //para os números aleatórios terem o tempo como semente

    int bombai, bombaj;

    for(int auxiliar=0; auxiliar<numbombas; auxiliar++){

        bombai=rand() % 8;
        bombaj=rand() % 8;

        if(matriz[bombai][bombaj] >= 10){  //caso ja houver uma mina gera um novo numero aleatório e repete o processo
            auxiliar--;
        }
        else{
        matriz[bombai][bombaj]+=10;

        //distribuir dicas no entorno da coordenada da bomba
        
        bombai=bombai+1;
        somardicas (bombai, bombaj, matriz);

        bombaj=bombaj+1;
        somardicas (bombai, bombaj, matriz);

        bombai=bombai-1;
        somardicas (bombai, bombaj, matriz);

        bombai=bombai-1;
        somardicas (bombai, bombaj, matriz);

        bombaj=bombaj-1;
        somardicas (bombai, bombaj, matriz);

        bombaj=bombaj-1;
        somardicas (bombai, bombaj, matriz);

        bombai=bombai+1;
        somardicas (bombai, bombaj, matriz);

        bombai=bombai+1;
        somardicas (bombai, bombaj, matriz);
    }
  }

  return 0;
}


int somardicas (int bombai, int bombaj, int matriz[][9]) {
    //somar dica a casa apenas se as coordenadas estiverem no vetor 

    if ((bombai >= 0) && (bombai < 9) && (bombaj >= 0) && (bombaj < 9))
        matriz[bombai][bombaj]++;

    return 0; 
} 


int imprimirtela (int matrizint[][9], char matrizchar[][9], int define) { 
    //imprimir matrizes integer e character, usando o parametro "define"
    
    if (define == 1) { //para int

        printf("\n\n       [1]   [2]   [3]   [4]   [5]   [6]   [7]   [8]   [9]\n\n\n");

        for (int i=0; i<9; i++ ){

            printf("[%d]    ", i+1);

            for (int j=0; j<9; j++ ) {

              if (matrizint[i][j]<10)
                printf(" %d    " , matrizint[i][j]);
              else
                printf("[X]   ");
            }

            printf("\n\n\n");
        }

        return 0;
    }

    if (define == 2) { //para char

        printf("\n\n       [1]   [2]   [3]   [4]   [5]   [6]   [7]   [8]   [9]\n\n\n");

        for (int i=0; i<9; i++ ){

            printf("[%d]    ", i+1);

            for (int j=0; j<9; j++ ){
                printf(" %c    " , matrizchar[i][j]);
            }

            printf("\n\n\n");
        }

        return 0;
    }

    else {

        printf("Erro de parâmetro.");
        return 0;
    }
}


int rules () { 
    //Exibir as regras
    
    int matrizint[9][9];
    char matrizchar[9][9];

    system("clear");
    printf("\t\t\t\tRegras do Campo Minado\n");    

    //Mostrar como será o tabuleiro de jogo
    inicializar( NULL, matrizchar, 'c'); 
    imprimirtela (matrizint, matrizchar, 2);
    printf(" A tabela acima representa um campo minado.\n");
    printf("\n De inicio, todas as casas estarao escondidas,\n cabe a voce escolher as coordenadas daquela que deseja abrir.");
    printf("\n\nTome cuidado, pois se voce acertar uma mina, voce perde!");
    printf("\n\nAperte qualquer tecla e tecle enter para seguir.\n\t");
    getchar();
    getchar(); //Gambiarra aprovada pelo Monitor©


    system("clear");

    //explicar como as dicas sao distribuidas
    matrizchar[2][2] = 'X';
    matrizchar[1][1] = '1';
    matrizchar[2][1] = '1';
    matrizchar[3][1] = '1';
    matrizchar[3][2] = '1';
    matrizchar[3][3] = '1';
    matrizchar[2][3] = '1';
    matrizchar[1][3] = '1';
    matrizchar[1][2] = '1';
    printf("\t\t\t\tRegras do Campo Minado\n");
    imprimirtela(matrizint, matrizchar, 2); 
    printf("Quando houver uma bomba (X), as casas adjacentes a sua\n receberao um numero indicando a quantidade de bombas ao seu entorno.");
    printf("\n\nUse as dicas para se guiar e evitar as bombas.");
    printf("\n\nA casa de linha 3 e coluna 3 exemplifica o explicado acima.\n");
    printf("\nTecle enter para seguir.");
    getchar();

    system("clear");

    //mais sobre dicas
    matrizchar[4][4] = 'X';
    matrizchar[5][3] = '1';
    matrizchar[3][3] = '2';
    matrizchar[4][3] = '1';
    matrizchar[5][4] = '1';
    matrizchar[5][5] = '1';
    matrizchar[4][5] = '1';
    matrizchar[3][5] = '1';
    matrizchar[3][4] = '1';
    printf("\t\t\t\tRegras do Campo Minado\n");
    imprimirtela(matrizint, matrizchar, 2); 
    printf("\nQuando houver mais de uma bomba em seu entorno,\na casa mostrara este valor.\n\nIsto pode ser visto na coordenada de linha 4 e coluna 4.\n");
    printf("\nTecle enter para seguir.");
    getchar();

    system("clear");
 
    //como vencer ou perder
    printf("\t\t\t\tRegras do Campo Minado\n");
    imprimirtela(matrizint, matrizchar, 2); 
    printf("\nO jogo se encerrara em duas condicoes: \n\n1. quando a casa escolhida conter uma mina (voce perdeu!)\n2. Apos todas as casas terem sido reveladas.\n");
    printf("\nTecle enter para seguir.");
    getchar();

    system("clear");
    
    //motivacao para um jogo que depende de sorte
    printf("\t\t\t\tRegras do Campo Minado\n");
    printf("\nSeu objetivo e chegar ao fim do jogo, no menor tempo possivel.\n\n\t\tBoa sorte!!");
    printf("\n\nTecle enter para voltar ao menu.");
    getchar();

    return 0;
}


int fimpartida (int bomba, int tentativas, time_t tempo, int matriz[][9]) { 
    //A tela do fim da partida

    int input;

    struct ranking {    //criar registro contendo nome e tempo
        char nome[20];
        int tempo;
    };

    struct ranking dados;   //criando variavel dados

    system("clear");

    if (bomba != 0) { //perdeu 
        printf("\nVocê pisou em uma bomba, que pena!\n"); //idealmente um único printf seria necessário, mas ninguém merece né
        printf("Ainda lhe restavam %d tentativas, e seu tempo foi de %lld.", tentativas, (long long) tempo);
        printf("\n\nConfira a seguir os locais das bombas e das dicas.\n");

        imprimirtela(matriz, NULL, 1); //inserir a segunda matriz aqui e irrelevante
    }
    else {            //ganhou
        printf("\n\nParabéns! Você conseguiu abrir todas as casas sem pisar em nenhuma bomba!\n E seu tempo foi de %lld segundos.", (long long) tempo);
        printf("\n\n Confira a seguir os locais das bombas e das dicas.\n");

        imprimirtela(matriz, NULL, 1); //inserir a segunda matriz aqui e irrelevante

        printf("\n\nDigite seu nome de ate 20 digitos (para ficar na historia): ");
        scanf(" %s", dados.nome);
        dados.tempo= (int) tempo;   //associar valor de tempo recebido do jogo a variavel time de struct

        FILE *file;
            file = fopen("ranking", "a");
            fprintf(file, "*%s %d\n", dados.nome, dados.tempo);
            fclose(file);
    }

    printf("\nDigite '1' para voltar ao menu principal.\n\n\n");
    printf("Digite '2' para sair.\n\n\n");

    do {
        printf("O que deseja fazer?: ");
        scanf("%d", &input);
    }
    while(input != 1 && input != 2);
    
    if (input == 2) {
        return 1;
    }
    else {
       return 0; //caso usuario digite o numero, ou de algum problema, retornar ao menu principal
    } 
}


int ranking () { // Armazena o ranking com nomes dos usuarios usando struct

    system("clear");

    printf("\n\nEsta e a lista das pontuacoes dos jogos anteriores.\n");

    char ranking[400];

    FILE *file;

    file = fopen("ranking", "a"); //caso nao tenha nenhum jogo salvo ainda
    fclose(file);

    file = fopen("ranking", "r");

    while(fgets(ranking, 400, file) != NULL){

        printf("\n\n%s", ranking);
    }

    fclose(file);

    printf("\n\nDigite qualquer coisa e tecle enter pra voltar ao menu principal.");

    getchar();
    getchar();

    return 0;
}