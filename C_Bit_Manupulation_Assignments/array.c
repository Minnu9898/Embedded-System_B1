


#include<stdio.h>

int main()
{

    int arr[]= {1,2,9,7,4,1,2,4};
    for (int i=0;i<7;i++)
    {
        printf(" %d",arr[i]);
    }
    for (int i=0;i<7;i++)
    {   
        int n=arr[i];
        int x=arr[i+1];

        for (int j=31;j>0;j--)
        {
           if(n^x)
           {
                break;
           }
           else
           {
            printf("%d \t",arr[i]);
           }
        }
       


    }

}
