
# include <stdio.h>
//Function of sum
int summation(int arr[],int x)
    {
        int sum=0;
        for (int i=0;i<x;i++)
        {
            sum+=arr[i];
            
        }
        return sum;
    }

    int oddnum(int arr[],int x)
    {   
        int odd[20];
        int j=0;
        for (int i=0; i<x;i++)
        {   
            if(arr[i]%2!=0)
            {
                odd[j]=arr[i];
                j++;
            }
            
        }
    for (int i=0; i<j; i++)
    {
        
        printf("%d" "\t", odd[i]) ;
    }
    }
int main()
{
	int n,sum=0,odd_num;
	int arr[50];
    int sum_result=0;
	printf("Enter the value of N \n");
	scanf("%d",&n);
	printf("Enter %d numbers to array \n ",n);
	for (int i=0; i<n; i++)
	{
		scanf("%d",&arr[i]);
		
	}
	printf("Then Entered array is \n");
    for (int i=0; i<n; i++)
    {
        
        printf("%d" "\t", arr[i]) ;
    }
    //function call to find sum of elements of an array 
    sum_result =summation(arr,n);
    printf("\n\nSum of the Elements of the Array is %d \n\n",sum_result);
    
    oddnum(arr,n);

}
