#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  char *name;
  struct Node *next;
};
typedef struct Node node;


void sortList(node *head) {
  node *aux = head;
  node *index = NULL;
  char *temp;

  if (head == NULL) {
    return;
  } else {
    while (aux != NULL) {
      index = aux->next;

      while (index != NULL) {
        if (strcmp(aux->name, index->name) > 0) {
          temp = aux->name;
          aux->name = index->name;
          index->name = temp;
        }

        index = index->next;
      }
      aux = aux->next;
    }
  }
}


void printList(node *head) {
  node *aux = head;
  node *aux2 = head;
  int count = 0;
  int count2 = 0;
  int limite = 0;

  while (aux != NULL) {
    count = 0;
    aux2 = head;
    while (aux2 != NULL) {
      if (strcmp(aux->name, aux2->name) == 0) {
        count++;
      }
      aux2 = aux2->next;
    }
    limite = 0;
    aux2 = head;

    while (aux2 != aux) {
      if (strcmp(aux->name, aux2->name) == 0) {
        limite = 1;
      }
      aux2 = aux2->next;
    }
    if (limite == 0) {
      printf("%s %d\n", aux->name, count);
    }
    aux = aux->next;
  }

}


node *addList(node *head, char *name) {
  node *newNode = (node *)malloc(sizeof(node));
  newNode->name = name;
  newNode->next = NULL;

  if (head == NULL) {
    head = newNode;
  } else {
    node *aux = head;
    while (aux->next != NULL) {
      aux = aux->next;
    }
    aux->next = newNode;
  }

  return head;
}


void remover_especiais(char *str) {
  int i = 0;
  int aux = 0;

  while (str[i] != '\0') {
    if (str[i] != '.' && str[i] != '"' && str[i] != '(' && str[i] != '*' && str[i] != '$' && str[i] != '#' && str[i] != ':') {
      str[aux] = str[i];
      aux++;
    } else {
      str[aux] = ' ';
      aux++;
    }
    i++;
  }
}


void toLower(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] = str[i] + 32;
    }
    i++;
  }
}


int main() {
  char matrix[200][200];
  char *str;

  int i = 0;

  while (scanf(" %m[^\n]", &str) != EOF) {
    remover_especiais(str);
    strcpy(matrix[i], str);
    i++;
  }

  // split
  char *token;
  char *word[200];
  int size = 0;

  for (int j = 0; j < i-1; j++) {
    token = strtok(matrix[j], " ");
    while (token != NULL) {
      word[size] = token;
      size++;
      token = strtok(NULL, " ");
    }
  }

  for (int j = 0; j < size; j++) {
    toLower(word[j]);
  }

  node *head = NULL;
  for (int j = 0; j < size; j++) {
    head = addList(head, word[j]);
  }
  

  sortList(head);
  printList(head);

  // free memory
  node *aux = head;
  while (aux != NULL) {
    node *aux2 = aux;
    aux = aux->next;
    free(aux2);
  }

  


  return 0;
}