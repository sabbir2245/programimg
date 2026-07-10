#include<iostream>

class Node{
public:
    int data;
    Node* next;
    Node* prev ; 
    Node(int data){
        this->data = data;
        this->next = nullptr;
    }
};

class DoublyLinkedList{
    Node* head;
    Node* tail;
    int size;
    
public:
    DoublyLinkedList(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

void addnode(int val){
    Node* newNode = new Node(val);
    if(head==nullptr){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->next=nullptr;
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;

    }
}
void addtobeg(int val){
    Node* newNode = new  Node(val) ;
    newNode->next = head ; 
    newNode->prev = nullptr ; 
    if (head != nullptr) {
        head->prev = newNode;
    } else {
        // If the list was empty, set the tail to the new node
        tail = newNode;
    }
    head = newNode ; 
    
     
}

void print(){
    Node* current = head;
    while(current!=nullptr){
        std::cout<<current->data<<" ";
        current = current->next;
    }
    std::cout<<std::endl;
}

};
int main(){
    DoublyLinkedList dll;
    dll.addnode(1);
    dll.addnode(2);
    dll.addnode(36);
    dll.addtobeg(67) ;
    dll.addtobeg(33) ;

    dll.print();
    return 0;

}