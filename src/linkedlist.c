#include <stdio.h>
#include <string.h>
#include "../include/linkedlist.h"
#include <stdlib.h>

Node* createNode(Node* prev, const char* type, const char* description, double amount, char* status, Node* next) {
  // Allocate memory for the new node
  Node *new_node = (Node*)malloc(sizeof(Node));
  // Check if memory allocation was successful
  if (new_node == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  // Initialize the new node
  new_node->type = strdup(type);
  new_node->description = strdup(description);
  new_node->amount = amount;
  new_node->status = strdup(status);

  new_node->prev = prev;
  new_node->next = next;
  new_node->size = 0;
  new_node->balance = 0;
  return new_node;
}

void addFirst(Node* sen, const char* type, const char* description, double amount) {
  char status[30] = "(new)";
  // Check if the list is empty
  if (sen->size == 0) {
    // Create a new node
    Node* new_node = createNode(sen, type, description, amount, status, sen);
    sen->next = new_node;
    sen->prev = new_node;
  }
  else {
    // Get the first item
    Node* firstItem = sen->next;
    // Create a new node
    Node* new_node = createNode(sen, type, description, amount, status, firstItem);
    // Rejoin the connections
    firstItem->prev = new_node;
    sen->next = new_node;
  }
  // Update the balance and size
  sen->balance += amount;
  sen->size += 1;
}

void addLast(Node* sen, const char* type, const char* description, double amount) {
  char status[30] = "(new)";
  // Check if the list is empty
  if (sen->size == 0) {
    // Create a new node
    addFirst(sen, type, description, amount);
  }
  else {
    // Get the last item
    Node* lastItem = sen->prev;
    // Create a new node
    Node* new_node = createNode(lastItem, type, description, amount, status, sen);
    // Rejoin the connections
    lastItem->next = new_node;
    sen->prev = new_node;
    sen->balance += amount;
    sen->size += 1;
  }

}

void insert(Node* sen, const char* type, const char* description, double amount, int pos) {
  int position = pos - 1;
  // Check if the list is empty
  if (sen->size == 0 || position == 0) {
    // Add the first item
    addFirst(sen, type, description, amount);
  }
  // Check if the position is the last
  else if (position == sen->size) {
    // Add the last item
    addLast(sen, type, description, amount);
  }
  // Check if the position is out of range
  else if (position < 0 || position > sen->size) {
    // Print an error message
    printf("Invalid position\n");
    return;
  }
  // Insert at the desired position
  else {
    // Get the first item
    Node* current = sen;
    // Traverse the list to the desired position
    for (int i = 0; i < position; i++) {
      current = current->next;
    }
    // Create a new node
    char status[30] = "+++ i";
    Node* nextNode = current->next;
    Node* new_node = createNode(current, type, description, amount, status, nextNode);
    current->next = new_node;
    nextNode->prev = new_node;
    sen->balance += amount;
    sen->size += 1;
  }
}

void markDelete(Node* sen, int pos) {
  // Check if the list is empty
  if (sen->size == 0) {
    return;
  }

  Node* current = sen->next;

  // Traverse the list to the desired position
  for (int i = 0; current != sen && i < pos - 1; i++) {
    current = current->next;
  }

  // Out of range
  if (current == sen) {
    return;
  }

  // Mark the transaction for deletion
  free(current->status);
  current->status = strdup("--- d");
  current->status = "--- d";
  sen->balance -= current->amount;
}

void update(Node* sen) {
  if (sen->size == 0) {
    return;
  }

  Node* current = sen->next;

  // Traverse the list
  while (current != sen) {
    if (strcmp(current->status, "--- d") == 0) {
      // Get the next item
      Node* tmp = current;
      current = current->next;
      // Rejoining all the connections
      if (tmp->prev != NULL) {
        tmp->prev->next = tmp->next;
      }
      if (tmp->next != NULL) {
        tmp->next->prev = tmp->prev;
      }
      // Update the size
      free(tmp);
      sen->size -= 1;
      continue;
    }
    current = current->next;
  }
}



int size(Node* sen) {
  return sen->size;
}

void printList(Node* sen) {
  printf("  *******************  \n");
  printf("  **  Transactions **  \n");
  printf("  *******************  \n");
  int labelNum = 1;

  // Check if the list is empty
  if (sen->size != 0) {
    Node* current = sen->next;
    do {
      // Print the transaction
      printf("%d. %s\t%.2f\t%s\n", labelNum, current->description, current->amount, current->status);
      current = current->next;
      labelNum++;
      // Traverse the list
    } while (current != sen);
    printf("\n");
  }
  else {
    printf("Empty List\n");
  }

}

