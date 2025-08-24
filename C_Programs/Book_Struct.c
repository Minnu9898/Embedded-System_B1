#include<stdio.h>

struct book
{
    char title[50];
    char author[30];
    float price;
};

float expensive(float p[], int n)
{   
    float max=p[0];
    for (int i =0;i<n;i++)
    {
        if (p[i]>max)
        {
            max=p[i];
        }
        
    }
    printf("\nMost Expensive Book cost = %2f", max);
    return(max);

}

int main()
{
    int n,ch;
    struct book b[50];
    printf("Enter the number of books \n");
    scanf("%d",&n);

    for (int i=0;i<n;i++)
    {
        printf("Enter the Title of book %d\n",i+1);
        scanf("%s",b[i].title);
        printf("Enter the Author of book %d\n",i+1);
        scanf("%s",b[i].author);
        printf("Enter the Price of book %d\n",i+1);
        scanf("%f",&b[i].price);

    }
        while(ch=getchar()!='\n' && ch!=EOF)

    {
        
    }
   
    for (int i=0;i<n;i++)
    {   
        printf("Title %d: %s \nAuthor %d: %s \n Price %d: %2f",i+1,b[i].title,i+1,b[i].author,i+1,b[i].price);
    }
    //Add these prices to an array and find the highest number 
    
     float p[50];
     float cost;
    for (int i=0;i<n;i++)
    {
        p[i]=b[i].price;
    }
    cost=expensive(p,n); //function call to find highest number from array P which is the expensive book
    printf("\nCost of Book =%2f",cost);

    for(int i=0;i<n;i++)
    {
        if(b[i].price ==cost)
        {
            printf("\n \nTitle : %s \nAuthor: %s \n Price : %2f",b[i].title,b[i].author,b[i].price);
        }
    }

//optimised code  for learning purpose
        // int indexMostExpensive = 0;
        // for (i = 1; i < 3; i++) {
        // if (books[i].price > books[indexMostExpensive].price) {
        //     indexMostExpensive = i;
        // }
        // Print details of the most expensive book
    // printf("\nMost Expensive Book:\n");
    // printf("Title: %s\n", books[indexMostExpensive].title);
    // printf("Author: %s\n", books[indexMostExpensive].author);
    // printf("Price: %.2f\n", books[indexMostExpensive].price);

   // }

}
