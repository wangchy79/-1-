#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;
int i, row = 0, line = 0;
char test[1000]; 
int number[100];	
char mark[100][5];   

int alysis(ofstream &fout)
{

    if ((test[i] >= 'A'&&test[i] <= 'Z')||(test[i]>='a'&&test[i]<='z'))  
    {
        char word[10];
        char keyword[100][100] = { "char",
                                "int","if","else","var" ,"return","break",
								"do","while","for","double","float","short","getc"}; 

        int n = 0;
        word[n++] = test[i++];
        while ((test[i] >= 'A'&&test[i] <= 'Z') || (test[i] >= '0' && test[i] <= '9')||(test[i]>='a'&&test[i]<='z'))
        {
            word[n++] = test[i++];
        }
        word[n] = '\0';
        i--;

        for (n = 0; n < 100; n++)
        {
            if (strcmp(word, keyword[n]) == 0)
            {
                fout <<  keyword[n] << "\t " << n+4 <<" keyword" << endl;
                return 3;
            }
        }

        int m = 0;
        if (line != 0)
        {
            int q = 0;
            while (q<line)
            {
                if (strcmp(word, mark[q++]) == 0)
                {
                    fout << word << "\t " << 0 <<" definition"<< endl;
                    return 3;
                }
            }

        }

        strcpy(mark[line], word);
        fout << word << "\t" << 0 <<" definition"<< endl;
        line++;
        return 3;

    }
    else if (test[i] >= '0' && test[i] <= '9')  
    {
        char x[100];
        int n = 0;
        x[n++] = test[i++];
        
        while (test[i] >= '0' && test[i] <= '9')
        {
            x[n++] = test[i++];
        }
        x[n] = '\0';
        i--;
        int num = atoi(x); //将字符串转换成int型
        
        if (row != 0)
        {   
            
            for(int y=0;y<row;y++)
            {
            	if(number[y]==num)
            	{
            		fout << num << "\t "<< 3<< " number"<<endl;
                    return 3;
				}
			}
        }
        
        number[row]=num;
        int line = row;
        fout << num << "\t "<< 3 <<" number" <<endl;
        row++;

        return 3;
    }
    else                      
    	switch (test[i])
    {
        case ' ':
        case '\n':
            return -1;
        case '#': return 0;
        case '=':fout << "=\t" << 17 <<" PT" <<endl;  return 3;
        case '<':
            i++;
            if (test[i] == '=')
            {
                fout << "<=\t" << 19 <<" PT" << endl;
                return 3;
            }
            else
            {
                i--;
                fout << "<\t" <<  18 <<" PT" <<endl;
                return 3;
            }
        case '>':
            i++;
            if (test[i] == '=')
            {
                fout <<  ">=\t" <<21 <<" PT" << endl;
                return 3;
            }
            else
            {
                i--;
                fout << ">\t" << 20 <<" PT" << endl;
                return 3;
            }
        case '+': fout << "+\t" <<  22<<" PT" <<endl; return 3;
        case '-': fout << "-\t" <<  23 <<" PT" << endl; return 3;
        case '*': fout << "*\t" <<  24 <<" PT" << endl; return 3;
        case '/': 
            i++;
            if(test[i]!='/'){
                i--;
                fout << "/\t" <<  25 <<" PT" << endl; return 3;
            }

            else{

                while(1){
                    if(test[i++]=='\n')
                        return -1;
                }
                fout << "//\t" <<  25 <<" PT" << endl;;return 3;

            }

        case ':': fout << ":\t" <<  26<< " PT" <<endl;return 3;
        case ';': fout << ";\t" <<  27 <<" PT" << endl;return 3;
        case '(': fout << "(\t" <<  28 <<" PT" << endl;return 3;
        case ')': fout << ")\t" <<  29 <<" PT" << endl; return 3;
        case '{': fout << "{\t" <<  30 <<" PT" << endl; return 3;
        case '}': fout << "}\t" <<  31 <<" PT" << endl; return 3;
        case '[': fout << "[\t" <<  32 <<" PT" << endl; return 3;
        case ']': fout << "]\t" <<  33 <<" PT" << endl; return 3;
        case '|': fout << "|\t" <<  34 <<" PT" << endl;return 3;
        case '"': fout << "\"\t" << 35 <<" PT" << endl; return 3;
        case ',': fout << ",\t" <<  36 <<" PT" << endl; return 3;
        case '\'': fout << "\\\t" <<  37 <<" PT" << endl; return 3;//单引号
        case '&': 
            i++;
            if(test[i]!='&'){
                i--;
                fout << "&\t" <<  38 <<" PT" << endl;return 3;
            }   
            else{   
                fout << "&\t" <<  39 <<" PT" << endl;return 3;

            }
        case '\\': fout << "\\\\\t" <<  40 <<" PT" <<endl; return 3;
    }
    return 3;
}

int main()
{
    int c = 0;
    int m;
    i = 0;
    FILE *fp;
    fp=fopen("demo.c","r");
    ofstream fout1;
    fout1.open("token.txt");
   
    while (!feof(fp))
    {
        test[c++] = fgetc(fp);
    }
    test[c] = '#';
    do
    {
        m = alysis(fout1);

        switch (m)
        {
        case -1:i++; break;
        case 0: i++; break;
        case 3: i++; break;
        }
    } while (m != 0);


    return 0;
}
