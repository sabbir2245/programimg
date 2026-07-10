#include <iostream>
using namespace std;

class Queue
{
private:
    int *array;
    //write your code here. Add additional private variables if necessary
    int front , rear , size , capacity ; 

public:
    // Constructor
    Queue()
    {
        array = new int[1];
        front = rear =size =0 ;  
        capacity = 1 ; 
        //write your code here. Initialize additional private variables if necessary
    }
    Queue(int initialCapacity)
    {
        array = new int[initialCapacity]; // Allocate initial memory
        //write your code here. Initialize additional private variables if necessary
         front = rear =size =0 ;  
        capacity = initialCapacity ; 

    }

    // Destructor
    ~Queue()
    {
        delete[] array; // Free dynamically allocated memory
         front = rear =size =0 ;  
    }

    // Helper function to resize the array when full
    void resize(int newCapacity)
    {
        int *newArray = new int[newCapacity]; // Allocate new array

        //write your code here. Copy the elements from the old array to the new array
        for(int i = 0 ; i< size ;i++){
            newArray[i] = array[i] ; 

        }
        

        delete[] array; // Free old memory
        array = newArray ; 
        capacity = newCapacity ; 
        front = 0;
     rear = size - 1;
        //write your code here. Update the capacity and array pointers
    }

    // Enqueue an element onto the queue
    void enqueue(int x)
    {
        //write your code here. Check if the array is full and resize if necessary.

        if(size == capacity){
            resize(2*capacity);
        }
        if(!isEmpty()){
             rear =(rear +1 ) % capacity ;
        }else{
            front = 0 ; 
            rear = 0 ; 
        }
        array[rear] = x ; 
       
        size++ ; 
       // cout<< "successfully enqued" <<endl;

    }

    // Remove and return the peek element
    int dequeue()
    {
       //write your code here. Check if the stack is empty and return -1 if it is.
       //remove the peek element and return it
       //resize the array if necessary
       if(isEmpty()) {return -1 ;} 
       int temp = array[front] ; 
       front = (front+1 ) % capacity  ; 
       size-- ;
    if (size > 0 && size <= capacity / 4) {
     resize(capacity / 2);}
    
       return temp ; 
    }

    // Return the peek element without removing it
    int peek()
    {
        //write your code here. Check if the queue is empty and return -1 if it is.
        //return the peek element
       if(isEmpty()) {return -1 ;} 
        
        return array[front] ; 

    }

    // Return the number of elements in the queue
    int length()
    {
        //write your code here. Return the number of elements in the queue
        return size ; 
    }

    // Check if the queue is empty
    bool isEmpty()
    {
        //write your code here. Return true if the queue is empty, false otherwise
        return size == 0 ; 
    }

    // Clear the queue
    void clear()
    {
        //write your code here. Clear the queue. resize the array to 1

        delete [] array ; 
        array = new int[1] ; 
         front = rear =size =0 ;  
        
    }
    void printque(){
        cout << "Queue: ";  // print the queue name
        if (isEmpty())
        {
            cout << "Empty\n";
            return;
        }

        for (int i = 0; i < size; i++)
        {
            cout << array[(front + i) % capacity] << " ";
        }
        cout << endl;
        
    }
};
