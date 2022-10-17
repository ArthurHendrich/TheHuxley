#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  char nome[100];
  struct Node *next;
};
typedef struct Node node;


void afterColon(char *str) {
  int i = 0;

  while(str[i] != '\0') {
    if(str[i] == ':') {
      break;
    }
    i++;
  }

  i = i + 1;

  char *aux = (char *)malloc(sizeof(char) * 100);
  aux = &str[i];
  strcpy(str, aux);
}

char *strToke(char *str, char *elemento) {
  char *token = strtok(str, elemento);
  return token;
}

node *add(node *head, char *nome) {
  node *new = (node *)malloc(sizeof(node));
  strcpy(new->nome, nome);
  new->next = NULL;

  if(head == NULL) {
    head = new;
    return head;
  }

  node *aux = head;
  while(aux->next != NULL) {
    aux = aux->next;
  }

  aux->next = new;
  return head;
}

// remover elemento da lista
node *remover(node *head) {
  node *aux = head;
  head = head->next;
  free(aux);
  return head;
}

void print(node *head) {
  node *aux = head;
  while (aux != NULL) {
    printf("%s", aux->nome);
    aux = aux->next;
  }
}

int size(node *head) {
  int cont = 0;
  node *aux = head;
  while(aux != NULL) {
    cont++;
    aux = aux->next;
  }
  return cont;
}

// verify if string has ':'
int hasColon(char *str) {
  int aux = 0;
  int i = 0;
  while(str[i] != '\0') {
    if(str[i] == ':') {
      return aux = 1;
    }
    i++;
  }

  return aux;
}

// remove '\n' from string
void removeNewLine(char *str) {
  int i = 0;
  while(str[i] != '\0') {
    if(str[i] == '\n') {
      str[i] = '\0';
    }
    i++;
  }
}

// verify if list is empty
int isEmpty(node *head) {
  if(head == NULL) {
    return 1;
  }
  return 0;
}

int main() {
  char *ru, *area2;

  // recebe o input dos restaurantes
  scanf(" %m[^\n]", &ru);
  scanf(" %m[^\n]", &area2);

  // verify if has ':'

  // copia o valor da string para uma variavel auxiliar
  char *nomeRu = (char *)malloc(sizeof(char) * 100);
  strcpy(nomeRu, ru);
  char *nomeArea2 = (char *)malloc(sizeof(char) * 100);
  strcpy(nomeArea2, area2);

  // salva o valor depois dos dois pontos  e armazena novamente
  char *comidaRu = (char *)malloc(sizeof(char) * 100);
  strcpy(comidaRu, ru);
  char *comidaArea2 = (char *)malloc(sizeof(char) * 100);
  strcpy(comidaArea2, area2);

  afterColon(comidaRu);
  afterColon(comidaArea2);


  // salva o valor antes dos dois pontos e armazena novamente
  nomeRu = strToke(nomeRu, ":");
  nomeArea2 = strToke(nomeArea2, ":");


  // iniciar as filas
  node *head1 = NULL; // fila do RU
  node *head2 = NULL; // fila do Area2


  // criando os clientes
  char *entrada = (char *)malloc(sizeof(char) * 100);
  char *comida = (char *)malloc(sizeof(char) * 100);
  char *nome = (char *)malloc(sizeof(char) * 100);
  char *saida = (char *)malloc(sizeof(char) * 100);

  int sizeRu = 0; // tamanho da fila do RU
  int sizeArea2= 0; // tamanho da fila do Area2

  // come?ar a ler os inputs e armazenar na fila
  do {

    if(fgets(entrada, 100, stdin) == NULL) {
      break;
    }
    
    if(entrada[0] != '\n') {


      strcpy(comida, entrada);
      strcpy(nome, entrada);

      saida = strcpy(saida, nome);
      afterColon(saida);
      int hasSaida;
      hasSaida = hasColon(saida);
      if(hasSaida == 0) {
        removeNewLine(saida);
      }

      int has;
      has = hasColon(nome);
      if(has == 0) {
        removeNewLine(nome);
      }
      
      nome = strToke(nome, ":");  // nome do cliente

      afterColon(comida);

      int hasComida;
      hasComida = hasColon(comida);
      if(hasComida == 0) {
        removeNewLine(comida);
      }

      if (strcmp(nome, "SAIU") != 0) {
        if(strcmp(comida, comidaRu) == 0 && strcmp(comida, comidaArea2) != 0) {
          head1 = add(head1, nome);
          printf("\n%s foi para a fila do RU", nome);

        } else if(strcmp(comida, comidaArea2) == 0 && strcmp(comida, comidaRu) != 0) {
          head2 = add(head2, nome);
          printf("\n%s foi para a fila da Area 2", nome);

        } else {
          sizeRu = size(head1);
          sizeArea2 = size(head2);

          if (sizeRu == sizeArea2) {
            head2 = add(head2, nome);
            printf("\n%s foi para a fila da Area 2", nome);

          } else if (sizeRu > sizeArea2) {
            head2 = add(head2, nome);
            printf("\n%s foi para a fila da Area 2", nome);

          } else {
            head1 = add(head1, nome);
            printf("\n%s foi para a fila do RU", nome);
          }
        }
      } else {

        if (saida[0] == 'A') {
          // cliente saiu da fila do Area2
          if(isEmpty(head2) == 0) {
            printf("\n%s almocou na Area 2 e esta voltando pra aula", head2->nome);
            head2 = remover(head2);
            sizeArea2--;
          } else {
            printf("\nNao ha mais ninguem para comer aqui");
          }
        } else if(saida[0] == 'R') {
          // cliente saiu da fila do RU
          if(isEmpty(head1) == 0) {
            printf("\n%s almocou no RU e esta voltando pra aula", head1->nome);
            head1 = remover(head1);
            sizeRu--;
          } else {
            printf("\nNao ha mais ninguem para comer aqui");
          }
        }

      }

    }
  } while(1);

  free(ru);
  free(area2);
  free(nomeRu);
  free(nomeArea2);
  free(comidaRu);
  free(comidaArea2);
  free(entrada);
  free(comida);
  free(nome);
  free(saida);


  return 0;
}