

/*
2. You are given an 8-bit register represented as an unsigned char. Write a function to:
● Set the 3rd bit (bit index 2).
● Clear the 6th bit (bit index 5).
● Toggle the 1st bit (bit index 0). Return the modified register value.
Note: Use bitwise operators only. Avoid loops or conditionals.


*/

#include <stdio.h>
#include <stdlib.h>
void PrintBinary(int num)
{
    int mask=0;
    for(int i=31;i>=0;i--)
    {
       mask=1<<i;
       if (num&mask)
       {
        printf("1");
       }
       else
       {
        printf("0");
       }
    }
}

void set(int num,int P3) // Set to 1
{
    int mask=0;
    
       mask=1<<P3;
       num=(num|mask);
       PrintBinary(num);
       
    
}

void clear(int num,int P6) //Clear to 0
{
    int mask=0;
    
       mask=1<<P6;
       mask=~mask;
       num=(num&mask);
       PrintBinary(num);
       
    
}

void Toggle(int num,int P1) //Toggle to 0 to 1 and viceversa
{
    int mask=0;
    
       mask=1<<P1;
       num=num^mask;
       PrintBinary(num);
       
    
}



int main()
{
    int num,P1,P6,P3;
    printf("Enter a number: \n");
    scanf("%d",&num);
    printf("Enter the Bit to Set: \n");
    scanf("%d",&P3);
    printf("Enter the Bit to clear: \n");
    scanf("%d",&P6);
    printf("Enter the Bit to toggle: \n");
    scanf("%d",&P1);

    PrintBinary(num);
    set(num,P3);
    clear(num,P6);
    Toggle(num,P1);


}