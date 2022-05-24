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
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//udp
#define BUFLEN 512	// Tamanho do buffer
#define PORT 9876	// Porto para recepção das mensagens
//tcp
#define SERVER_PORT 9000 // Porto para recepção das mensagens
#define BUF_SIZE	1024 // Tamanho do buffer
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
    int logofacoisto,refresh,nusers,uport, tport;
    struct bolsa bolsas[6];
    struct user users[10];
    struct admin adm;
    char filename[30];
    sem_t  write;
}memory;

typedef struct{
    int fd;
    int index;
}inf;


memory *mem;



struct sockaddr_in si_minha, si_outra;
struct sockaddr_in addr;
struct hostent *hostPtr;
struct sockaddr_in addr, client_addr;
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
void * showfeed(void * arg);
bool inscrito(int idx);
bool carteira(int idx);
#endif //FUNC
