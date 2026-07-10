#include <stdio.h> 
void print_multiplication_table(int n);
int main() 

{ 
    for (int num = 1; num <= 
          10; num++)

  { print_multiplication_table(num); 
    printf("\n");
    // Add a newline after each multiplication table 
    } 
  return 0; } 




void print_multiplication_table(int n)
{ printf("Multiplication table for %d -\n", n);
  for (int i = 1; i <= 10; i++) 
  { printf("%d x %d = %d\n", n, i, n * i); } }
