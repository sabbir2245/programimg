#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int * array;
    // Add more fields here
    int size, capacity,position ; 
    
} ArrayList;


void init_arraylist(ArrayList *list, int intcapacity)
{
    printf("implement init_arraylist\n");
    // dynamically allocate space for the array
    // initialize the size, capacity, and current position
    list->array = (int*)malloc(sizeof(int) * intcapacity) ; 
    list->size = 0 ;
    list->position= 0 ; 
    list->capacity = intcapacity ;

    

}


void clear(ArrayList *list)
{
    printf("Implement clear\n");
    // clear the list but do not free the array
    // modify the size, capacity, and current position
    list->array = NULL ;
    list->size = 0 ;
    list->capacity = 0 ;
    list->position = 0 ;
   
    list->position = 0 ;

}

int get_size(ArrayList *list)
{
    return list->size ; 
}


void resize(ArrayList *list, int new_capacity)
{
   // printf("Implement resize\n");
    // allocate space for new array with new_capacity
    // print log message
    list->array =(int*)realloc(list->array,new_capacity*sizeof(int)) ;
    list->capacity=new_capacity ; 

}


void append(ArrayList *list, int value)
{
   // printf("Implement append\n");
    // call resize if necessary
    // add value to the end of the list
    if(list->size==list->capacity){
        resize(list,list->capacity*2);
    }
    list->array[list->size]=value ;
    list->size++ ; 

  

}


void insert(ArrayList *list, int value)
{
    printf("Implement insert\n");
    // call resize if necessary
    // shift the elements to the right to make space
    // add value at the current position
     if(list->size==list->capacity){
        resize(list,list->capacity*2);
    }
    for(int i = list->size ; i > list->position ;i-- ){
        list->array[i] = list->array[i-1] ;

    }
    list->array[list->position] = value ; 
    list->size++ ; 

}

// need to finish this 

int remove_at_current(ArrayList *list)
{
    printf("Implement remove_at_current\n");
    if(list->size == 0 )  return -1;
    // save the value of the current element in a variable
    // shift the elements to the left to fill the gap
    // change the size, and current position as necessary
    // call resize if necessary
    // return the saved value
    int savedval = list->array[list->position] ;
    
    for(int i = list->position ; i < list->size ; i++){
        list->array[i] = list->array[i+1] ;

    }
    list->size-- ;
    if(list->size < list->capacity/4) resize(list,list->capacity/2);
    return savedval ;
  

}

int find(ArrayList *list, int value)
{
    printf("Implement find\n");
   
    // traverse the list and return the position of the value
    // return -1 if the value is not found
    for(int i = 0 ; i<list->size ;i++){
        if(list->array[i]==value){
            return i ; 
            break ; 
        }
    }
    return -1 ; 
}


void move_to_start(ArrayList *list)
{
    printf("Implement move_to_start\n");
    // consider the cases when the list is empty
    list->position = 0 ; 
}


void move_to_end(ArrayList *list)
{
    printf("Implement move_to_end\n");
    // consider the cases when the list is empty
    list->position = list->size -1 ;
}


void prev(ArrayList *list)
{
    printf("Implement prev\n");
    // no change if the current position is at the start
    if(list->position == 0 ){
        return ; 
    }
    else{
        list->position--;
    }
}


void next(ArrayList *list)
{
    printf("Implement next\n");
    // no change if the current position is at the end
     if(list->position == list->size -1 ){
        return ; 
    }
    else{
        list->position++;
    }
}


void move_to_position(ArrayList *list, int nposition)
{
    printf("Implement move_to_position\n");
    list->position = nposition ; 
    
}


int get_current_position(ArrayList *list)
{
    printf("Implement get_current_position\n");
    return list->position;
    return -1;
}


int get_value(ArrayList *list)
{
    printf("Implement get_current_element\n");
    return list->array[list->position] ;
    return -1;
}


void print_list(ArrayList *list)
{
    printf("< ");
   
    for (int i = 0; i < list->size; i++)
    {   
         if(i == list->position){
            printf("|") ; 
        }
        printf("%d  ", list->array[i]); 
       
        
    }
    printf(" >");
    printf("\n");
    
}


void free_list(ArrayList *list)
{
    printf("Implement free_list\n");
    // free the array before terminating the program
    free(list->array);
}

