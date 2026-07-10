#include "linkedlist.h"

#include <stdio.h>

int main()

{
    int capacity;
    int size;
    LinkedList list ;
    size = 5 ; 
    
    init_linkedlist(&list);

  int testValues[] = {10, 20, 30, 40, 50};

    printf("enter the numbers\n") ;
    for(int i = 0 ;i<size ;i++){
        // int z ; 
        // scanf("%d",&z) ;
      //  append(&list, z);
       append(&list, testValues[i]);
    } 
append(&list,78) ;


move_to_position(&list,4);
prev(&list);





    printf("printing the list\n");
    print_list(&list);

   
   

  move_to_start(&list);
remove_at_current(&list);
remove_at_current(&list);
remove_at_current(&list);
remove_at_current(&list);

 


    
    print_list(&list);


    printf("\n");











}