#include<stdio.h>
#include<conio.h>
int main()
{
	//Square matrix multiplication.
	int size;
	
	
	printf("Enter the size of the square matrix:\n");
	scanf("%d",&size);
	
	int a[size][size],b[size][size],c[size][size];
	
	printf("Enter the elements of the first array:\n");
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			scanf("%d",&a[i][j]);
	
	printf("Enter the elements of the second array:\n");
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			scanf("%d",&b[i][j]);
	
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		{
			c[i][j]=0;
			for(int k=0;k<size;k++)
				c[i][j]=c[i][j] + a[i][k] * b[k][j];
		}
		
		printf("The result of the matrix multiplication is:\n");
		
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
			printf("%d ",c[i][j]);
            
			printf("\n");	
	}
}
