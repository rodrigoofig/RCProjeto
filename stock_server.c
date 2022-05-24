#include "functions.h"

int main(int argc, char *argv[])
{
    
    char line[10];
    //start shared memory
    int shmid = shmget(IPC_PRIVATE, sizeof(memory), IPC_CREAT|0700);
    mem = (memory*)shmat(shmid, NULL, 0);
    mem->tport = atoi(argv[1]);
    mem->uport = atoi(argv[2]);
    strcpy(mem->filename, argv[3]);
    //sems
    sem_init(&mem->write,1 ,1);
    
    
    // read the config.txt and create structs
    bolsatruct();
    userstruct();
    adminstruct();

    // save the number of users
    if (getLine(2, line));
    mem->nusers = atoi(line);

    //initialize refreshtime thread
    pthread_t refresh;
    pthread_create(&refresh, NULL, refreshtime, NULL);
    
    PORTO_CONFIG = fork();
    if(PORTO_CONFIG == 0){
      porto_config();
      exit(0);
    }

    PORTO_BOLSA = fork();
    if(PORTO_BOLSA == 0){
     porto_bolsa();
     exit(0); 
    }
    

    for(int i = 0; i <2;i++){
      wait(NULL);
    }

    pthread_join(refresh, NULL);
    return 0;
}
