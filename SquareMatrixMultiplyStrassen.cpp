#include<stdio.h>
#include<stdlib.h>

int **matrixMultiply(int **,int **,int);
int **matrixAllocate(int);
void matrixFree(int **,int);
int **matrixAdd(int **,int **,int);
int **matrixSubtract(int **,int **,int);

int main()
{
	int rows;
	printf("Enter the number of rows of the square matrix\n");
	scanf("%d",&rows);
	
	int **A=matrixAllocate(rows);
	int **B=matrixAllocate(rows);
	
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<rows;j++)
		{
			A[i][j]=i+j;
			B[i][j]=i+j;
		}
	}
	
	printf("\nThe first matrix is:\n");

	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<rows;j++)
		{
			printf("%d ",A[i][j]);
		}
		printf("\n");
	}
	
	printf("\nThe second matrix is:\n");
		
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<rows;j++)
		{
			printf("%d ",B[i][j]);
		}
		printf("\n");
	}
	
	
	int **C=matrixMultiply(A,B,rows);
	
	
	printf("\nThe product is:\n");
		
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<rows;j++)
		{
			printf("%d ",C[i][j]);
		}
		printf("\n");
	}
	
	matrixFree(A,rows);
	matrixFree(B,rows);
	matrixFree(C,rows);
	
	return 0;
}


int **matrixMultiply(int **A,int **B,int rows)
{
	
	int **C=matrixAllocate(rows);
	
	if(rows==1)
	C[0][0]=A[0][0] * B[0][0];
	
	else
	{
		rows=rows/2;
		
		int **a00=matrixAllocate(rows);
		int **a01=matrixAllocate(rows);
		int **a10=matrixAllocate(rows);
		int **a11=matrixAllocate(rows);
		
		int **b00=matrixAllocate(rows);
		int **b01=matrixAllocate(rows);
		int **b10=matrixAllocate(rows);
		int **b11=matrixAllocate(rows);
		
		//partitioning the Matrices A and B.
		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<rows;j++)
			{
				a00[i][j]=A[i][j];
				a01[i][j]=A[i][rows+j];
				a10[i][j]=A[rows+i][j];
				a11[i][j]=A[rows+i][rows+j];
				
				b00[i][j]=B[i][j];
				b01[i][j]=B[i][rows+j];
				b10[i][j]=B[rows+i][j];
				b11[i][j]=B[rows+i][rows+j];
			}
		}
		
		
		
		//creating the 10 submatrices 
		int **S1=matrixSubtract(b01,b11,rows);
		int **S2=matrixAdd(a00,a01,rows);
		int **S3=matrixAdd(a10,a11,rows);
		int **S4=matrixSubtract(b10,b00,rows);
		int **S5=matrixAdd(a00,a11,rows);
		int **S6=matrixAdd(b00,b11,rows);
		int **S7=matrixSubtract(a01,a11,rows);
		int **S8=matrixAdd(b10,b11,rows);
		int **S9=matrixSubtract(a00,a10,rows);
		int **S10=matrixAdd(b00,b01,rows);
		
	/*	printf("\n");
		
			for(int i=0;i<rows;i++)
			{
				for(int j=0;j<rows;j++)
				{
					printf("s9 is %d ",S9[i][j]);
				}
				printf("\n");
			}
		
	*/
	printf("s9 is %d ",S9[0][0]);
		
		printf("\n");
		
			for(int i=0;i<rows;i++)
			{
				for(int j=0;j<rows;j++)
				{
					printf("s10 is %d ",S10[i][j]);
				}
				printf("\n");
			}
		
		printf("\n");
		
		//Creating the product matrices
		int **P1=matrixAllocate(rows);
		int **P2=matrixAllocate(rows);
		int **P3=matrixAllocate(rows);
		int **P4=matrixAllocate(rows);
		int **P5=matrixAllocate(rows);
		int **P6=matrixAllocate(rows);
		int **P7=matrixAllocate(rows);
		
		P1=matrixMultiply(a00,S1,rows);
		P2=matrixMultiply(S2,b11,rows);
		P3=matrixMultiply(S3,b00,rows);
		P4=matrixMultiply(a11,S4,rows);
		P5=matrixMultiply(S5,S6,rows);
		P6=matrixMultiply(S7,S8,rows);
		P7=matrixMultiply(S9,S10,rows);
		
		
		printf("\n");
		
			for(int i=0;i<rows;i++)
			{
				for(int j=0;j<rows;j++)
				{
					printf("p7 is %d ",P7[i][j]);
				}
				printf("\n");
			}
		
		printf("\n");
		
		//Was getting the computation of following computation parts wrong!
		int **d1=matrixAdd(P5,P4,rows);
		int **d2=matrixSubtract(d1,P2,rows);
		
		int **c00=matrixAdd(d2,P6,rows);
		int **c01=matrixAdd(P1,P2,rows);
		int **c10=matrixAdd(P3,P4,rows);
		int **c11=matrixSubtract(matrixAdd(P5,P1,rows),matrixAdd(P3,P7,rows),rows);
		
	
		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<rows;j++)
			{
				C[i][j]=c00[i][j];
				C[i][rows+j]=c01[i][j];
				C[rows+i][j]=c10[i][j];
				C[rows+i][rows+j]=c11[i][j];
				
			}
		}
		
				printf("\n");
		for(int i=0;i<rows;i++)
	{
		for(int j=0;j<rows;j++)
		{
			printf("%d ",C[i][j]);
		}
		printf("\n");
	}
		printf("\n");
	
	
		
	}
	
	return C;
}


int **matrixAdd(int **a,int **b,int rows)
{
		int **S=matrixAllocate(rows);
		
		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<rows;j++)
			{
				S[i][j]=a[i][j] + b[i][j];
			}
		}
		
		return S;
}


int **matrixSubtract(int **a,int **b,int rows)
{
		int **S=matrixAllocate(rows);
		
		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<rows;j++)
			{
				S[i][j]=a[i][j] - b[i][j];
			}
		}
		
		return S;
}


int **matrixAllocate(int rows)
{
	int **matrix=(int **)malloc(rows * sizeof(int *));
	
	for(int i=0;i<rows;i++)
	matrix[i]=(int *)malloc(rows * sizeof(int));
	
	return matrix;
}


void matrixFree(int **matrix,int rows)
{
	for(int i=0;i<rows;i++)
	{
		free(matrix[i]);
	}
	
	free(matrix);
}

