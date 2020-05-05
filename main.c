#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch;
    int intlength=0;
    char integer[10];
    FILE*fileR;
    FILE*fileW;

    fileR=fopen("code.psi.txt","r");
    fileW=fopen("code.lex.txt","w");

    fseek(fileR, 0, SEEK_END);//get file size.
    int size = ftell(fileR);
    fseek(fileR, 0, SEEK_SET);
    //char filearray[size];//array for file.

    if(fileR != NULL)//eger dosya var ise
    {
        while((ch = fgetc(fileR)) != EOF)
        {
            if(ch == ' ' || ch=='\n' || ch=='\t')//bosluklari saymamamiz gerek.
                    {
                        ch=fgetc(fileR);
                    }
            if(ch=='*' || ch=='/' || ch=='+' || ch=='-' || ch==':')//operator durumu.
                    {
                    if(ch=='*')//* operator'u var ise yazdiriyoruz.
                        {
                            fputs("Operator(*)\n",fileW);
                        }
                    if(ch=='/')
                        {
                            fputs("Operator(/)\n",fileW);
                        }
                    if(ch=='+')
                        {
                            ch=fgetc(fileR);
                            if(ch == '+')//++ operator'u var ise yazdiriyoruz.
                                {
                                    fputs("Operator(++)\n" , fileW);
                                }
                            else//+ operator'u durumu.
                                {
                                    fputs("Operator(+)\n" , fileW);
                                    continue;
                               }
                        }
                    if(ch=='-')
                        {
                            ch=fgetc(fileR);
                            if(ch=='-')//-- operator'u var mi diye bakiyoruz.
                                {
                                    fputs("Operator(--)\n",fileW);
                                }
                            else//- operator'u durumu.
                                {
                                    fputs("Operator(-)\n" ,fileW);
                                }
                        }
                    if(ch==':')//:= operator durumunu inceliyoruz.
                        {
                            if(fgetc(fileR) == '=')//eger : dan sonra = geliyorsa bu operatordur.
                                {
                                    fputs("Operator(:=)\n" ,fileW);
                                }
                        }
            }

            if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')
                {
                    printf("%c",ch);
                    integer[intlength]=ch;
                    while(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')
                        {
                            intlength++;
                            if(intlength>10)
                                {
                                    printf("Error Message : Integer value can not be longer than 10 digit!");
                                }
                            else
                                {
                                    integer[intlength] = ch ;
                                    //printf("%c",  integer[intlength]);
                                    ch=fgetc(fileR);
                                }
                        }
                        fputs("IntConst(",fileW);
                        fputs(integer, fileW);
                        fputs(")\n",fileW);
                        intlength=0;

                }
            if(ch==';')//End Of Line ise.
                {
                    endofLine(fileW);
                }
        }//if
    }//while
}//main
void endofLine(FILE*fileW)
{
    fputs("EndofLine\n",fileW);
}


