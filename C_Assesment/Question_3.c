
/*
Write a C program to print a pyramid of stars for a given number n.
If n = 5, the output should be:
*
***
*****
*******
*********

*/
/*
n=1- *=1 -space=0
n=2  * =2 space=1
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter the values of n: \n");
    scanf("%d",&n);
     for (int i=1; i<=n; i++)
     {
        for (int k=1;k<n-i; k++)
        {
            printf(" ");
        }
        for (int j=1;j<(2*i-1); j++)
        {
            printf("*");
        }
         

        
        printf("\n");
     }


}