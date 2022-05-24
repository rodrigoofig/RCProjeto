#include "functions.h"

int main(int argc, char *argv[]) {
  char endServer[100];
  char writec[100];
  int fd;

  

  
  if (argc != 3) {
    printf("cliente <host> <port>\n");
    exit(-1);
  }

  strcpy(endServer, argv[1]);
  if ((hostPtr = gethostbyname(endServer)) == 0)
    erro("Não consegui obter endereço");

  bzero((void *) &addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = ((struct in_addr *)(hostPtr->h_addr))->s_addr;
  addr.sin_port = htons((short) atoi(argv[2]));

  if ((fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    erro("socket");
  if (connect(fd,(struct sockaddr *)&addr,sizeof (addr)) < 0)
    erro("Connect");
  



  int nread = 0;
  char buffer[BUF_SIZE];
  char input[BUF_SIZE];

  while(1){
    nread = read(fd, buffer, BUF_SIZE-1);
    while(nread>0){
      nread = read(fd, buffer, BUF_SIZE-1);
    }
    printf("%s", buffer);
    scanf("%s", input);
    memset(buffer, 0 , strlen(buffer));
    memset(input, 0 , strlen(input));
  }
  
  close(fd);
  exit(0);
}
