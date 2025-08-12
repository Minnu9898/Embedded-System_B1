# include <stdio.h>

int main()
{
    int even[10];
    int j=2;
    
    for (int i=0; i<=9; i++)
    {
        even[i]=j;
        printf("value of mark[%d] = %d \n",  i, j);
        j=j+2;
    }
    return 0;
}