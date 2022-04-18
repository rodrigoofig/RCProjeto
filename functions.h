#ifndef FUNC
#define FUNC

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
// server librarys
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 512	// Tamanho do buffer
#define PORT 9876	// Porto para recepção das mensagens

#define FILENAME "config.txt"


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
bool getLine(int l, char *line);
void listusers(int tam);
void userstruct();
void bolsatruct();
void adminstruct();
int refreshtime(int time);
void deleteuser(char* name, int *tam);
void writefile(int tam);
void erro(char *s);
#endif //FUNC
