#ifndef FUNC
#define FUNC

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
// server librarys
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
//SO librarys
#include <signal.h>
#include <pthread.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <ctype.h>
#include <sys/stat.h>



//udp
#define BUFLEN 512	// Tamanho do buffer
#define PORT 9876	// Porto para recepção das mensagens
//tcp
#define SERVER_PORT 9000 // Porto para recepção das mensagens
#define BUF_SIZE	1024 // Tamanho do buffer
//multicast
#define EXAMPLE_PORT 6000
#define GROUP1 "239.0.0.1"
#define GROUP2 "239.0.0.2"
#define GROUP3 "239.0.0.3"
#define GROUP4 "239.0.0.4"
#define GROUP5 "239.0.0.5"
#define GROUP6 "239.0.0.6"
//--------------------------------------------------------
#define FILENAME "config.txt"

//global variables

//structures
typedef struct{
    char nome[50];
    int quantidade;
    bool inscrito;
}acao;

struct user{
    char name[50];
    char password[50];
    char bolsa1[50];
    char bolsa2[50];
    float saldo;
    acao acoes[6];
};

struct admin{
    char name[50];
    char password[50];
};

struct bolsa{
    char mercado[50];
    char acao[50];
    float preco;
    int quantidade;
};
typedef struct {
    int logofacoisto,refresh,nusers,uport, tport, counter;
    struct bolsa bolsas[6];
    struct user users[10];
    struct admin adm;
    char filename[30];
    sem_t write;
    sem_t process, start;
}memory;

memory *mem;



struct sockaddr_in si_minha;
struct sockaddr_in si_outra;
struct sockaddr_in addr;
struct sockaddr_in client_addr;
struct hostent *hostPtr;
struct ip_mreq mreq;
pid_t PORTO_CONFIG, PORTO_BOLSA;


//functions
void addUser(char *name, char*password, char*bolsas, float saldo);
int searchUser(char *name);
bool getLine(int l, char *line);
void listusers();
void userstruct();
void bolsatruct();
void adminstruct();
void * refreshtime();
int deleteuser(char* name);
void writefile();
void process_client(int fd);
void porto_bolsa();
void porto_config();
void erro(char *s);
void * showfeed();
bool inscrito(int idx);
bool carteira(int idx);
void * reader(void * arg);
#endif //FUNC
