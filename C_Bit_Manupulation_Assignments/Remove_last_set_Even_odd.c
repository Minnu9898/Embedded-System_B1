


// Q 4.) Remove the last set bit of a number.
// Q 5. ) Find whether a number is even or odd

#include<stdio.h>
void even_or_odd(int num)  // Find whether a number is even or odd
//only last bit need to be 1 0r zero to check odd or even , so no loop
{
   
    if(num&1)
    {
        printf("\nIts an ODD num");
    }
    else
    {
        printf("\nIts an Even num");
    }

}


int main()
{
    int num,temp;
    printf("\nEnter a number :\n ");
    scanf("%d", &num);
    /*LOGIC
    if num=10 then do AND operation with (n-1) 
    n  =1010
    n-1=1001
    __________ &
        1000    (goal was to set the 1010 to 1000 -last 1 will become zero)
    */
    temp=num;
    temp=temp&(temp-1);
    printf("\nNumber after Removing last set BIT = %d", temp);
    
    even_or_odd(num);  // Q 5.) Find whether a number is even or odd
   
}