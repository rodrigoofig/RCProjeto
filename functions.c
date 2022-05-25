#include "functions.h"
pthread_mutex_t feedmutex = PTHREAD_MUTEX_INITIALIZER;
bool getLine(int l, char line[])
{

    int linecounter = 0;
    char ch;
    int i = 0;
    FILE *ptr;
    ptr = fopen(mem->filename, "r");
    // reading char by char
    do
    {
        ch = fgetc(ptr);

        if (ch != '\n')
        {
            // fill the string
            line[i] = ch;
            i++;
        }
        // if the line has changed
        else
        {
            // simply counts the line we currently are
            linecounter++;
            line[i] = '\0';
            // return true if we get the line we wanted
            if (linecounter == l)
            {
                return true;
            }
            // reset vars
            i = 0;
            line[0] = '\0';
        }

    } while (ch != EOF);

    fclose(ptr);
    return false;
}

void userstruct()
{
    char line[100];
    char temp[50];

    struct user aux;
    strcpy(aux.bolsa1, "vazio");
    strcpy(aux.bolsa2, "vazio");
    // buscar a segunda linha
    getLine(2, line);
    int numberofusers = atoi(line);
    // loops for all users in the file
    for (int i = 3; i < 3 + numberofusers; i++)
    {

        int w = 0;
        line[0] = '\0';
        getLine(i, line);
        int len = strlen(line);
        // saving the name in a temp var
        int param = 0;
        for (int i = 0; i < len + 1; i++)
        {

            if (line[i] != ';' && line[i] != '\0')
            {
                temp[w] = line[i];
                w++;
                // printf("%c", temp[i]);
            }
            else if (line[i] == ';' || line[i] == '\0')
            {
                temp[w] = '\0';
                if (param == 0)
                {
                    strcpy(aux.name, temp);
                }
                if (param == 1)
                {
                    strcpy(aux.password, temp);
                }
                if (param == 2)
                {
                    aux.saldo = atof(temp);
                }
                if (param == 3)
                {
                    strcpy(aux.bolsa1, temp);
                }
                if (param == 4)
                {
                    strcpy(aux.bolsa2, temp);
                }

                temp[0] = '\0';
                w = 0;
                param++;
            }
        }
        for (int i = 0; i < 6; i++)
        {
            aux.acoes[i].inscrito = false;
            strcpy(aux.acoes[i].nome, mem->bolsas[i].acao);
            aux.acoes[i].quantidade = 0;
        }
        
        mem->users[i - 3] = aux;
    }
}

void bolsatruct()
{
    char line[100];
    char temp[50];

    struct bolsa aux;

    // buscar a segunda linha
    getLine(2, line);
    int numberofusers = atoi(line);
    // loops for all users in the file
    for (int i = 3 + numberofusers; i < 3 + numberofusers + 6; i++)
    {

        int w = 0;
        line[0] = '\0';
        getLine(i, line);
        int len = strlen(line);
        // saving the name in a temp var
        int param = 0;
        for (int i = 0; i < len + 1; i++)
        {

            if (line[i] != ';' && line[i] != '\0')
            {
                temp[w] = line[i];
                w++;
                // printf("%c", temp[i]);
            }
            else if (line[i] == ';' || line[i] == '\0')
            {
                temp[w] = '\0';
                if (param == 0)
                {
                    strcpy(aux.mercado, temp);
                }
                if (param == 1)
                {
                    strcpy(aux.acao, temp);
                }
                if (param == 2)
                {
                    aux.preco = atof(temp);
                }

                temp[0] = '\0';
                w = 0;
                param++;
            }
        }
        aux.quantidade = (rand()%10) * 10;
        mem->bolsas[i - 3 - numberofusers] = aux;
    }
}

void adminstruct()
{

    char line[100];
    char temp[50];
    int w = 0;
    int param = 0;

    // buscar a primeira linha
    getLine(1, line);
    for (int i = 0; i < strlen(line) + 1; i++)
    {
        if (line[i] != '/' && line[i] != '\0')
        {
            temp[w] = line[i];
            w++;
        }
        else if (line[i] == '/' || line[i] == '\0')
        {

            temp[w] = '\0';
            if (param == 0)
            {
                strcpy(mem->adm.name, temp);
            }
            if (param == 1)
            {
                strcpy(mem->adm.password, temp);
            }
            temp[0] = '\0';
            w = 0;
            param++;
        }
    }
}


//if exists return the position in the array
//else rerturn -1
int searchUser(char *name)
{
    for (int i = 0; i < mem->nusers; i++)
    {
        if(strcmp(name, mem->users[i].name) == 0){
            return i;
        }
    }
    return -1;
}

void addUser(char *name, char*password, char*bolsas, float saldo){
    //get the position
    int pos = searchUser(name);
    struct user aux;
    if(pos >= 0){
        //check if the bolsas are empty if the name exists
        if(strcmp(mem->users[pos].bolsa1, "vazio") == 0){
            strcpy(mem->users[pos].bolsa1, bolsas);
            printf("bolsa 1 alterada\n");
        }
        else if(strcmp(mem->users[pos].bolsa2, "vazio") == 0){
            strcpy(mem->users[pos].bolsa2, bolsas);
            printf("bolsa 2 alterada\n");
        }
        else{
            printf("O utilizador nao pode ter mais bolsas\n");
            return ;
        }
    }
    //if the name doesnt exist, create and add to the array
    else{
        strcpy(aux.name, name);
        strcpy(aux.password, password);
        aux.saldo = saldo;
        strcpy(aux.bolsa1, bolsas);
        strcpy(aux.bolsa2, "vazio");
        mem->users[mem->nusers] = aux;
        mem->nusers++;
        printf("Utilizador adicionado com sucesso\n\n");
    }
}


int deleteuser(char* name){
    //get the position of the user to delete
    int pos = searchUser(name);
    if (pos >= 0 && pos + 1 < 10){

        for (int i = pos; i < mem->nusers; i++)
        {
            //shift to the left and ignore the last one
            mem->users[i] = mem->users[i +1];

        }

        mem->nusers--;
        return 1;
    }

    return pos;

}

void writefile(){
    sem_wait(&mem->write);
    FILE * ptr;
    ptr = fopen(mem->filename, "w");
    //add admin
    fprintf(ptr, "%s/%s\n", mem->adm.name, mem->adm.password);
    //add numero de users atualizado
    fprintf(ptr, "%d\n", mem->nusers);
    for (int i = 0; i < mem->nusers ; i++)
    {
        //se nenhuma bolsa esta assianda
        if(strcmp(mem->users[i].bolsa1, "vazio") == 0 && strcmp(mem->users[i].bolsa1, "vazio")==0){
           fprintf(ptr, "%s;%s;%f\n", mem->users[i].name, mem->users[i].password, mem->users[i].saldo);
        }
        //se apenas assinou uma bolsa
        else if(strcmp(mem->users[i].bolsa1, "vazio") != 0 && strcmp(mem->users[i].bolsa2, "vazio")==0){
           fprintf(ptr, "%s;%s;%f;%s\n", mem->users[i].name, mem->users[i].password, mem->users[i].saldo, mem->users[i].bolsa1);
        }
        //tem as duas bolsas assinadas
        else{
            fprintf(ptr, "%s;%s;%f;%s;%s\n", mem->users[i].name, mem->users[i].password, mem->users[i].saldo, mem->users[i].bolsa1,mem->users[i].bolsa2);
        }
    }
    //add markets
    for (int i = 0; i < 6; i++)
    {
        fprintf(ptr, "%s;%s;%1f\n", mem->bolsas[i].mercado, mem->bolsas[i].acao, mem->bolsas[i].preco);
    }


    fclose(ptr);
    sem_post(&mem->write);
}

void process_client(int client_fd)
{   
    
	int nread = 0;
	char buffer[BUF_SIZE];
    int login = 0;
    char username[50];
    char password[50];
    char loggedin[20] = "LOGGED IN\n";
    char fail[30] = "USER DOES NOT EXIST\n";
    char mess[100];
    int index = 0;
    
    //loop para efetuar o login e guardar as informaçoes de um user
    do {
        strcpy(mess, "login: ");
        write(client_fd, mess, 1 + strlen(mess));
        memset(mess, 0 , strlen(mess));
        nread = read(client_fd, buffer, BUF_SIZE-1);
        buffer[nread] = '\0';
        
        char * tok = strtok(buffer, " \n");
        strcpy(username, tok);
        tok = strtok(NULL," \n");
        strcpy(password, tok);
        for (int i = 0; i < mem->nusers; i++)
        {
            if(strcmp(username, mem->users[i].name) == 0 && strcmp(password, mem->users[i].password) == 0){
                write(client_fd, loggedin, 1 + strlen(loggedin));
                login = 1;
                //guardo o index do user para poder ir buscar as infos dele a estrutura diretamente e modificar se for necessario
                index = i;
                break;
            }
        }
        
        if(login == 0){
            write(client_fd, fail, 1 + strlen(fail)); 
            sleep(1);
        }
        else{
            fflush(stdout);
            break;
        }

        fflush(stdout);
    } while (nread>0);
        
    if(strcmp(mem->users[index].bolsa1, "vazio") == 0 && strcmp(mem->users[index].bolsa2, "vazio") == 0){
        strcpy(mess, "nao tem permissoes para nenhum mercado");
        write(client_fd, mess, 1 + strlen(mess));
        memset(mess, 0 , strlen(mess));
        close(client_fd);
    }
    for (int i = 0; i <6 ; i++)
    {
        sleep(1);
        char info[100] = "MERCADO: ";
        char aux[50];
        if(strcmp(mem->bolsas[i].mercado, mem->users[index].bolsa1) == 0 ||strcmp( mem->bolsas[i].mercado, mem->users[index].bolsa2) == 0){
            strcat(info, mem->bolsas[i].mercado);
            strcat(info, " ACAO: ");
            strcat(info, mem->bolsas[i].acao);
            sprintf(aux, "%f",mem->bolsas[i].preco);
            strcat(info, " PRECO: ");
            strcat(info, aux);
            strcat(info, "\n");
            write(client_fd, info, 1 + strlen(info));
        }
    }
    //------------------------------------------------
    char options[150] = "1 - ligar feed\n2 - desligar feed\n3 - conteudo carteira\n4 - subscrever\n5 - comprar\n6 - vender\n7 - sair\n";
    char aux[50];
    
    int on = 0;
    pthread_t feed;
    inf threadinfo;
    threadinfo.fd = client_fd;
    threadinfo.index = index;
    do {
        
        write(client_fd, options, 1 + strlen(options));
        nread = read(client_fd, buffer, BUF_SIZE-1);
        buffer[nread] = '\0';
        //ligar e desligar atualizacao de feed
        
        if(strcmp(buffer, "1\n") == 0){
            if(on == 0){
                
                pthread_create(&feed, NULL, showfeed, &threadinfo);
            }
            if(on == 1)
            {
                strcpy(mess, "feed is already on\n");
                write(client_fd, mess, 1 + strlen(mess));
                memset(mess, 0 , strlen(mess));
            }
            on= 1;
            
        }
        if(strcmp(buffer, "2\n") == 0){
            if(on == 1){
                pthread_cancel(feed);
            }
            else{
                strcpy(mess, "feed is already off\n");
                write(client_fd, mess, 1 + strlen(mess));
                memset(mess, 0 , strlen(mess));
            }
            on = 0;
            
        }
        //ver o conteudo da carteira do user, saldo e numero de acoes as quais esta inscrito
        if(strcmp(buffer, "3") == 0){
            strcpy(mess, "--------CARTEIRA-------\n");
            strcat(mess, "SALDO: ");
            sprintf(aux, "%f", mem->users[index].saldo);
            strcat(mess, aux);
            strcat(mess,"\n");
            for (int i = 0; i < 6; i++)
            {
                if(mem->users[index].acoes[i].inscrito == true){
                    strcat(mess, mem->users[index].acoes[i].nome);
                    strcat(mess,": ");
                    sprintf(aux, "%d", mem->users[index].acoes[i].quantidade);
                    strcat(mess, aux);
                    strcat(mess, "\n");
                }
            }
            
            write(client_fd, mess, 1+strlen(mess));
            memset(mess, 0 , strlen(mess));
            
        }
        if(strcmp(buffer, "4") == 0){
            strcpy(mess, "----acoes----\n");
            for (int i = 0; i < 6 ; i++)
            {
                if(strcmp(mem->bolsas[i].mercado, mem->users[index].bolsa1) == 0 ||strcmp( mem->bolsas[i].mercado, mem->users[index].bolsa2) == 0){
                    
                    sprintf(aux, "%d", i + 1);
                    strcat(mess, aux);
                    strcat(mess, " - ");
                    strcat(mess, "ACAO: ");
                    strcat(mess, mem->bolsas[i].acao);
                    strcat(mess, "\n");
                    
                }
            }
            write(client_fd, mess, 1 + strlen(mess));
            memset(mess, 0 , strlen(mess));

            nread = read(client_fd, buffer, BUF_SIZE-1);
            buffer[nread] = '\0';
            char * tok = strtok(buffer, " \n");
            int choice = atoi(tok);
            mem->users[index].acoes[choice-1].inscrito = true;
            
        }
        if(strcmp(buffer, "5") == 0){
            char acao[50];
            float preco;
            int quantidade;

            //uma funcao que verifica se o user esta subscrito em alguma acao
            if(inscrito(index)){
                strcpy(mess, "compra: ");
                write(client_fd, mess, 1 + strlen(mess));
                memset(mess, 0 , strlen(mess));
            //exemplo: acao preco quantidade
                nread = read(client_fd, buffer, BUF_SIZE-1);
                buffer[nread] = '\0';

                char * tok = strtok(buffer, " \n");
                strcpy(acao, tok);
                tok = strtok(NULL, " \n");
                preco = atof(tok);
                tok = strtok(NULL, " \n");
                quantidade = atoi(tok);
                
            
                for (int i = 0; i < 6; i++)
                {   
                    //encontrar a acao que o user especificou e verificar se esta inscrito nela
                    if(strcmp(mem->users[index].acoes[i].nome , acao) == 0 && mem->users[index].acoes[i].inscrito == true){
                        //verificar se tem saldo suficiente para aquilo que o user pediu
                        if(preco * quantidade <= mem->users[index].saldo){
                            //verificar se a bolsa tem quantidade suficiente para aquilo que o user pediu
                            if(quantidade <= mem->bolsas[i].quantidade){
                                printf("%f",preco -  mem->bolsas[i].preco );
                                //verificar se a diferença depreço esta entre 0 e 0.02
                                if( preco -  mem->bolsas[i].preco >= 0 && preco -  mem->bolsas[i].preco<= 0.02){
                                    mem->bolsas[i].quantidade -= quantidade;
                                    mem->users[index].acoes[i].quantidade += quantidade;
                                    mem->users[index].saldo -= preco;
                                    strcpy(mess, "COMPRA REALIZADA\n");
                                    write(client_fd, mess, 1 + strlen(mess));
                                    memset(mess, 0 , strlen(mess));
                                }
                                else{
                                    strcpy(mess, "PRECO DO COMPRADOR BAIXO\n");
                                    write(client_fd, mess, 1 + strlen(mess));
                                    memset(mess, 0 , strlen(mess));
                                }
                            }
                            else{
                                strcpy(mess, "STOCK INSUFICIENTE\n");
                                write(client_fd, mess, 1 + strlen(mess));
                                memset(mess, 0 , strlen(mess));
                            }
                            
                        }
                        else{
                            strcpy(mess, "SALDO INSUFICIENTE\n");
                            write(client_fd, mess, 1 + strlen(mess));
                            memset(mess, 0 , strlen(mess));
                        }
                    }
                
                }
            }
            else{
                strcpy(mess, "NAO ESTA INSCRITO EM NENHUMA ACAO\n");
                write(client_fd, mess, 1 + strlen(mess));
                memset(mess, 0 , strlen(mess));
            }
            
            
        }
        if(strcmp(buffer, "6") == 0){
            char acao[50];
            float preco;
            int quantidade;
            
            //uma funcao que verifica se o user esta subscrito em alguma acao
            
            if(inscrito(index) && carteira(index)){
            strcpy(mess, "venda: ");
            write(client_fd, mess, 1 + strlen(mess));
            memset(mess, 0 , strlen(mess));
            //exemplo: acao preco quantidade
                nread = read(client_fd, buffer, BUF_SIZE-1);
                buffer[nread] = '\0';

                char * tok = strtok(buffer, " \n");
                strcpy(acao, tok);
                tok = strtok(NULL, " \n");
                preco = atof(tok);
                tok = strtok(NULL, " \n");
                quantidade = atoi(tok);
                
            
                for (int i = 0; i < 6; i++)
                {   
                    //encontrar a acao que o user especificou e verificar se esta inscrito nela
                    if(strcmp(mem->users[index].acoes[i].nome , acao) == 0 && mem->users[index].acoes[i].inscrito == true){
                        if(quantidade <= mem->users[index].acoes[i].quantidade){
                            printf("%f", mem->bolsas[i].preco - preco);
                            if( mem->bolsas[i].preco - preco >= 0 && mem->bolsas[i].preco - preco <= 0.02){

                                mem->bolsas[i].quantidade += quantidade;
                                mem->users[index].acoes[i].quantidade -= quantidade;
                                mem->users[index].saldo += preco;
                                strcpy(mess, "VENDA REALIZADA\n");
                                write(client_fd, mess, 1 + strlen(mess));
                                memset(mess, 0 , strlen(mess));
                            }
                            else{
                                strcpy(mess, "PRECO DO VENDEDOR ALTO\n");
                                write(client_fd, mess, 1 + strlen(mess));
                                memset(mess, 0 , strlen(mess));
                            }
                        }
                        else{
                            strcpy(mess, "NAO TEM ACOES SUFICIENTES PARA VENDER\n");
                            write(client_fd, mess, 1 + strlen(mess));
                            memset(mess, 0 , strlen(mess));
                        }
                    }
                
                }
            }
            else{
                strcpy(mess, "NAO ESTA INSCRITO EM NENHUMA ACAO OU NAO TEM ACOES PARA VENDER\n");
                write(client_fd, mess, 1 + strlen(mess));
                memset(mess, 0 , strlen(mess));
            }
            
            
        }
        if(strcmp(buffer, "7") == 0){
            fflush(stdout);
            close(client_fd);
        }
        fflush(stdout);
    } while (nread>0);
    pthread_join(feed, NULL);
    close(client_fd);
}

void porto_bolsa(){
    int fd, client;
    int client_addr_size;
    
    bzero((void *) &addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(mem->tport);

    if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        erro("na funcao socket");
    if ( bind(fd,(struct sockaddr*)&addr,sizeof(addr)) < 0)
        erro("na funcao bind");
    if( listen(fd, 5) < 0)
        erro("na funcao listen");
    client_addr_size = sizeof(client_addr);
    while (1) {
        //clean finished child processes, avoiding zombies
        //must use WNOHANG or would block whenever a child process was working
        while(waitpid(-1,NULL,WNOHANG)>0);
        //wait for new connection
        client = accept(fd,(struct sockaddr *)&client_addr,(socklen_t *)&client_addr_size);
        if (client > 0) {
        if (fork() == 0) {
            close(fd);
            process_client(client);
            exit(0);
        }
        close(client);
        }
    }
    exit(0);
}

void porto_config(){
    
    
    mem->refresh = 2;
    
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
        si_minha.sin_port = htons(mem->uport);
        si_minha.sin_addr.s_addr = htonl(INADDR_ANY);

        // Associa o socket à informação de endereço
        if (bind(s, (struct sockaddr *)&si_minha, sizeof(si_minha)) == -1)
        {
        erro("Erro no bind");
        }

        while(1){
            if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_outra, (socklen_t *)&slen)) == -1)
            {
            erro("Erro no recvfrom");
            }
            
            buf[recv_len] = '\0';
            if (strcmp(buf, "X") == 0){
            continue;
            }
            else{break;}
            
        }

        // while(1){
            
        //     if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_outra, (socklen_t *)&slen)) == -1)
        //     {
        //       erro("Erro no recvfrom");
        //     }
            
        //     buf[recv_len] = '\0';
        //     char *tok = strtok(buf, " /\n"); 
            
        //     if(strcmp(adm.name, tok) == 0){
        //         printf("yey\n");
        //     }
        //     else{
        //         printf("no \n");
        //     }
            
        // }

        

        while (1)
        {
            
            if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_outra, (socklen_t *)&slen)) == -1)
            {
            erro("Erro no recvfrom");
            }
            
            buf[recv_len] = '\0';
            
            

            char *tok = strtok(buf, " \n"); 
            char send[100] = "\0";
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
                addUser(param1, param2, param3, atof(param4));
                writefile();
                strcpy(send, "Users updated\n");
                sendto(s,send,100,0,(struct sockaddr *)&si_outra,slen);

            }
            else if (strcmp(tok, "REFRESH") == 0)
            {
                char charrefresh[10];
                tok = strtok(NULL, " \n");
                mem->refresh = atoi(tok);
                strcpy(send, "REFRESH TIME changed to: ");
                sprintf(charrefresh, "%d", mem->refresh);
                strcat(send, charrefresh);
                strcat(send, " seg\n");
                sendto(s,send,100,0,(struct sockaddr *)&si_outra,slen);
                //printf("REFRESH TIME changed to: %d seg\n", refresh);
            }
            else if (strcmp(tok, "LIST") == 0)
            {
            
            //loops for the users array
            for (int i = 0; i < mem->nusers; i++)
            {

                char userid[3];
                char charsaldo[10];
                strcpy(send, "user ");
                sprintf(userid, "%d", i +1);
                strcat(send, userid);
                strcat(send, ":\nname: ");
                strcat(send, mem->users[i].name);
                strcat(send, "\nsaldo: ");
                sprintf(charsaldo, "%f", mem->users[i].saldo);
                strcat(send, charsaldo);
                strcat(send, "\nbolsa1: ");
                strcat(send, mem->users[i].bolsa1);
                strcat(send, "\nbolsa2: ");
                strcat(send, mem->users[i].bolsa2);
                strcat(send, "\n\n");
                sendto(s,send,100,0,(struct sockaddr *)&si_outra,slen);

            }

            }
            else if (strcmp(tok, "DEL") == 0)
            {
                tok = strtok(NULL, " \n");
                strcpy(param1, tok);
                if(deleteuser(param1) > 0){
                writefile();
                strcpy(send, "User Deleted\n");
                sendto(s,send,100,0,(struct sockaddr *)&si_outra,slen);
                }
                else{
                    strcpy(send, "user not found");
                    sendto(s,send,100,0,(struct sockaddr *)&si_outra,slen);
                }

                //printf("USER DELETED");
            }

            else if (strcmp(tok, "QUIT") == 0)
            {
                close(s);
                printf("CLOSING CONNECTION\n");
                break;
            }
            else if (strcmp(tok, "QUIT_SERVER") == 0)
            {
                return ;
            }
            else
            {
                printf("COMMAND DOES NOT EXIST\n");
            }
            
        }
    
        // Fecha socket e termina programa
        
        close(s);
        exit(0);
}

void erro(char *s) {
	perror(s);
	exit(1);
	}


void * refreshtime(){
    while(1){
        sleep(mem->refresh);

        for (int i = 0; i < 6; i++)
        {   
            if (rand()%2 == 0){
                mem->bolsas[i].preco += 0.01;
            } 
            else{
                mem->bolsas[i].preco -= 0.01;
            }
        }
        writefile();
    }

    return NULL;
}

void * showfeed(void * arg){
    
    inf threadinfo = *((inf*)arg);

    while(1){
        pthread_mutex_lock(&feedmutex);
        sleep(mem->refresh);
        for (int i = 0; i < 6 ; i++)
        {
            char info[100];
            char aux[50];
            if(mem->users[threadinfo.index].acoes[i].inscrito == true){
                
                strcpy(info, "ACAO: ");
                strcat(info, mem->bolsas[i].acao);
                sprintf(aux, "%f",mem->bolsas[i].preco);
                strcat(info, " PRECO: ");
                strcat(info, aux);
                strcat(info, " QUANTIDADE: ");
                sprintf(aux, "%d", mem->bolsas[i].quantidade);
                strcat(info,aux);
                strcat(info, "\n");
                write(threadinfo.fd, info, 1 + strlen(info));
            }
        }
        
        pthread_mutex_unlock(&feedmutex);
    }
}  

bool inscrito(int idx){
    for (int i = 0; i < 6; i++)
    {
        if(mem->users[idx].acoes[i].inscrito== true){
            return true;
        }
    }
    return false;
    
}

bool carteira(int idx){
    for (int i = 0; i < 6; i++)
    {
        if(mem->users[idx].acoes[i].quantidade > 0){
            return true;
        }
    }
    return false;
}
