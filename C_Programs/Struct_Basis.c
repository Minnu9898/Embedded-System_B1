// # include <stdio.h>

// struct Employee{
//     char name[32];
//     int id;
//     float salary;
// };

// int main()
// {
// struct Employee e={"Minnu Prakash",8577,50000.00};
// struct Employee p={"\nAnakha ",1000,1000.20};
// struct Employee b={"\nAnakha ",1000,1000.20};
// printf("Name: %s \n ID: %d\n Salary:%2f",e.name,e.id,e.salary);
// printf("Name: %s \n ID: %d\n Salary:%2f",p.name,p.id,p.salary);	
// printf("Name: %s \n ID: %d\n Salary:%2f",b.name,b.id,b.salary);	
// }

// struct Employee{
//     char name[32];
//     int id;
//     float salary;
// };

// int main()
// {   struct Employee e;
//     printf("Enter your name \n");
//     scanf("%s" ,e.name);
//     printf("Enter your ID \n");
//     scanf("%d" ,&e.id);
//     printf("Enter your Salary \n");
//     scanf("%f" ,&e.salary);

// printf("Name: %s \n ID: %d\n Salary:%2f",e.name,e.id,e.salary);	
// return 0;
// }


// # include <stdio.h>

// struct Employee{
//     char name[32];
//     int id;
//     float salary;
// };

// int main()
// {   
//     int ch;
//     struct Employee e[5];
//     for (int i=0;i<5;i++)
//     {
//         printf("Enter your name %d\n",i+1);
//     scanf("%s" ,e[i].name);
//     printf("Enter your ID %d\n",i+1);
//     scanf("%d" ,&e[i].id);
//     printf("Enter your Salary %d\n",i+1);
//     scanf("%f" ,&e[i].salary);
//     }
   
//     while(ch=getchar()!='\n' && ch!=EOF)
//     {
        
//     }
//     for (int i=0;i<5;i++)
//     {
//         printf("Name %d: %s \n ID %d: %d\n Salary %d:%2f",i+1,e[i].name,i+1,e[i].id,i+1,e[i].salary);	
//     }
//     return 0;
// }



# include <stdio.h>


struct Employee
{
    char name[32];
    int id;
    float salary;
};

int increment(struct Employee e,float percentage)
{
   e.salary= e.salary+((e.salary*percentage/100));
   printf("\nNew salary =%f",e.salary);
}

int main()
{   
    int ch;
    struct Employee e={"minnu",100,10000.00};
    printf("\nOld salary =%f",e.salary);
    increment(e,10.0);
    
    //printtf("Name: %s \n,ID: %d \n, Salary:%f ",e.name,e.id,e.salary);
}
