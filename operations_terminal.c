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
    
  
  do{
    nread = read(fd, buffer, BUF_SIZE-1);
    buffer[nread] = '\0';
    printf("%s", buffer);

    gets(input);
    write(fd, input, 1 + strlen(input));

    nread = read(fd, buffer, BUF_SIZE-1);
    buffer[nread] = '\0';
    printf("%s", buffer);
    
  }while(strcmp(buffer,"LOGGED IN\n" )!=0);
  do{
    
    nread = read(fd, buffer, BUF_SIZE-1);
    buffer[nread] = '\0';
    printf("%s", buffer);
  }while(strcmp(buffer, "1 - ligar feed\n2 - desligar feed\n3 - conteudo carteira\n4 - subscrever\n5 - comprar\n6 - vender\n7 - sair\n") != 0);
   
  while(1){
    gets(input);
    write(fd, input, 1 + strlen(input));
    if(strcmp(input, "3") == 0){
      
      nread = read(fd, buffer, BUF_SIZE-1);
      buffer[nread] = '\0';
      printf("%s", buffer);
      write(fd, buffer, 1 + strlen(buffer));
    }

    if(strcmp(input, "4") == 0){
      
      nread = read(fd, buffer, BUF_SIZE-1);
      buffer[nread] = '\0';
      printf("%s", buffer);

      gets(input);
      write(fd, input, 1 + strlen(input));
    }
    if(strcmp(input, "5") == 0){
      
      nread = read(fd, buffer, BUF_SIZE-1);
      buffer[nread] = '\0';
      printf("%s", buffer);
      if(strcmp(buffer, "NAO ESTA INSCRITO EM NENHUMA ACAO\n") != 0){
        gets(input);
        write(fd, input, 1 + strlen(input));
        nread = read(fd, buffer, BUF_SIZE-1);
        buffer[nread] = '\0';
        printf("%s", buffer);
        
      }
      write(fd, buffer, 1 + strlen(buffer));
        
    }
    if(strcmp(input, "6") == 0){
    
      nread = read(fd, buffer, BUF_SIZE-1);
      buffer[nread] = '\0';
      printf("%s", buffer);
      if(strcmp(buffer,"NAO ESTA INSCRITO EM NENHUMA ACAO OU NAO TEM ACOES PARA VENDER\n") != 0){
        gets(input);
        write(fd, input, 1 + strlen(input));
        nread = read(fd, buffer, BUF_SIZE-1);
        buffer[nread] = '\0';
        printf("%s", buffer);
        
      }
      write(fd, buffer, 1 + strlen(buffer));
      
      
    }
    nread = read(fd, buffer, BUF_SIZE-1);
    buffer[nread] = '\0';
    printf("%s", buffer);
    fflush(stdout);
  }
  

  close(fd);
  exit(0);
}
