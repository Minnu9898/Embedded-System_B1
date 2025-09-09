   
   
   //Q 10.) Toggle ith Bit of a number?
  //Q 11.) Count the number of set bits in a number
#include<stdio.h>
void printBin (int n)
{
    int mask=0;
// to find which is the value in BIT , we can do AND if its 1 it will retutn 1 if we do and with 1
    for (int i=31; i>=0;i--) //32 bit 
    {
     mask=1<<i;
     if(n&mask)
     {
        printf("1");
     }
     else
     {
         printf("0");
     }

    }
}
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

void toggle(int x, int i)
{
    printBin(x);
    int mask=1<<i;
    x= x ^ mask;   //  (8= 1000) ------> i=3  value at i =1  1000 XOR 1000 = 0000   now value at i became 0
    
    printf ("\nToggled number is %d",x);
    printBin(x);


    
}


int main()
{

    int num,p;
    printf("Enter a number : \n");
    scanf("%d",&num);
    count_of_binary(num);

    //Toggle ith Bit of a number?
    printf("\nEnter the position to be toggled");
    scanf("%d", &p);
    toggle(num,p);
}
