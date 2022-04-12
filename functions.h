
#ifndef FUNC
#define FUNC

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>


#define FILENAME "config.txt"
#define TEST "test.txt"


struct user{
    char name[50];
    char password[50];
    char bolsa1[50];
    char bolsa2[50];
    int saldo;
    
};

struct admin{
    char name[50];
    char password[50];
};

struct bolsa{
    char mercado[50];
    char acao[50];
    float preco;
    
};
struct bolsa bolsas[6];
struct user users[10];
struct admin adm;


void addUser(char *name, char*password, char*bolsas, int saldo, int *tam);
int searchUser(char *name, int tam);
bool getline(int l, char *line);
void listusers(int tam);
void userstruct();
void bolsatruct();
void adminstruct();
int refreshtime(int time);
void deleteuser(char* name, int *tam);
void writefile(int tam);

#endif //FUNC