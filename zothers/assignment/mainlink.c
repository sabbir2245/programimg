
 #include "linkedlist.h"
#include <stdio.h>


int main()
{
    FILE *file = fopen("in.txt", "r");
    if (file == NULL)
    {
        
        return 1;
    }
    
    int capacity;
    int size;
    fscanf(file, "%d %d", &size, &capacity);

    LinkedList list;
  

   init_linkedlist(&list);
    int i;
    for (i=0; i<size; i++)
    {
        int value;
        fscanf(file, "%d", &value);
        append(&list, value);
    }
    print_list(&list);
    
    int func, param;
    while (fscanf(file, "%d %d", &func, &param) == 2 && func != 0)
    {
        if (func == 1)
        {
            insert(&list, param);
            printf("inserted %d\n", param);
        }
        else if (func == 2)
        {
            int value = remove_at_current(&list);
        }
        else if (func == 3)
        {
            int ret = find(&list, param);
            if(ret ==-1){
                printf("did not find %d in the list\n", param);
            }else {
            printf("found %d at position %d\n", param, ret);}
        }
        else if (func == 4)
        {
            move_to_start(&list);
            printf("moved current postion to 0\n");
        }
        else if (func == 5)
        {
            move_to_end(&list);
            printf("moved current postion to %d\n", list.size - 1);
        }
        else if (func == 6)
        {
            prev(&list);
        }
        else if (func == 7)
        {
            next(&list);
        }
        else if (func == 8)
        {
            int pos = get_current_position(&list);
            printf("current position is %d \n", pos);
        }
        else if (func == 9)
        { int t = list.pos ;
            move_to_position(&list, param);     
            printf("moved current position from %d to %d \n",t ,param);       
        }
        else if (func == 10)
        {
            int len = get_size(&list);
            printf("size  is %d\n ", len);
        }
        else if (func == 11)
        {
            int value = get_value(&list);
            printf("current element is %d \n", value);
        }
        else if (func == 12)
        {
            append(&list, param);
            
            printf("appended %d\n", param);
        }
        else if (func == 13)
        {
            clear(&list);
            printf("cleared list\n");
        }
        else if (func == 0)
        {
            exit(0);
        }
        else
        {
            printf("Invalid function\n");            
        }
        print_list(&list);
    }
    printf("Program ended\n");
    free_list(&list);
    fclose(file);
    return 0;
}