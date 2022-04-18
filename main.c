#include "functions.h"

int main()
{

    char line[100];

    int refresh = 2;
    if (getLine(2, line))
        ;

    // save the number of users
    int nUsers = atoi(line);

    // pointer to change it inside functions
    int *ptrusers = &nUsers;

    // read the config.txt and create structs
    userstruct();
    bolsatruct();
    adminstruct();

    struct sockaddr_in si_minha, si_outra;

    int s, recv_len;
    socklen_t slen = sizeof(si_outra);
    char buf[BUFLEN];

    // Cria um socket para recepção de pacotes UDP
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
      erro("Erro na criação do socket");
    }

    // Preenchimento da socket address structure
    si_minha.sin_family = AF_INET;
    si_minha.sin_port = htons(PORT);
    si_minha.sin_addr.s_addr = htonl(INADDR_ANY);

    // Associa o socket à informação de endereço
    if (bind(s, (struct sockaddr *)&si_minha, sizeof(si_minha)) == -1)
    {
      erro("Erro no bind");
    }


    while (1)
    {
        // Espera recepção de mensagem (a chamada é bloqueante)
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_outra, (socklen_t *)&slen)) == -1)
        {
          erro("Erro no recvfrom");
        }
        // Para ignorar o restante conteúdo (anterior do buffer)
        buf[recv_len] = '\0';

        char *tok = strtok(buf, " \n");

        char param1[50];
        char param2[50];
        char param3[50];
        char param4[50];
        if (strcmp(buf, "X") == 0){
          continue;
        }
        printf("[%s:%d] %s\n", inet_ntoa(si_outra.sin_addr), ntohs(si_outra.sin_port),buf);

        if (strcmp(tok, "ADD_USER") == 0)
        {
            tok = strtok(NULL, " \n");
            strcpy(param1, tok);
            tok = strtok(NULL, " \n");
            strcpy(param2, tok);
            tok = strtok(NULL, " \n");
            strcpy(param3, tok);
            tok = strtok(NULL, " \n");
            strcpy(param4, tok);
            addUser(param1, param2, param3, atoi(param4), ptrusers);
            writefile(*ptrusers);
        }
        else if (strcmp(tok, "REFRESH") == 0)
        {
            tok = strtok(NULL, " \n");
            refresh = atoi(tok);
            printf("REFRESH TIME changed to: %d seg\n", refresh);
        }
        else if (strcmp(tok, "LIST") == 0)
        {
            listusers(*ptrusers);
        }
        else if (strcmp(tok, "DEL") == 0)
        {
            tok = strtok(NULL, " \n");
            strcpy(param1, tok);
            deleteuser(param1, ptrusers);
            writefile(*ptrusers);
        }

        else if (strcmp(tok, "QUIT") == 0)
        {
            break;
        }
        else if (strcmp(tok, "QUIT_SERVER") == 0)
        {
            return 1;
        }
        else
        {
            printf("COMMAND DOES NOT EXIST\n");
        }
    }

    // Fecha socket e termina programa
    close(s);
    return 0;
}
