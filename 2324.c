#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int pontosGlobal = 0;
int movR[4] = {-1, 1, 0, 0};
int movC[4] = {0, 0, -1, 1};

typedef struct {
  char movimento;
  int valor;
} vertigem;


typedef struct {
  int rows;
  int cols;
  char nome[100];
  int pontos;
  vertigem matriz[100][100];
} mapas;

int palindromo(char *s);
void printResult(mapas *mapa, int n);

int main() {
  int n;
  int row = 0, col = 0;
  int pontosRodada = 0;
  int condicao = 1;
  int j = 0;

  scanf("%d", &n);
  if (n < 1 || n > 100) {
    return 0;
  }

  mapas mapa[n];

  int i;
  while(i < n) {
    int rows, cols, num, movimento;
    char *c;
    scanf("%d %d", &rows, &cols);

    char nome[100];
    scanf("%s", nome);

    mapa[i].rows = rows;
    mapa[i].cols = cols;
    mapa[i].pontos = 0;
    strcpy(mapa[i].nome, nome);

    int j = 0;
    while(j < rows) {
      int k = 0;
      while(k < cols) {
        scanf("%d%c%d", &movimento, &c, &num);
        mapa[i].matriz[j][k].movimento = movimento;
        mapa[i].matriz[j][k].valor = num;
        k++;
      }
      j++;
    }
    i++;
  }



  while(condicao){
    int movimento = mapa[j].matriz[row][col].movimento;
    int pontuacao = mapa[j].matriz[row][col].valor;
  

    // adiciona a pontuacao da rodada
    if (movimento != 4) {
      pontosRodada += pontuacao;
    }

    // se chegar no final do mapa acaba o mapa
    if(col == mapa[j].cols - 1 && row == mapa[j].rows - 1) {
        int pontos; 
        if(palindromo(mapa[j].nome) == 1) {
            pontos = pontosRodada * 2;
        } else {
            pontos = pontosRodada;
        }     
        pontosGlobal = pontosGlobal + pontos; 
        mapa[j].pontos = mapa[j].pontos + pontos;
        break;
    }

      if(movimento == 4) {
        int pontos;
        if(palindromo(mapa[j].nome) == 1) {
            pontos = pontosRodada * 4;
        } else {
            pontos = pontosRodada;
        }
        
        pontosGlobal = pontosGlobal + pontos; 
        mapa[j].pontos = mapa[j].pontos + pontos;
        j = pontuacao;
        pontosRodada = 0;


        // se o numero de pontos for maior que a dimensao do mapa, o jogador volta ao inicio
        // do contrario, ele vai para a posicao correspondente ao numero de pontos
        int dimensao = mapa[j].rows * mapa[j].cols;
        int prox = pontosGlobal % dimensao; // proxima posicao
        int operacao = (prox / mapa[j].cols); // obtem a linha
        int operacao2 = (prox % mapa[j].cols); // obtem a coluna
        row = operacao;
        col = operacao2;
    }

    if(movimento != 4){
      row += movR[movimento];
      row += mapa[j].rows;
      row %= mapa[j].rows;
      col += movC[movimento];
      col += mapa[j].cols;
      col %= mapa[j].cols;
    }
    
    
    }


  printResult(mapa, n);

  return 0;
}

int palindromo(char *str) {
  int len = strlen(str);
  int i = 0;
  int j = len - 1;

  while (i < j) {
    if (str[i] != str[j]) {
      return 0;
    }
    i++;
    j--;
  }
  return 1;
}

void printResult(mapas *mapa, int n) {
  if (mapa == NULL) {
    return;
  }
  printf("%d\n", pontosGlobal);

  for (int i = 0; i < n; i++) {
    printf("%s %d\n", mapa[i].nome, mapa[i].pontos);
  }
}