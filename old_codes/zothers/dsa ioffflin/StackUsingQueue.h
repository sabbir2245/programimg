#include <iostream>
#include "QueueLinkedList.h"
using namespace std;

class Stack
{
private:
    
    //write your code here. Add additional private variables if necessary
    Queue box ; 
    
    int size ; 
public:
    // Constructor
    Stack()
    {
        //write your code here. Initialize additional private variables if necessary
        size= 0 ;  

        
    }
    Stack(int initialCapacity)
    {
        //write your code here. Initialize additional private variables if necessary
        size = initialCapacity ; 
        
    }

    // Destructor
    ~Stack()
    { 
        box.clear() ; 
    }

    
    // Push an element onto the stack
    void push(int x)
    {
        //write your code here.
        //push the element onto the stack
        box.enqueue(x) ; 
        size++ ;

        
    }

    // Remove and return the top element
    int pop()
    {
       //write your code here. Check if the stack is empty and return -1 if it is.
       //pop the top element and return it
       if(box.isEmpty()){
        return -1 ; 
       }
       
       for (int i = 0; i < size -1; i++)
       {
            int t = box.dequeue() ; 
                box.enqueue(t) ; 
       }
       int temp = box.dequeue() ;
       size-- ;
       return temp ;


       
    }

    // Return the top element without removing it
    int top()
    {
        //write your code here. Check if the stack is empty and return -1 if it is.
        //return the top element
        if(box.isEmpty()){
        return -1 ; 
       }
        for (int i = 0; i < size -1; i++)
       {
            int t = box.dequeue() ; 
                box.enqueue(t) ; 
       }
       int temp = box.dequeue() ;
       box.enqueue(temp) ;  
      
       return temp ;
       
    }

    // Return the number of elements in the stack
    int length()
    {
        //write your code here. Return the number of elements in the stack
        return size ; 
        
    }

    // Check if the stack is empty
    bool isEmpty()
    {
        //write your code here. Return true if the stack is empty, false otherwise
        return box.isEmpty() ; 
    }

    // Clear the stack
    void clear()
    { 
        box.clear() ;
        //write your code here. Clear the stack.
        
    }
    // void printStack(){
    //     box.printjj();
    // }
};
