#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    int *ptr;
    printf("Enter the count \t");
    scanf("%d",&n);
    //Allocate memory
    ptr= (int *) malloc(n*sizeof(int)); // 40 bytes needed to save 10 integers
    //check success or not
    if(ptr==NULL)
    {
        printf("Memory allocation is failed");
        return 1; 
    }
    for (int i=0;i<n;i++)
    {
        printf("Enter the element  %d \t",i+1);
        scanf("%d", (ptr+i));
    }
     printf("You Entered : \t");
     for (int i=0;i<n;i++)
    {
       
        printf("%d \t", *(ptr+i));
    }
    free(ptr);
}

