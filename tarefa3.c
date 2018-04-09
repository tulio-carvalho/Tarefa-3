#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void imprime1( double **M, int dim) // função que imprime a matriz
{
	printf("\n");
	for(int i=0;i<dim;i++) 
	{	for(int j=0;j<dim+1;j++) 
			
			printf("%3f ",M[i][j]);	  
		
		puts("");
	}		
	printf("\n*******************************\n");
}

double **leitura(char *arq, int *n) // função para leitura do arquivo que contém o sistema linear a ser solucionado
{
	int tam,a;
	double **x;
	FILE *fp;

	fflush(stdin);
	
	if((fp=(fopen("tarefa3.dat","r")))==NULL)
		return NULL;
		
	fscanf(fp,"%d",&tam);
	
	x=malloc(tam*sizeof(double));
	
	for(int i=0;i<tam;i++)
	{
		x[i]=(double *)malloc((tam+1)*sizeof(double*));
	}
	
	for(int i=0;i<tam;i++)
	{
		for(int j=0;j<tam+1;j++) // a condição de j deve ir uma coluna a mais da dimensao do sistema, assim conseguimos imprimir a matriz aumentada referente ao sistema linear
		{
			fscanf(fp,"%d",&a);
			x[i][j]=a;
		}
	}
	
	*n=tam;
	fclose(fp);
	return x;
}	

double **triangsup(double **M, int dim) // função triangular superior
{
	int i,j,k,l;
	double auxiliar; // variável auxiliar para calculo dos passos da triangularização
	
	for(k=0;k<dim;k++) 
	{
		for (i=k+1;i<dim;i++)
		{
			auxiliar=M[i][k]/M[k][k];
			
			for(j=0;j<dim;j++)
			{
				M[i][j]=M[i][j]-(auxiliar*M[k][j]);
			}
		}
		printf("\n Passo %d\n", k+1); // k+1 para não imprimir zero no terminal
		imprime1(M,dim);
	}
	return M;
}

void subsreversa(double **M, double* raizes, int dim)
{
	double x[dim], soma[dim], auxiliar;
	int i, j;
	
	for(i=dim-1;i>=0;i--)
	{
		soma[i]=0;
		
		for(j=i;j<=dim;j++)
		{
			soma[i]=soma[i]+M[i][j-1]*raizes[j-1];
		}
		
		auxiliar=M[i][dim];
		x[i]=auxiliar-soma[i];
		raizes[i]=x[i]/M[i][i];
	}	
}

int main (int argc , char ** argv )
{
	double ** M;
	double * raizes ;
	int i , dim ;

	M= leitura ( argv [1] ,& dim );
	imprime1 (M , dim ) ;
	triangsup (M , dim ) ;
	imprime1 (M , dim ) ;
	raizes = malloc ( dim * sizeof ( double ) );
	subsreversa (M , raizes , dim );
	for ( i =0; i < dim ; i ++) 
		printf ("x%1d = %5.2lf\n",i , raizes [i]) ;
 	return 0;
}
