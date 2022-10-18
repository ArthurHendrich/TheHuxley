#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct Node {
  char name[MAX];
  struct Node *prox;
  struct Node *before;
};

typedef struct Node node;


// print the list
void printList(node *head) {
  if (head == NULL) {
    printf("List is empty\n");
    return;
  }

  node *current = head;
  
  while(current != NULL) {
    if(head != current) {
      printf(" ");
    }
    printf("%s", current->name);

    current = current->prox;
  }
}

// add a new node to the end of the list
node* addReverse(node *head, char name[]) {
  node *newElement = (node *)malloc(sizeof(node));
  
  
  if(newElement == NULL) {
    printf("Error: Memory not allocated");
    exit(1);
  }

  strcpy(newElement->name, name);

  if((head) == NULL) {
    newElement->before = NULL;
    newElement->prox = NULL;
    head = newElement;
  } else {
    node *current = head;
    while(current->prox != NULL) {
      current = current->prox;
    }
    current->prox = newElement;
    newElement->before = current;
    newElement->prox = NULL;
  }

  return head;  
}


int find(node *head, char name[]) {
  node *current = head;
  int i = 0;
  if (head == NULL) {
    return -1;
  } else {
    while(current != NULL) {
      if(strcmp(current->name, name) == 0) {
        return i;
      }
      current = current->prox;
      i++;
    }
    return -1;
  }
}

// add all elements of aux in the position of the element "name"
void addPosition(node *head, node *aux, int position) {
  node *current = head;
  node *currentAux = aux;
  int i = 0;
  if (head == NULL) {
    return;
  } else {
    while(current != NULL) {
      if(i == position) {
        // Add all elements of aux before the position of the element "name" 
        while(currentAux != NULL) {
          node *newElement = (node *)malloc(sizeof(node));
          strcpy(newElement->name, currentAux->name);
          newElement->prox = current;
          newElement->before = current->before;
          current->before->prox = newElement;
          current->before = newElement;
          currentAux = currentAux->prox;
        }
      }
      current = current->prox;
      i++;
    }
  }
}

// add all elements of aux in the end of the list
void addEnd(node *head, node *aux) {
  node *current = head;
  node *currentAux = aux;
  if (head == NULL) {
    return;
  } else {
    while(current->prox != NULL) {
      current = current->prox;
    }
    // Add all elements of aux in the end of the list
    while(currentAux != NULL) {
      node *newElement = (node *)malloc(sizeof(node));
      strcpy(newElement->name, currentAux->name);
      newElement->prox = NULL;
      newElement->before = current;
      current->prox = newElement;
      current = current->prox;
      currentAux = currentAux->prox;
    }
  }
}

int main() {
  node *head = NULL;
  char name[MAX];

  // add elements to the list
  for (int i = 0; i < 4; i++) {
    scanf(" %s", name);
    head = addReverse(head, name);
  }

  node *aux = NULL;
  for (int i = 0; i < 3; i++) {
    scanf(" %s", name);
    aux = addReverse(aux, name);
  }
  
  // option string
  char option[20];
  scanf(" %s", option);  
  int position = find(head, option);


  if(position == -1) {
    addEnd(head, aux);
  } else {
    addPosition(head, aux, position);
  }

  printList(head);

  return 0;
}