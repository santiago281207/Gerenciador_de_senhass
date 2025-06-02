#define _CRT_SECURE_NO_WARNINGS
#define MAX_COMP_PASS 30
#define MIN_COMP_PASS 6


#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>


int EntreAB(int n,int min,int max);
int IsInString(char caracter,char string[]);    //Verifica se um caracter esta numa string
int Check_Password_Strenght(char password[]);   
int PassValid(char senha[]);    //Verificar se password e valida
void Generate_Random_Password(char passwd[],int comp);  //Gerar password aleatoria



int main()
{
    int criadas = 1;
    int comprimento_pass = 0;   //Comprimento que o utilizador quiser a palavra passe aleatoria
    char choice;    //Escolha do menu
    char senha[MAX_COMP_PASS+1];    //Verificar senha
    char generated_password[MAX_COMP_PASS+1];   //Senha randomizada
    FILE* log;  //Ficheiro


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
            case '1':   //Verificar password do user
                do
                {
                    printf("Digite a sua senha: ");
                    scanf("%s",senha);
                    fflush(stdin);
                    if(PassValid(senha) == 0)   
                    {
                        puts("Introduza uma palavra passe que nao contenha espacos.");
                    }
                } while (PassValid(senha) == 0);    //Verifica se a password é valida (nao tem espacos)
                getchar();

                switch(Check_Password_Strenght(senha)) //Verifica o valor retornado pela funcao 1-fraco 2-medio 3- forte
                {
                    case 1:
                    printf("Forca de password: Fraca\n\n");
                    break;
                case 2:
                    printf("Forca da password: Media\n\n");
                    break;
                case 3:
                    printf("Forca da password: Forte\n\n");
                    break;
                default:
                    printf("ERRO!\n");
                    break;
            }

            case '2':   //Gerar password forte
                do
                {
                    printf("Indique o comprimento da senha desejada (%d-%d): ",MIN_COMP_PASS,MAX_COMP_PASS);  //Comprimento da password
                    scanf("%d",&comprimento_pass);
                    if(EntreAB(comprimento_pass,MIN_COMP_PASS,MAX_COMP_PASS) == 0)  //Se comprimento nao for valido
                    {
                        printf("ERRO-Valor nao esta entre %d e %d: ",MIN_COMP_PASS,MAX_COMP_PASS);
                    }
                } while (EntreAB(comprimento_pass,MIN_COMP_PASS,MAX_COMP_PASS) == 0);
                    
                Generate_Random_Password(generated_password,comprimento_pass);  //Gerar password aleatoria

                printf("Password gerada: ");
                Sleep(2000);    //Esperar 2 segundos
                printf("Password gerada: %s\n\n",generated_password);   //Mostrar password gerada

                log = fopen("log.txt","w");
                if(log == NULL)
                {
                    printf("ERRO - nao deu para criar ficheiro!");
                }
                else
                {
                    fprintf(log,"%dº Passowrd gerada: %s\n",criadas,generated_password);
                    criadas++;
                }
                break;

            case '3':
                printf("Saindo...");
                Sleep(3000);
                break;
            }

            if(choice == '3')
            {
                break;
            }
        }

    if(criadas > 1)
        printf("Um ficheiro foi criado com as passwords geradas!\n");
    return 0;
    }



int Check_Password_Strenght(char password[])
{
    char letras_upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char letras_lower[] = "abcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    char special[] = "!#$%%&/()=?+*-@£§{}_.";

    int i = 0,total = 0,strenght;
    size_t qtd_caracteres = strlen(password);  //Tem de ser maior do que 7 caracteres
    int qtd_caracteres_check = 0;
    int letras_upper_check = 0; //Tem letras grandes?
    int letras_lower_check = 0; //Tem minusculas?
    int numbers_check = 0;  //tem numeros?
    int special_symbols_check = 0;  //tem simbolos especiais?

    if(qtd_caracteres > 6)
    {
        qtd_caracteres_check = 1;
    }
    
    for(i = 0;password[i] != '\0';i++)
    {
        if(isalpha(password[i]))
        {
            if(letras_upper_check == 0)
            {
                letras_upper_check += IsInString(password[i],letras_upper);
            }
            if(letras_lower_check == 0)
            {
                letras_lower_check += IsInString(password[i],letras_lower);
            }
        }
        else if(isdigit(password[i]) && numbers_check == 0)
        {
            numbers_check += IsInString(password[i],digits);
        }
        else if(special_symbols_check == 0)
        {
            special_symbols_check += IsInString(password[i],special);
        }

    }

    total = special_symbols_check + letras_lower_check + letras_upper_check + numbers_check + qtd_caracteres_check;
    
    switch(total)
    {
        case 2: case 1:
            strenght = 1;   //Palavra passe fraca
            break;
        case 3: case 4:
            strenght = 2;   //Plavra passe media
            break;
        case 5:
            strenght = 3;  //Palavra passe forte
            break;
    }
    return strenght;
}

int IsInString(char caracter,char string[])
{
    size_t i = 0;

    for(i = 0;i < strlen(string);i++)
    {
        if(string[i] == caracter)
            return 1;
    }
    return 0;
}

int EntreAB(int n,int min,int max)
{
    return n >= min && n <= max;
}

void Generate_Random_Password(char passwd[],int comp)  //Gerar password aleatoria
{
    char upper_letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower_letters[] = "abcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    char special[] = "!#$%%&/()=?+*-@£§{}_.";

    size_t i = 0,choosen_character_type = 0,pos_choosen = 0;

    srand(time(NULL));

    for(i = 0;i < comp;i++);
    {
        choosen_character_type = rand() % 4 + 1;

        if(choosen_character_type == 1)
        {
            pos_choosen = rand() % strlen(upper_letters) + 1;
            passwd[i] = upper_letters[pos_choosen];
        }
        else if(choosen_character_type == 2)
        {
            pos_choosen = rand() % strlen(special) + 1;
            passwd[i] = special[pos_choosen];
        }
        else if(choosen_character_type == 3)
        {
            pos_choosen = rand() % strlen(digits) + 1;
            passwd[i] = digits[pos_choosen];
        }
        else
        {
            pos_choosen = rand() % strlen(lower_letters) + 1;
            passwd[i] = lower_letters[pos_choosen];
        }

    }
    passwd[i] = '\0';
}

int PassValid(char senha[])
{
    size_t i = 0;

    for(i = 0;i < strlen(senha);i++)
    {
        if(senha[i] == ' ')
            return 0;
    }
    return 1;
}