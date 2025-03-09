#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Node{
  struct Node* next;
  struct Node* prev;
  int size;
  double balance;
  
  char* type;
  double amount;
  char* description;
  char* status;

};

typedef struct Node Node;

Node* createNode(Node* prev, const char* type, const char* description, double amount, char* status, Node* next);

void addFirst(Node* sen, const char* type, const char* description, double amount);

void addLast(Node* sen, const char* type, const char* description, double amount);

void insert(Node* sen, const char* type, const char* description, double amount, int pos);

void markDelete(Node* sen, int pos);

void update(Node* sen);

int size(Node* sen);

void printList(Node* sen);


#endif 
