#include<stdio.h>

int main()
{
    int a=10;
    int b=20;
    int c=30;
    printf("%p \n",&a);
    printf("%p\n",&b);
    printf("%p\n",&c);
    
    int *ptr1=&a;
    int *ptr2=&b;
    int *ptr3=&c;

 printf("%p\n",ptr1); // will print same as &a
 printf("%p\n",ptr2);
 printf("%p\n",ptr3);


printf("%d\n",*ptr1);// will print 10
printf("%d\n",*ptr2);
printf("%d\n",*ptr3);

 printf("%p\n",&ptr1); // Address of pointer
 printf("%p\n",&ptr2);
 printf("%p\n",&ptr3);
 
 
  printf("%d\n",*&a);// to get value of a =10
return 0;

}
