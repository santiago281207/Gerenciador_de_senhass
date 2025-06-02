#define MAX_COMP_PASS 30
#define MIN_COMP_PASS 1



#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int Check_Password_Strenght(char password[]);
int PassValid(char senha[]);
void Generate_Random_Password(char passwd[],int comp);




int main()
{
    int comprimento_pass = 0;
    char choice;
    char senha[MAX_COMP_PASS+1];
    char generated_password[MAX_COMP_PASS+1];

    while(1)    //Ciclo que mantem sempre a correr
    {
        puts("=== Gerenciador de senhas ===");
        puts("1- Verificar senha");
        puts("2- Gerar senha forte");
        puts("3- Sair");
        do
        {
            scanf("%c",&choice);
            fflush(stdin);
            if(isdigit(choice) != 1)
            {
                puts("Introduza um numero.");
            }
        } while (isdigit(choice) != 1);
        
        switch(choice)  //Verificar escolha do utilizador
        {
            case '1':
            do
            {
                printf("Digite a sua senha: ");
                scanf("%s",senha);
                fflush(stdin);
            } while (PassValid(senha) == 0);

            switch (Check_Password_Strenght(senha))
            {
            case 1:
                printf("Forca de password: Fraca\n");
                break;
            case 2:
                printf("Forca da password: Media\n");
                break;
            case 3:
                printf("Forca da password: Forte\n");
                break;
            default:
            printf("ERRO!\n");
                break;

            case '2':
                do
                {
                    printf("Indique o comprimento da senha desejada (%d-%d): ",MIN_COMP_PASS,MAX_COMP_PASS);
                    scanf("%d",&comprimento_pass);
                    if(EntreAB(comprimento_pass,MIN_COMP_PASS,MAX_COMP_PASS) == 0)
                    {
                        printf("ERRO-Valor nao esta entre %d e %d: ",MIN_COMP_PASS,MAX_COMP_PASS);
                    }
                } while (EntreAB(comprimento_pass,MIN_COMP_PASS,MAX_COMP_PASS) == 0);
                    
                Generate_Random_Password(generated_password,comprimento_pass);

                printf("Password gerada: ");
                Sleep(2000);
                puts(generated_password);
                break;
            case '3':
                printf("Saindo...");
                Sleep(3000);
                break;
            }
        }
    }
    return 0;
}