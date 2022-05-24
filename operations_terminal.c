#include "functions.h"


int main(int argc, char *argv[]) {
  char endServer[100];
  int fd;
  char input[BUF_SIZE];
  char buffer[BUF_SIZE];
  int nread;
  if (argc != 2) {
    printf("cliente <host>\n");
    exit(-1);
  }

  strcpy(endServer, argv[1]);
  if ((hostPtr = gethostbyname(endServer)) == 0){
    erro("Nao consegui obter endereco");
  }
    

  bzero((void *)&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = ((struct in_addr *)(hostPtr->h_addr))->s_addr;
  addr.sin_port = htons(9000);

  if ((fd = socket(AF_INET,SOCK_STREAM,0)) == -1){
    erro("socket");
  }
    
  if (connect(fd,(struct sockaddr *)&addr,sizeof (addr)) < 0){
    erro("Connect");
  }
    




  nread = read(fd, buffer, BUF_SIZE-1);
  buffer[nread] = '\0';
  printf("%s", buffer);
  
  scanf("%s", input);
  write(fd, input, 1 + strlen(input));
  

  

  close(fd);
  exit(0);
}
