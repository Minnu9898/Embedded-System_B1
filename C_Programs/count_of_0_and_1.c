#include<stdio.h>

void count_of_binary(int x)
{
     int mask=0;
    int sum_1=0,sum_0=0;
    for (int i=31;i>=0;i--)
    {
    //to remain the number same do AND with 1
        mask=1<<i;
        if(x & mask)
        {
            sum_1++;
        }
        else
        {
            sum_0++;
        }
    }
    printf("\nCount of 1= %d",sum_1);
    printf("\nCount of 0= %d",sum_0);
}




int main()
{

    int num;
    printf("Enter a number : \n");
    scanf("%d",&num);
    count_of_binary(num);

}
