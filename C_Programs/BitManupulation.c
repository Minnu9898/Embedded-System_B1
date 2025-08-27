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

void setBit(int n, int pos)
{
    //set pos value to 1 or 0 
    int mask =0;
    
    mask=1<<pos;
    n=(n|mask);
    printBin(n);
          
}


void ClearBit(int n, int p)
{
    //Clear bit by & and ~
    int mask =0;
    mask=1<<p;
    mask= ~mask;
    n=(n&mask);
    printBin(n);
           
}
int main()
{
    int n,pos,p;
    printf("\n\n\n Enter a number :  " );
    scanf("%d",&n);
    printBin(n);
    printf("\n Enter the position to be set: ");
    scanf("%d", &pos);
   
    setBit(n,pos);
     printf("\n Enter the position to be cleared: ");
    scanf("%d", &p);
    ClearBit(n,p);
}