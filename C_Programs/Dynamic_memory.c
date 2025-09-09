#include<stdio.h>

int main()
{
// int a=10;
// int b=20.0;
// void *ptr=&a; // generic purpose pointer
// printf("Value of a =%d\n",*(int *)ptr);
// *(int *)ptr=30;
// printf("Modified value of a =%d",*(int *)ptr);

float arr[5]={1.0,2.0,3.0,4.0};
void *ptr=&arr;
for(int i=0;i<5;i++)
{
    printf("%f \t", *(float *)(ptr +i));

}
return 0;

}


