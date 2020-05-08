#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main()
{
    char ch;
    int intlength=0;
    char integer[10];
    char word[20];
    char keywords[18][8]={"break","case","char","const","continue","do","else","enum","float","for","goto","if","int","long","record","return","static","while"};
    char string[500];
    char comments[500];

    FILE*fileR;//dosya islemleri
    FILE*fileW;
    fileR=fopen("code.psi.txt","r");
    fileW=fopen("code.lex.txt","w");
    fseek(fileR, 0, SEEK_END);//get file size.
    int size = ftell(fileR);
    fseek(fileR, 0, SEEK_SET);

    ch=fgetc(fileR);//ilk chari aliyoruz
    if(fileR != NULL)//eger dosya var ise
    {
        while(!feof(fileR))
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
                            else
                                {
                                    printf("ERROR: Undefined operator!");
                                    return 1;
                                }
                        }
            }

            if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')//integer durumu
                {
                    integer[intlength]=ch;
                    ch=fgetc(fileR);
                    while(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')
                        {
                            intlength++;
                            integer[intlength]=ch;
                            ch=fgetc(fileR);
                        }
                    if(intlength>10)
                        {
                            printf("ERROR : Maximum integer size is 10 digits . ");
                        }
                    else
                        {
                            fputs("IntConst(",fileW);
                            fputs(integer, fileW);
                            fputs(")\n",fileW);
                        }
                    intlength=0;
                    continue;

                }
            if(ch==';')//End Of Line ise.
                {
                    endofLine(fileW);
                }
            if(ch=='('|| ch==')'|| ch=='[' || ch==']'||ch=='{'||ch=='}')//brackets kontrolu.
                {
                    bracketsControl(fileW,ch);
                }
            /*if(ch=='"')//strings kontrolu
                {
                    int counter=0;
                    ch=fgetc(fileR);
                    while(ch!='"')
                    {
                        string[counter]=ch;
                        counter++;
                        ch=fgetc(fileR);
                        if(ch==EOF)
                            {
                                printf("ERROR :a string constant cannot terminate before the file end");
                                break;
                            }
                    }

                    string[counter]='\0';//bu iki satiri yapmazsak K\ gibi bir durum söz konusu kaliyordu.
                    string[counter+1]='0';
                    fputs("String Constants (" ,fileW );
                    fputs(string,fileW);
                    fputs(")\n" ,fileW);
                }*/
            if(ch=='(')//parantez ile basliyor ve
                {
                   ch=fgetc(fileR);
                   if(ch=='*')//* ile devam ediyor ise
                   {
                        int counter=0;
                        ch=fgetc(fileR);
                        while(ch!='*' && ch!=EOF)
                        {
                            comments[counter]=ch;
                            counter++;
                            ch=fgetc(fileR);
                        }
                        if(ch=='*')
                        {
                            ch=fgetc(fileR);
                            if(ch==')')//*dan sonra ) ile de kapaniyorsa yorum satiri demektir.
                            {
                                comments[counter]='\0';
                                comments[counter+1]='\0';
                            }
                             else if(ch==EOF)//yorum bitmeden dosya biterse lexical error.
                            {
                                printf("ERROR : a comment cannot terminate before the file end");
                            }
                        }

                   }


                }
                ch=getc(fileR);
        }//if
    }//while
}//main

void bracketsControl(FILE*fileW , char ch)
{
    if(ch=='(')
    {
        fputs("LeftPar\n" , fileW);
    }
    if(ch==')')
    {
        fputs("RightPar\n", fileW);
    }
    if(ch=='[')
    {
        fputs("LeftSquareBracket\n", fileW);
    }
    if(ch==']')
    {
        fputs("RightSquareBracket\n", fileW);
    }
    if(ch=='{')
    {
        fputs("LeftCurlyBracket\n", fileW);
    }
    if(ch=='}')
    {
        fputs("RightCurlyBracket\n", fileW);
    }

}

void endofLine(FILE*fileW)
{
    fputs("EndofLine\n",fileW);
}
