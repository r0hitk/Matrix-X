#include<stdio.h>
#include<stdlib.h>

int** matrixMultiply(int**,int**,int);
int** matrixAllocate(int);
int** matrixAdd(int**,int**,int);
void matrixFree(int**,int);

int main()
{
	int** a=matrixAllocate(4);
	int** b=matrixAllocate(4);
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			a[i][j]=i+j;
			b[i][j]=i+j;
		}
	}
	
	printf("The first matrix is:\n");	
	for(int i=0;i<4;i++)
	{
	
		for(int j=0;j<4;j++)
		{
			printf("%d ",a[i][j]);
		}
		
		printf("\n");
	}
	
	
	printf("\nThe second matrix is:\n");
	for(int i=0;i<4;i++)
	{
	
		for(int j=0;j<4;j++)
		{
			printf("%d ",b[i][j]);
		}
		
		printf("\n");
	}
	
	//matrixMultiply must return a pointer to pointer.
	int** c=matrixMultiply(a,b,4);
	
	printf("\nThe product is:\n");
	
	
	for(int i=0;i<4;i++)
	{
	
		for(int j=0;j<4;j++)
		{
			printf("%d ",c[i][j]);
		}
		
		printf("\n");
	}
	
	matrixFree(a,4);
	matrixFree(b,4);
	matrixFree(c,4);
	
}


int** matrixAllocate(int rows)
{
	int** matrix=(int**)malloc(rows * sizeof(int*));
	
	for(int i=0;i<rows;i++)
	matrix[i]=(int*)malloc(rows * sizeof(int));
	
	return matrix;
}


void matrixFree(int** matrix,int rows)
{
	for(int i=0;i<rows;i++)
	free(matrix[i]);
	
	//frees the pointer to the array holding arrays.
	free(matrix);
}

//int** matrixMultiply(int (*a)[4],int (*b)[4],int rows)
int** matrixMultiply(int** a,int** b,int rows)
{
	int** c=matrixAllocate(rows);
	
	if(rows==1)
	{
	 c[0][0]=a[0][0] * b[0][0];
	}
	
	else
	{
		rows=rows/2;
		//partition rows in half to create n/2 x n/2 size submatrices.
	
		int** a00=matrixAllocate(rows);
		int** a01=matrixAllocate(rows);
		int** a10=matrixAllocate(rows);
		int** a11=matrixAllocate(rows);

		int** b00=matrixAllocate(rows);
		int** b01=matrixAllocate(rows);
		int** b10=matrixAllocate(rows);
		int** b11=matrixAllocate(rows);
	
	//filling the elements of submatrices from the original matrices A and B
		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<rows;j++)
				{
					a00[i][j]=a[i][j];
					a01[i][j]=a[i][rows+j];
					a10[i][j]=a[rows+i][j];
					a11[i][j]=a[rows+i][rows+j];
			
					b00[i][j]=b[i][j];
					b01[i][j]=b[i][rows+j];
					b10[i][j]=b[rows+i][j];
					b11[i][j]=b[rows+i][rows+j];
				}
		}
	
	//filling up the submatrices of C(product of A and B),these are c00,c01,c10,c11
	int** c00=matrixAdd(matrixMultiply(a00,b00,rows),matrixMultiply(a01,b10,rows),rows);
	int** c01=matrixAdd(matrixMultiply(a00,b01,rows),matrixMultiply(a01,b11,rows),rows);
	int** c10=matrixAdd(matrixMultiply(a10,b00,rows),matrixMultiply(a11,b10,rows),rows);
	int** c11=matrixAdd(matrixMultiply(a10,b01,rows),matrixMultiply(a11,b11,rows),rows);

	//Adding the submatrices c00,c01,c10,c11 as the elements of product matrix "C".
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<rows;j++)
		{
			c[i][j]=c00[i][j];
			c[i][rows+j]=c01[i][j];
			c[rows+i][j]=c10[i][j];
			c[rows+i][rows+j]=c11[i][j];
		}
	}
	
	matrixFree(c00,rows);
	matrixFree(c01,rows);
	matrixFree(c10,rows);
	matrixFree(c11,rows);
	matrixFree(a00,rows);
	matrixFree(a01,rows);
	matrixFree(a10,rows);
	matrixFree(a11,rows);
	matrixFree(b00,rows);
	matrixFree(b01,rows);
	matrixFree(b10,rows);
	matrixFree(b11,rows);
	}
	
	return c;
}


int** matrixAdd(int** a,int** b,int rows)
{
	int** c=matrixAllocate(rows);
	
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<rows;j++)
		{
			c[i][j]=a[i][j] + b[i][j];
		}
	}
	
	return c;
}
