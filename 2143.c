#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


typedef struct Toke{
  char food[50];
  struct Pilha*next;
} toke;

typedef struct Node {
  toke *pilha;
} node;


char *strToke(char *str, char *elemento) {
  char *token = strtok(str, elemento);
  return token;
}

void enqueue(node *head, char *food) {
  toke *new = (toke *)malloc(sizeof(toke));
  strcpy(new->food, food);
  
  if (new != NULL) {
    strcpy(new->food, food);
    new->next = head->pilha;
    head->pilha = new;
  }
}

void dequeue(node *head) {
  toke *aux = head->pilha;
  head->pilha = head->pilha->next;
  free(aux);
  return;
}

void print (node *head) {
  toke *aux = head->pilha;
  while(aux != NULL) {
    printf("%s ", aux->food);
    aux = aux->next;
  }
  printf("\n");
}

int main() {
  node *array;
  array = (node *)malloc(10 * sizeof(node));

  // aloca memoria para cada pilha
  for (int i = 0; i < 10; i++) {
    array[i].pilha = (toke *)malloc(sizeof(toke));
  }

  char *strInput;
  char *strOutput;
  // alocate memory for strOutput
  strOutput = (char *)malloc(sizeof(char) * 1024);
  strInput = (char *)malloc(sizeof(char) * 1024);

  for (int i = 0; i < 10; i++) {
    scanf(" %[^\n]s", strInput);
    strcpy(strOutput, strInput);
    // remove the " " from the string
    char *token = strToke(strOutput, " ");
    // add the string to the array except the " "
    while(token != NULL) {
      enqueue(&array[i], token);
      token = strToke(NULL, " ");
    }
  }


  // print the array
  // for (int i = 0; i < 10; i++) {
  //   print(&array[i]);
  // }


  // array to alocate the prices of each food
  float *prices = (float *)malloc(sizeof(float) * 10);
  float globalPrice = 0;

  // scan the prices
  for (int i = 0; i < 10; i++) {
    float amount;
    scanf("%f", &amount);
    prices[i] = amount;
  }

  // scan the desired food and calculate the price
  while(scanf("%s", strInput) != EOF) {
    for (int i = 0; i < 10; i++) {
      if (array[i].pilha == NULL) {
        continue;
      }

      if (strcmp(array[i].pilha->food, strInput) == 0) {
        if (i == 5) {
          printf("Opa, um item 0800!\n");
          dequeue(&array[i]);
          break;
        } else {
          globalPrice += prices[i];
          dequeue(&array[i]);
          break;
        }
      } 
      
      if (i == 9) {
        printf("Nao temos %s disponivel no momento.\n", strInput);
      }
    }
  }

  printf("Compras realizadas com sucesso. Voce gastou R$%.2f.", globalPrice);

  return 0;
}
