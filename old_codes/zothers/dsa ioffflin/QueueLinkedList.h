#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }

    Node(int value, Node *nextNode)
    {
        data = value;
        next = nextNode;
    }
};

class Queue
{
private:
    Node *peekNode; // Points to the front of the queue
    int currentSize;

public:
    // Constructor
    Queue()
    {
        peekNode = nullptr;
        currentSize = 0;
    }

    // Enqueue an element onto the queueu
    void enqueue(int x)
    {
       // write your code here. Create a new node with the value x and enqueue it onto the queue
       // update the peekNode and currentSize
       Node *t = new Node(x ) ; 
       if(isEmpty()){
        peekNode = t;
        return ; 
       }
       Node* curr = peekNode ; 
       while (curr->next)
       { curr = curr->next ; 
        /* code */
       }
       curr->next = t ;
       currentSize++ ;

       
    }

    // Remove and return the peek element
    int dequeue()
    {
        // write your code here. Check if the queueu is empty and return -1 if it is.
        // dequeue the peek element and return it
        // update the peekNode and currentSize
        // delete the node that was dequeued
        if(isEmpty()){return -1 ; }
        Node *temp = peekNode ; 
        int trmp = peekNode->data ; 
        peekNode = peekNode->next ; 
        delete temp ; 
        currentSize--;
        return trmp ; 
    }

    // Return the peek element without removing it
    int peek()
    {
        // write your code here. Check if the queueu is empty and return -1 if it is.
        // return the peek element
        if(isEmpty()){return -1 ; }

        return peekNode->data ; 
    }

    // Return the number of elements in the queueu
    int length()
    {
        // write your code here. Return the number of elements in the queueu
        return currentSize ; 
        
    }

    // Check if the queueu is empty
    bool isEmpty()
    {
        // write your code here. Return true if the queueu is empty, false otherwise
        return peekNode == nullptr ; 
    }

    // Clear the queueu
    void clear()
    {
        while (!isEmpty())
        {
            dequeue(); // Continuously dequeue elements until the queueu is empty
        }
    }

    // Destructor
    ~Queue()
    {
        clear();
    }
    // void printjj(){
    //     // case when empty
    //     if(isEmpty()){
    //         cout << "Queue is empty" << endl ;
    //         return ;
    //     }
        
    //     cout << endl ;
    //     Node *temp = peekNode ; 
    //     while(temp!=nullptr){
    //         cout << temp->data << " " ;
    //         temp = temp->next ;
    //     }
    //     cout << endl ;
    // }
};
