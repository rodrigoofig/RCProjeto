#include "functions.h"


int main(int argc, char *argv[]) {
  char endServer[100];
  int fd;
  char input[BUF_SIZE];
  char buffer[BUF_SIZE];
  int nread;
  struct sockaddr_in addrm[6];

  if (argc != 3) {
    printf("cliente <host> <port>\n");
    exit(-1);
  }

  strcpy(endServer, argv[1]);
  if ((hostPtr = gethostbyname(endServer)) == 0){
    erro("Nao consegui obter endereco");
  }
  

  bzero((void *)&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = ((struct in_addr *)(hostPtr->h_addr))->s_addr;
  addr.sin_port = htons((short)atoi(argv[2]));

  if ((fd = socket(AF_INET,SOCK_STREAM,0)) == -1){
    erro("socket");
  }
    
  if (connect(fd,(struct sockaddr *)&addr,sizeof (addr)) < 0){
    erro("Connect");
  }
  //------------------------------------------------------
  int  sock;
  struct ip_mreq mreq[6];
  
  /* set up socket */
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("socket");
    exit(1);
  }
  int multicastTTL = 255; // by default TTL=1; the packet is not transmitted to other networks
  if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &multicastTTL, sizeof(multicastTTL)) < 0){
    perror("socket opt");
    exit(1);
  }
  int reuseaddr = 1;
  if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *)&reuseaddr, sizeof(reuseaddr))<0){
    perror("feed error: socket opt 2");
    exit(1);
  }
  bzero((char *)&addrm, sizeof(addrm));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(EXAMPLE_PORT);
  
  if (bind(sock, (struct sockaddr *) &addrm, sizeof(addrm)) < 0) {
    perror("bind");
    exit(1);
  } 
  pthread_t readt;
  
  
  do{
    nread = read(fd, buffer, BUF_SIZE-1);
    buffer[nread] = '\0';
    printf("%s", buffer);

    fgets(input, BUF_SIZE, stdin);
    write(fd, input, 1 + strlen(input));

    nread = read(fd, buffer, BUF_SIZE-1);
    buffer[nread] = '\0';
    printf("%s", buffer);
    
  }while(strcmp(buffer,"LOGGED IN\n" )!=0);
  
    
  nread = read(fd, buffer, BUF_SIZE-1);
  buffer[nread] = '\0';
  printf("%s", buffer);
  write(fd, buffer, 1 + strlen(buffer));
  nread = read(fd, buffer, BUF_SIZE-1);
  buffer[nread] = '\0';
  printf("%s", buffer);


  while(1){
    fgets(input, BUF_SIZE, stdin);
    write(fd, input, 1 + strlen(input));
    if(strcmp(input, "1\n") == 0){
      pthread_create(&readt, NULL, reader, &sock);
      
    }
    if(strcmp(input, "2\n") == 0){
      pthread_cancel(readt);
    }
    if(strcmp(input, "3\n") == 0){
      
      nread = read(fd, buffer, BUF_SIZE-1);
      buffer[nread] = '\0';
      printf("%s", buffer);
      write(fd, buffer, 1 + strlen(buffer));
    }

    if(strcmp(input, "4\n") == 0){
      
      nread = read(fd, buffer, BUF_SIZE-1);
      buffer[nread] = '\0';
      printf("%s", buffer);

      fgets(input, BUF_SIZE, stdin);
      write(fd, input, 1 + strlen(input));
      
      
      if(strcmp(input, "1\n") == 0){
        mreq[0].imr_multiaddr.s_addr = inet_addr(GROUP1);
        mreq[0].imr_interface.s_addr = htonl(INADDR_ANY);
        addrm[0].sin_addr.s_addr = inet_addr(GROUP1);
        if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq[0], sizeof(mreq[0])) < 0) {
          perror("setsockopt mreq");
          exit(1);
        }
      }
      if(strcmp(input, "2\n") == 0){
        mreq[1].imr_multiaddr.s_addr = inet_addr(GROUP2);
        mreq[1].imr_interface.s_addr = htonl(INADDR_ANY);
        addrm[1].sin_addr.s_addr = inet_addr(GROUP2);
        if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq[1], sizeof(mreq[1])) < 0) {
          perror("setsockopt mreq");
          exit(1);
        }
      }
      if(strcmp(input, "3\n") == 0){
        mreq[2].imr_multiaddr.s_addr = inet_addr(GROUP3);
        mreq[2].imr_interface.s_addr = htonl(INADDR_ANY);
        addrm[2].sin_addr.s_addr = inet_addr(GROUP3);
        if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq[2], sizeof(mreq[2])) < 0) {
          perror("setsockopt mreq");
          exit(1);
        }
      }
      if(strcmp(input, "4\n") == 0){
        mreq[3].imr_multiaddr.s_addr = inet_addr(GROUP4);
        mreq[3].imr_interface.s_addr = htonl(INADDR_ANY);
        addrm[3].sin_addr.s_addr = inet_addr(GROUP4);
        if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq[3], sizeof(mreq[3])) < 0) {
          perror("setsockopt mreq");
          exit(1);
        }
      }
      if(strcmp(input, "5\n") == 0){
        mreq[4].imr_multiaddr.s_addr = inet_addr(GROUP5);
        mreq[4].imr_interface.s_addr = htonl(INADDR_ANY);
        addrm[4].sin_addr.s_addr = inet_addr(GROUP5);
        if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq[4], sizeof(mreq[4])) < 0) {
          perror("setsockopt mreq");
          exit(1);
        }
      }
      if(strcmp(input, "6\n") == 0){
        mreq[5].imr_multiaddr.s_addr = inet_addr(GROUP6);
        mreq[5].imr_interface.s_addr = htonl(INADDR_ANY);
        addrm[5].sin_addr.s_addr = inet_addr(GROUP6);
        if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq[5], sizeof(mreq[5])) < 0) {
          perror("setsockopt mreq");
          exit(1);
        }
      }
      

    }
    if(strcmp(input, "5\n") == 0){
      
      nread = read(fd, buffer, BUF_SIZE-1);
      buffer[nread] = '\0';
      printf("%s", buffer);
      if(strcmp(buffer, "NAO ESTA INSCRITO EM NENHUMA ACAO\n") != 0){
        fgets(input, BUF_SIZE, stdin);
        write(fd, input, 1 + strlen(input));
        nread = read(fd, buffer, BUF_SIZE-1);
        buffer[nread] = '\0';
        printf("%s", buffer);
        
      }
      write(fd, buffer, 1 + strlen(buffer));
        
    }
    if(strcmp(input, "6\n") == 0){
    
      nread = read(fd, buffer, BUF_SIZE-1);
      buffer[nread] = '\0';
      printf("%s", buffer);
      if(strcmp(buffer,"NAO ESTA INSCRITO EM NENHUMA ACAO OU NAO TEM ACOES PARA VENDER\n") != 0){
        fgets(input, BUF_SIZE, stdin);
        write(fd, input, 1 + strlen(input));
        nread = read(fd, buffer, BUF_SIZE-1);
        buffer[nread] = '\0';
        printf("%s", buffer);
        
      }
      write(fd, buffer, 1 + strlen(buffer));
      
      
    }
    if(strcmp(input, "7\n") == 0){
      close(fd);
    }
    nread = read(fd, buffer, BUF_SIZE-1);
    buffer[nread] = '\0';
    printf("%s", buffer);
    fflush(stdout);
  }
  
  pthread_join(readt, NULL);
  close(fd);
  exit(0);
}
