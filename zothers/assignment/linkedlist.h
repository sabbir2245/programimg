#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;

} Node;

typedef struct
{
    // add Node* head, tail, current_positionition and other necessary fields here
    Node *head;
    Node *tail;
    int position;
    int size;

} LinkedList;

void init_linkedlist(LinkedList *list)
{
    printf("implement init_linkedlist\n");
    // initialize head, tail with null

    list->head = NULL;
    list->tail = NULL;
    list->position = 0;
    list->size = 0;
}

void clear(LinkedList *list)
{
    printf("Implement clear\n");
    // traverse the list and free each node
    // set head and tail to null

    Node *temp = list->head;
    while (temp != NULL)
    {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->position = 0;
    list->size = 0;
}

int get_size(LinkedList *list)
{
    printf("Implement get_size\n");
    if (list->head == NULL)
    {
        return -1;
    }

    return list->size;
}

void append(LinkedList *list, int val)
{
    printf("Implement append\n");
    // create a new node and set its value
    // consider the case when the list is empty and when it isnt

    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->data = val;
    newnode->next = NULL;
    newnode->prev = NULL;

    if (list->head == NULL)
    {
        list->head = newnode;
        list->tail = newnode;
        list->position = 0;
        list->size = 1;
        return;
    }
    else
    {
        Node *curr = list->tail;
        curr->next = newnode;
        newnode->prev = curr;
        list->tail = newnode;
    }

    list->size++;
}

void insert(LinkedList *list, int value)
{
    printf("Implement insert\n");
    // create a new node and set its value
    // place it at the current positionition (check order of operations)
    // consider the case when the list is empty and when it isnt
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->data = value;
    newnode->next = NULL;
    newnode->prev = NULL;

    if (list->head == NULL)
    {
        list->head = newnode;
        list->tail = newnode;
        list->position = 0;
        list->size = 1;
        return;
    }
    if (list->position == 0)
    {
        newnode->next = list->head;
        list->head->prev = newnode;
        list->head = newnode;
        list->position = 0;
        list->size++;
        return;
    }

    Node *curr = list->head;
    for (int i = 0; i < list->position - 1; i++)
    {
        curr = curr->next;
    }

    newnode->next = curr->next;
    newnode->prev = curr;
    curr->next = newnode;
    list->size++;
}

int remove_at_current(LinkedList *list)

{
    printf("Implement remove_at_current\n");
    // consider the case when current code is at the begining or at the end
  
    Node *curr = list->head;
int c = 0 ; 
while( c < list->position){
    curr = curr->next ;
    c++;
}

if(curr == list->head ){
  list->head = curr->next ;
 list->head->prev = NULL ;
}
else{
    curr->prev->next = curr->next ;
    if(curr->next!= NULL)
    curr->next->prev = curr->prev ;
}

free(curr);

list->size--;
if(list->position == list->size){
    list->position-- ; 
}

return curr->data;



}
int find(LinkedList *list, int value)
{
    printf("Implement find\n");

    if (list->head == NULL)
    {
        return -1;
    }

    int cposition = 0;
    // traverse the list and return the positionition of the value
    Node *t = list->head;
    while (t != NULL)
    {
        if (t->data == value)
        {
            //  cposition = list->position ;
            return cposition;
        }
        t = t->next;
        cposition++;
        // list->position++ ;
    }

    return -1;
}

void move_to_start(LinkedList *list)
{
    printf("Implement move_to_start\n");
    list->position = 0;
}

void move_to_end(LinkedList *list)
{
    printf("Implement move_to_end\n");
    list->position = list->size - 1;
}

void prev(LinkedList *list)
{
    printf("Implement prev\n");
    // no change if the current positionition is at the start
    if (list->position == 0)
    {
        return;
    }
    else
    {
        list->position--;
    }
}

void next(LinkedList *list)
{
    printf("Implement next\n");
    // no change if the current positionition is at the end
    if (list->position == list->size - 1)
    {
        return;
    }
    else
    {
        list->position++;
    }
}

void move_to_position(LinkedList *list, int positionition)
{
    printf("Implement move_to_positionition\n");
    // traverse the list and stop at the given positionition
    list->position = positionition;
}

int get_current_position(LinkedList *list)
{
    printf("Implement get_current_positionition\n");
    // traverse the list and stop when you are at the current positionition
    // return the positionition (integer)
    return list->position;
}

int get_value(LinkedList *list)
{
    printf("Implement get_current_element\n");

    // return the value at the current positionition
    Node *t = list->head;
    for (int i = 0; i < list->position; i++)
    {
        t = t->next;
    }
    return t->data;
}

void print_list(LinkedList *list)
{

    int temp = list->position;
    printf("< ");
    Node *t = list->head;

    while (t != NULL)
    {
        if (temp == 0)
        {
            printf("|");
        }

        printf("%d  ", t->data);
        t = t->next;
        temp--;
    }
    printf(">\n ");
}
void free_list(LinkedList *list)
{
    printf("Implement free_list\n");
    // free each node in the list
}
