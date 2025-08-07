
# include <stdio.h>
# include <conio.h>
# include <math.h>



int sum(int c,int d)
{
    int add=0;
    add=c+d;
    return add;
}

int sub(int c,int d)
{
    int subtract=0;
    subtract=c-d;
    return subtract;
}

int mul(int c,int d)
{
    int multiplication=0;
    multiplication=c*d;
    return multiplication;
}

int division(float c,float d)
{
    float divi=0;
    divi=c/d;
    return divi;
}

int main()
{
 
printf("A program");
int a,b;
/*
printf("Enter value for A \n");
scanf("%d",&a);
printf("Enter value for B \n");
scanf("%d",&b);
*/
printf("Enter value for A  and B");
scanf("%d" "%d",&a, &b);

int add_result=0;
int sub_result=0;
int mul_result=0;
float div_result=0;

add_result=sum(a,b);

sub_result=sub(a,b);

mul_result=mul(a,b);

div_result=division(a,b);

printf("Addition Result =%d \n",add_result);
printf("Subtraction Result =%d \n",sub_result);
printf("Multiplication Result =%d \n",mul_result);
printf("Division Result =%f \n",div_result);
return 0;
}