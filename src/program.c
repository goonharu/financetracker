#include <stdio.h>
#include "../include/linkedlist.h"
#include "../include/ui.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void printCommand();
void slice(const char* str, char* result, size_t start, size_t end);
bool validateCommand(char* command, Node* sen);
bool processCommand(Node* sen);
void addIncome(Node* sen);
void addExpense(Node* sen);
void insertPos(Node* sen, char* type, char* description, double amount);
void displayList(Node* sen); 
bool quit(Node* sen);
void deleteList(Node* sen, char* command);
void readFile(Node* sen);
void saveData(Node* sen);

void start() {
  // initiate the sentinel node
  Node* sen = createNode(sen, "null", "null", 0, "null", sen);
  sen->size = 0;

  // print welcome message
  bool wantToContinue = printWelcome();

  // read file
  if (wantToContinue) {
    readFile(sen);
    printf("Current Balance: %.2f\n", sen->balance);
    if (sen->balance < 0) {
      printf("Budget Status: !!! Over budget !!!\n");
    }
    else {
      printf("Budget Status: *** Within budget ***\n");
    }
  }

  // print available commands
  printCommand();

  // process commands
  bool finished = false;
  while (! finished) {
    finished = processCommand(sen);
    printf("\n");
  }


}

bool processCommand(Node* sen) {
  char command[30];
  // get user input
  printf("Enter command: ");
  scanf(" %[^\n]s", command);
  return validateCommand(command, sen);
}

void readFile(Node* sen) {
  // read file
  FILE* file_ptr;
  int line_count = 0;
  bool first = false;
  bool second = false;
  bool third = false;

  char type[30] = "";
  char description[50] = "";
  char amountStr[20] = "";
  double amount;

  char ch;
  // open file
  file_ptr = fopen("./logs/transactions.txt", "r");

  if (file_ptr == NULL) {
    printf("File does not exist\n");
    return;
  }

  // skip the first 4 lines(headers)
  while (line_count < 4 && (ch = fgetc(file_ptr)) != EOF) {
    if (ch == '\n') {
      line_count++;
    }
  }

  // read the rest of the file
  while ((ch = fgetc(file_ptr)) != EOF) {
    if (ch == '\n') {
      // convert amount to double
      amount = atof(amountStr);
      // add to linked list
      addLast(sen, type, description, amount); 
      first = false;
      second = false;
      third = false;
      type[0] = '\0';
      description[0] = '\0';
      amountStr[0] = '\0';
    } else {
      if (!first) {
        // concatenate the character to the string
        strncat(type, &ch, 1);
        if (ch == '|') {
          first = true;
          // remove the last character
          type[strlen(type) - 1] = '\0';
        }
      } else if (first && !second) {
        // concatenate the character to the string
        strncat(description, &ch, 1);
        if (ch == '|') {
          second = true;
          // remove the last character
          description[strlen(description) - 1] = '\0';
        }
      } else if (first && second && !third) {
        // concatenate the character to the string
        strncat(amountStr, &ch, 1);
      }
    }
  }

  if (strlen(amountStr) > 0) {
    // convert amount to double
    amount = atof(amountStr);
    addLast(sen, type, description, amount);
  }
  fclose(file_ptr);

  Node* current = sen->next;
  // update status
  while (current != sen) {
    free(current->status);
    current->status = strdup("(saved)");
    current->status = "(saved)";
    current = current->next;
  }
  return;
}



void printCommand() {
  printf("\n");
  printf("\n");

   printf("    ---------------------------   \n");
  printf("    -   Available Commands:   -   \n");
  printf("    ---------------------------   \n");

  printf("\n");
  printf("\n");
  printf("    add income            Add the income amount and description of your income.\n");
  printf("    add expense           Add the expense amount and description of your expense.\n");
  printf("    delete [position]     delete the transaction at the entered <position>.\n");
  printf("    print                 print the log file of transactions and balance of the user. Depending on the balance, the user will see their budget status.\n");
  printf("    quit                  Save transactions and quit the program.\n");
  printf("\n");
}

void slice(const char* str, char* result, size_t start, size_t end) {
  strncpy(result, str + start, end - start);
}


bool validateCommand(char* command, Node* sen) {
  bool wantToQuit = false;
  bool isDelete = false;
  // check if the command is delete
  if (strlen(command) >= 6) {
    char sliceCommand[6] = "";
    slice(command, sliceCommand, 0, 6);
    if (strcmp(sliceCommand, "delete") == 0) {
      deleteList(sen, command);
      isDelete = true;
    }
  }
  // check if the command is add income, add expense, print, or quit
  if (strcmp(command, "add income") == 0) {
    addIncome(sen);
  }
  else if (strcmp(command, "add expense") == 0) {
    addExpense(sen);
  }
  else if (strcmp(command, "print") == 0) {
    displayList(sen);
  }
  else if (strcmp(command, "quit") == 0) {
    wantToQuit = quit(sen);
  }
  else if (!isDelete) {
    printf("I don't know what you mean...");
  }
  return wantToQuit;
}

void addIncome(Node* sen) {
  char description[50];
  double income;
  char choice[10];
  printf("Enter income description: ");
  scanf(" %[^\n]s", description);
  char type[30] = "INC";
  
  printf("Enter amount: ");
  scanf(" %lf", &income);
  getchar();

  // ask user if they want to insert at a specific position
  printf("Do you wanna insert at your desired position? (y/n): ");
  scanf(" %c", choice);
  if (*choice == 'y' || *choice == 'Y') {
    insertPos(sen, type, description, income);
  }
  else {
    addLast(sen, type, description, income);
    printf("Income added.");
  }
  printf("\n");
  // print current balance and budget status
  printf("Current Balance: %.2f\n", sen->balance);
  if (sen->balance < 0) {
    printf("Budget Status: !!! Over budget !!!\n");
  }
  else {
    printf("Budget Status: *** Within budget ***\n");
  }
}

void addExpense(Node* sen) {
  char description[50];
  double expense;
  char choice[10];
  printf("Enter expense description: ");
  scanf(" %[^\n]s", description);
  getchar();
  char type[30] = "EXP";

  printf("Enter amount: ");
  scanf("%lf", &expense);
  expense = -expense;
  getchar();

  // ask user if they want to insert at a specific position
  printf("Do you wanna insert at your desired position? (y/n): ");
  scanf(" %c", choice);
  if (*choice == 'y' || *choice == 'Y') {
    insertPos(sen, type, description, expense);
  }
  else {
    addLast(sen, type, description, expense);
    printf("Expense added.");
  }

  printf("\n");
  // print current balance and budget status
  printf("Current Balance: %.2f\n", sen->balance);
  if (sen->balance < 0) {
    printf("Budget Status: !!! Over budget !!!\n");
  }
  else {
    printf("Budget Status: *** Within budget ***\n");
  }
}

void displayList(Node* sen) {
   printList(sen);
}

void insertPos(Node* sen,char* type, char* description, double amount) {
  // ask user for position
  int position;
  printf("Insert at position: ");
  scanf("%d", &position);
  // insert at the desired position
  insert(sen, type, description, amount, position); 
  if (strcmp(type, "INC") == 0) {
    printf("Income added at position %d", position);
    return;
  }
  printf("Expense added at position %d", position);
}

void deleteList(Node* sen, char* command) {
  char commandName[30];
  int position, ret;

  // get the position
  ret = sscanf(command, " %s %d", commandName, &position);

  markDelete(sen, position);
  printf("Transaction at position %d marked for deletion.", position);

  // print current balance and budget status
  printf("\n");
  printf("Current Balance: %.2f\n", sen->balance);
  if (sen->balance < 0) {
    printf("Budget Status: !!! Over budget !!!\n");
  }
  else {
    printf("Budget Status: *** Within budget ***\n");
  }
} 

bool quit(Node* sen) {
  if (sen->size == 0) {
    printf("No transactions to save. Exiting program.\n");
    return true;
  }
  printf("Saving transactions to file...\n");
  update(sen);
  saveData(sen);
  printf("Done. Exiting program.\n");
  return true;
}

void saveData(Node* sen) {
  Node* current = sen->next;
  FILE* file_ptr;

  // open file
  file_ptr = fopen("./logs/transactions.txt", "w");

  if (file_ptr == NULL) {
    printf("File does not exist\n");
    return;
  }

  // write the header to file
  fprintf(file_ptr, "# Format: TYPE|DESCRIPTION|AMOUNT\n");
  fprintf(file_ptr, "# TYPE: INC (Income) or EXP (Expense)\n");
  fprintf(file_ptr, "# AMOUNT: Positive decimal number\n");
  fprintf(file_ptr, "\n");

  // write the transactions to the file
  while (current != sen) {
    fprintf(file_ptr, "%s|%s|%.2f\n", current->type, current->description, current->amount);
    current = current->next;
  }

  fclose(file_ptr);
}
















