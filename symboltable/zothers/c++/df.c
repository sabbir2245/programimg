#include <stdio.h>
#include<string.h>

int main()
{ 
    char str[20];
    
    while (1 )
{  
    scanf("%s",str);
    

    if ( strcmp(str,"quit") ==0)
    {
        break;
    }
    printf("%s\n",str);

}

printf("done");

return 0 ;
}