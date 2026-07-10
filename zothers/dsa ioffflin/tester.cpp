#include "StackUsingQueue.h"
#include <iostream>

using namespace std;

int main()
{
  Stack p ; 

  p.push(5) ; 
  p.push(10) ;
  p.push(15) ;
  p.push(20) ;
  p.push(25) ;
  p.push(30) ;
  p.pop() ; 
  p.pop() ; 

  p.printStack() ; 

cout << " top value is " << p.top() << endl;



  p.printStack() ; 

  cout<< "number of elements in stack is "<< p.length()<< endl ; 

}