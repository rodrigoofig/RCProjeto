#include "functions.h"



int main(){
    
    
    FILE * ptr;
    char line[100];
    
    int refresh = 1;
    if(getline(2,line));

    //save the number of users
    int nUsers = atoi(line);

    //pointer to change it inside functions
    int *ptrusers = &nUsers;

    //read the config.txt and create structs
    userstruct();
    bolsatruct();
    adminstruct();
    

    while(1){
        char input[200];
        fgets(input, 200, stdin);
        char *tok = strtok(input, " \n");
        char param1[50];
        char param2[50];
        char param3[50];
        char param4[50];


        if(strcmp(tok, "ADD_USER") == 0){
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
        else if(strcmp(tok, "LIST") == 0){
            listusers(*ptrusers);
        }
        else if(strcmp(tok, "DEL") == 0){
            tok = strtok(NULL, " \n");
            strcpy(param1, tok);
            deleteuser(param1, ptrusers);
            writefile(*ptrusers);
        }
        else if(strcmp(tok, "REFRESH") == 0){
            printf("aqui");
            tok = strtok(NULL, " \n");
            refresh = atoi(tok);
            printf("REFRESH TIME changed to: %s seg\n", refresh);
        }
        else if(strcmp(tok, "QUIT") == 0){
            
            break;
        }
        else if(strcmp(tok, "QUIT_SERVER") == 0){
            
            return 1;
        }
        else{
            printf("COMMAND DOES NOT EXIST\n");
        }

    }

    return 0;
}



