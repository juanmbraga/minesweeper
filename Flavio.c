#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>

int main(void) {
  int inputMenu, i, j, bombai, bombaj, auxiliar2, auxiliar;
  int matriz[9][9];
  int matrizvista[9][9];


  printf("Ola bem vindo ao campo minado \n \n \n");
  printf("--------------------------------\n\n\n");
  printf("Digite '1' para iniciar o jogo\n\n\n");
  printf("Digite '2' para ver as regras e como jogar\n\n\n");
  printf("Digite '3' para acessar o ranking\n\n\n");

  scanf("%d", &inputMenu);
  if (inputMenu>3  inputMenu<0){printf("\nInsira um número válido");}
  else{
      if(inputMenu==1){
    // (1) aqui inicia-se o preenchimento da matriz nula //
    for ( i=0; i<9; i++ ){
      for ( j=0; j<9; j++ ){
     matriz[i][j]=0;

      }
    }
    srand(time(NULL));

    for(auxiliar=0; auxiliar<11; auxiliar++){
        bombai=rand() % 7;
        bombaj=rand() % 7;
        if(bombai == 0 || bombaj == 0){
            auxiliar--;
        }
        else{
        matriz[bombai][bombaj]+=10;

        //aqui comeca a distribuir as dicas nesse local de bomba//
        bombai=bombai+1;
        matriz[bombai][bombaj]++;
        bombaj=bombaj+1;
        matriz[bombai][bombaj]++;
        bombai=bombai-1;
        matriz[bombai][bombaj]++;
        bombai=bombai-1;
        matriz[bombai][bombaj]++;
        bombaj=bombaj-1;
        matriz[bombai][bombaj]++;
        bombaj=bombaj-1;
        matriz[bombai][bombaj]++;
        bombai=bombai+1;
        matriz[bombai][bombaj]++;
        bombai=bombai+1;
        matriz[bombai][bombaj]++;
        }
    }
    for ( i=0; i<9; i++ ){
      for ( j=0; j<9; j++ ){
     matrizvista[i][j]=9;
     }}
  }
}
  return 0;
}