#include <stdio.h>
#include<stdbool.h>

int prime( int n ){
  if(n<2){return false ;}
  for (int i = 2; i*i<=n ; i++)
  {
    if (n%i == 0 ){return false ;}
  }
  return true ;
}

int main (){
  printf("input your number ");
  int n ;
  scanf("%d",&n);

  if (prime(n))
  {
     printf(" Prime number");
  }
  else 
  {
    printf(" Not a Prime number");
  }
  
}