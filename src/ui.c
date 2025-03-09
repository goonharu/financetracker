#include <stdio.h>
#include "../include/ui.h"
#include "../include/program.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>



bool printChoice(char* choice);
bool fileExists(const char* filename);
void createDirectory(const char* path);
void createFile();
void printBanner();


bool printWelcome() {
  char choice[10];
  printf("\n");
  printf("\n");


  printBanner();

  printf("\n");
  printf("\n");
  printf("This tracker is built specifically to track income and expenses.\n");
  printf("\nWould you like to resume your previous session? (y/n): ");
  scanf("%c", choice);

  return printChoice(choice);

}

void printBanner() {
  printf("     ________            __  ______  _                 __     \n");
  printf("    /_  __/ /_  ___     / / / / / /_(_)___ ___  ____ _/ /____ \n");
  printf("     / / / __ \\/ _ \\   / / / / / __/ / __ `__ \\/ __ `/ __/ _ \\\n");
  printf("    / / / / / /  __/  / /_/ / / /_/ / / / / / / /_/ / /_/  __/\n");
  printf("   /_/ /_/ /_/\\___/   \\____/_/\\__/_/_/ /_/ /_/\\__,_/\\__/\\___/ \n");
  printf("                                                           \n");
  printf("            _______                        _       __\n");
  printf("          / ____(_)___  ____ _____  _____(_)___ _/ /\n");
  printf("         / /_  / / __ \\/ __ `/ __ \\/ ___/ / __ `/ / \n");
  printf("        /__/ / / / / / /_/ / / / / /__/ / /_/ / /  \n");
  printf("       /_/  /_/_/ /_/\\__,_/_/ /_/\\___/_/\\__,_/_/   \n");
  printf("                                              \n");
  printf("        ______                __            \n");
  printf("       /_  __/________ ______/ /_____  _____\n");
  printf("        / / / ___/ __ `/ ___/ //_/ _ \\/ ___/\n");
  printf("       / / / /  / /_/ / /__/ ,< /  __/ /    \n");
  printf("      /_/ /_/   \\__,_/\\___/_/|_|\\___/_/     \n");
}


bool printChoice(char* choice) {
  // Check if the user wants to resume from the previous session
  if ((*choice == 'y' || *choice == 'Y') && fileExists("./logs/transactions.txt")) {
    printf("\n");
    printf("Resuming from last session...\n");
    printf("Previous transactions loaded.\n");
    printf("\n");
    return true;
  }
  else {
    printf("\n");
    createDirectory("../logs");
    return false;
  }
}

bool fileExists(const char* filename) {
  // Check if the file exists
  struct stat buffer;
  return stat(filename, &buffer) == 0;
}

void createDirectory(const char* path) {
  // Create a new directory
  if (mkdir(path, 0755) == 0) {
    printf("Starting a new session...\n");
    printf("Current Balance: $0\n");
    printf("Budget Status: Within Budget\n");
    createFile();
  }
  else {
    return;
  }
}

void createFile() {
  // Create a new file
  FILE* file_ptr;

  file_ptr = fopen("./logs/transactions.txt", "w");

  if (file_ptr == NULL) {
    printf("File does not exist\n");
    return;
  }

  fclose(file_ptr);
  return;
 
 
}