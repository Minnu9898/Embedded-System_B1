


/*
. Write a function in C that takes an array of integers and its size, and returns the
second largest element.
Constraints:
● Do not sort the array.
● Assume the array has at least two distinct elements.

*/

#include <stdio.h>
#include <stdlib.h>

int largest_num (int a[],int n)
{
    int large=a[0];
    for(int i=0; i<n;i++)
    {
        if (a[i]>large)
        {
            large=a[i];
        }

    }
    return large;

}

int main()
{
    int a[50],n;
    printf("Enter the values of n: \n");
     scanf("%d",&n);

    printf("Enter the values : \n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }

    printf("Entered Array is: \n");
    for(int i=0;i<n;i++)
    {
       printf("%d \t",a[i]);
    }
    
    int Result= largest_num(a,n);
    printf("Result is : %d",Result);



}