#include <stdio.h>

/*
write a c program using pointer, to print the address and value of each element inside an array.
*/
int main()
{
    int arr[10];
    int *ptr=&arr[0];
    printf("Enter the values : \n");
    for(int i=0;i<10;i++)
    {
        scanf("%d",&arr[i]);
    }
    for(int i=0;i<10;i++)
    {
       printf("%d \t",arr[i]);
    }
    
    //print value and address of index
    
    for(int i=0;i<10;i++)
    {
        printf("\nAddress of Element arr[%d] is %p \t",i,(ptr+i));
        printf("\nValue at index %d is %d \t",i,*(ptr+i));
        
    }
     return 0;
}