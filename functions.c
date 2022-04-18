#include "functions.h"

bool getLine(int l, char line[])
{

    int linecounter = 0;
    char ch;
    int i = 0;
    FILE *ptr;
    ptr = fopen(FILENAME, "r");
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
                    aux.saldo = atoi(temp);
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
        users[i - 3] = aux;
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

        bolsas[i - 3 - numberofusers] = aux;
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
                strcpy(adm.name, temp);
            }
            if (param == 1)
            {
                strcpy(adm.password, temp);
            }
            temp[0] = '\0';
            w = 0;
            param++;
        }
    }
}


void listusers(int tam)
{
    //loops for the users array
    for (int i = 0; i < tam; i++)
    {
        printf("user %d:\nname: %s\nsaldo: %d\nbolsa1: %s\nbolsa2: %s\n\n",
               i + 1, users[i].name, users[i].saldo, users[i].bolsa1, users[i].bolsa2);
    }
}

//if exists return the position in the array
//else rerturn -1
int searchUser(char *name, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        if(strcmp(name, users[i].name) == 0){
            return i;
        }
    }
    return -1;
}

void addUser(char *name, char*password, char*bolsas, int saldo, int *tam){
    //get the position
    int pos = searchUser(name, *tam);
    struct user aux;
    if(pos >= 0){
        //check if the bolsas are empty if the name exists
        if(strcmp(users[pos].bolsa1, "vazio") == 0){
            strcpy(users[pos].bolsa1, bolsas);
            printf("bolsa 1 alterada\n");
        }
        else if(strcmp(users[pos].bolsa2, "vazio") == 0){
            strcpy(users[pos].bolsa2, bolsas);
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
        users[*tam] = aux;
        (*tam)++;
        printf("Utilizador adicionado com sucesso\n\n");
    }
}


void deleteuser(char* name, int *tam){
    //get the position of the user to delete
    int pos = searchUser(name, *tam);
    if (pos >= 0 && pos + 1 < 10){

        for (int i = pos; i < *tam; i++)
        {
            //shift to the left and ignore the last one
            users[i] = users[i +1];
        }

        (*tam)--;
    }
    else if(pos < 0){
        printf("User Not Found!\n");
    }
}

void writefile(int tam){
    FILE * ptr;
    ptr = fopen(FILENAME, "w");
    //add admin
    fprintf(ptr, "%s/%s\n", adm.name, adm.password);
    //add numero de users atualizado
    fprintf(ptr, "%d\n", tam);
    for (int i = 0; i < tam; i++)
    {
        //se nenhuma bolsa esta assianda
        if(strcmp(users[i].bolsa1, "vazio") == 0 && strcmp(users[i].bolsa1, "vazio")==0){
           fprintf(ptr, "%s;%s;%d\n", users[i].name, users[i].password, users[i].saldo);
        }
        //se apenas assinou uma bolsa
        else if(strcmp(users[i].bolsa1, "vazio") != 0 && strcmp(users[i].bolsa2, "vazio")==0){
           fprintf(ptr, "%s;%s;%d;%s\n", users[i].name, users[i].password, users[i].saldo, users[i].bolsa1);
        }
        //tem as duas bolsas assinadas
        else{
            fprintf(ptr, "%s;%s;%d;%s;%s\n", users[i].name, users[i].password, users[i].saldo, users[i].bolsa1,users[i].bolsa2);
        }
    }
    //add markets
    for (int i = 0; i < 6; i++)
    {
        fprintf(ptr, "%s;%s;%1f\n", bolsas[i].mercado, bolsas[i].acao, bolsas[i].preco);
    }


    fclose(ptr);
}

void erro(char *s) {
	perror(s);
	exit(1);
	}
