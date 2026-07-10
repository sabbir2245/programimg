#include <stdio.h>
#include <string.h>

int main()
{
    char str[20] = "thE caT is cute af";

    int n = strlen(str);
char coll[10][10];

int nofwords=0 ; 
int index = 0 ; 

 for (int i = 0; i < n; i++) {
        if (str[i] == ' ') {
            coll[nofwords][index] = '\0';
            nofwords++;
            index=0 ;
        }
        else
        { 
            coll[nofwords][index]=str[i];
            index++;

        }
        
 }
 coll[nofwords][index] = '\0';
    nofwords++;
 for (int i = 0; i < nofwords; i++) {

printf("\n %s",coll[i]) ;

}

}