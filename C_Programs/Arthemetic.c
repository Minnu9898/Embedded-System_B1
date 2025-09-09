
# include <stdio.h>

float sum(float c,float d)
{
    float add=0;
    add=c+d;
    return add;
}

float sub(float c,float d)
{
    float subtract=0;
    subtract=c-d;
    return subtract;
}

float mul(float c,float d)
{
    float multiplication=0;
    multiplication=c*d;
    return multiplication;
}

float division(float c,float d)
{
    if (d==0)
    {
        printf("Division not possible \n ");
        return 0;
    }
    else
    {
    float divi=0;
    divi=c/d;
    return divi;
    }
}

int main()
{
    
int input;
float a,b;
float add_result=0;
float sub_result=0;
float mul_result=0;
float div_result=0;
printf("Enter value for A  and B \n");
scanf("%f" "%f",&a, &b);
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
   printf("Addition Result =%f \n",add_result);
}
else if (input==2)
{
   sub_result=sub(a,b);
   printf("Subtraction Result =%f \n",sub_result);
}
else if (input==3)
{
   mul_result=mul(a,b);
   printf("Multiplication Result =%f \n",mul_result);
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