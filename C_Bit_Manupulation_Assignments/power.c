
// Q 6.) Check if the number is a power of 2?
// Q 7.) Check if a number is a power of 4?
// Q 8.) Check if a number is a power of 8?
// Q 9.) Check if a number is a power of 16?


#include<stdio.h>
void power_of_two(int num)  // Q 6.) Check if the number is a power of 2?
{
    // A number is power of 2 if it has only one bit set to 1
    /* 2^0=1(0001) ,2^1=2 (0010),2^3=8(1000) 
    6=0110 -has two 1 - so not a power of 2
    */
   if (num>0 && (num&(num-1))==0)
   {
    printf("\nNumber is Power of 2");
   }
   else
   {
    printf("\nNumber is NOT a Power of 2");
   }

}
void power_of_four(int num) // Q 7.) Check if a number is a power of 4?
{ 
    /* Conditions
    1. It should be power of 2 (only 1 bit is set) 
    2. Its bit will be set only in even position
    */
   if (num>0 &&(num&(num-1))==0 && num%3==1) //5 or 3 any odd number
   {
    printf("\nNumber is  Power of 4");
   }
   else
   {
    printf("\nNumber is  NOT a Power of 4");
   }

}

void power_of_eight(int num) // Q 7.) Check if a number is a power of 8?
{
    /* Conditions
        1. Should be Power of 2
        2. Set bit position will be in a position which are multiple of 3 (0,3,6,9)

    */
   if (num>0 && (num&(num-1))==0 && num%3==0)
   {
    printf("\nNumber is  Power of 8");
   }
   else
   {
    printf("\nNumber is  NOT a Power of 8");
   }

}

int main()
{
    int num,temp;
    printf("\nEnter a number :\n ");
    scanf("%d", &num);

    power_of_two(num); // Q 6.) Check if the number is a power of 2?
    power_of_four(num); // Q 6.) Check if the number is a power of 4?
    power_of_eight(num); // Q 8.) Check if a number is a power of 8?
}