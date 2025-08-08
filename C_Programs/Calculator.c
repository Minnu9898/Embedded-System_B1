
# include <stdio.h>

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

float division(float c,float d)
{
    float divi=0;
    divi=c/d;
    return divi;
}

int main()
{
    
int a,b,input;
int add_result=0;
int sub_result=0;
int mul_result=0;
float div_result=0;
printf("Enter value for A  and B \n");
scanf("%d" "%d",&a, &b);
/*
printf("Enter value for A \n");
scanf("%d",&a);
printf("Enter value for B \n");
scanf("%d",&b);
*/
printf("Enter the option : \n 1.Addition \n 2. Subtraction \n 3. Multiplication \n 4. Division \n");
scanf("%d",&input);
if (input==1)
{
   add_result=sum(a,b);
   printf("Addition Result =%d \n",add_result);
}
else if (input==2)
{
   sub_result=sub(a,b);
   printf("Subtraction Result =%d \n",sub_result);
}
else if (input==3)
{
   mul_result=mul(a,b);
   printf("Multiplication Result =%d \n",mul_result);
}
else if (input==4)
{
   div_result=division(a,b);
   printf("Division Result =%f \n",div_result);
}
else
{
    printf("Invalid input! Retry");
}

return 0;
}