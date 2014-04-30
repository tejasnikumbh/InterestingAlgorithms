/*                                                                            *
 * File : strassen.cpp                                                        *
 * ========================================================================== *  
 * Main program to compute the product of two matrices using the strassen     *
 * algorithm. This program makes use of the ogdf::Array2D<double> data type   *  
 * for storing matrices.                                                      *
 * ========================================================================== */

//Including the necessary libraries
#include <ogdf/basic/Array2D.h>
#include <iostream>
#include <string>


//Function prototypes

//Relevant to main program
void initializeMatrix(ogdf::Array2D<double>* matrix);
void displayMatrix(ogdf::Array2D<double>* matrix);

//Relevant to Strassen Algorithm
ogdf::Array2D<double> computeProductStrassen(ogdf::Array2D<double> A,
			      		     ogdf::Array2D<double> B);
void splitMatrix(ogdf::Array2D<double> A,
		 ogdf::Array2D<double>* a11,
		 ogdf::Array2D<double>* a12,
		 ogdf::Array2D<double>* a21,
		 ogdf::Array2D<double>* a22);

void assembleMatrix(ogdf::Array2D<double>* A,
		    ogdf::Array2D<double> a11,
		    ogdf::Array2D<double> a12,
		    ogdf::Array2D<double> a21,
		    ogdf::Array2D<double> a22);

ogdf::Array2D<double> addMatrix(ogdf::Array2D<double> a,
				ogdf::Array2D<double> b);
ogdf::Array2D<double> subMatrix(ogdf::Array2D<double> a,
				ogdf::Array2D<double> b);

//The main program
int main(){

	//Program Introduction
	cout<<"========================================================"<<endl;
	cout<<"This is a program to compute the product of two matrices"<<endl;
	cout<<"using the Strassen Algorithm"<<endl;
	cout<<"========================================================"<<endl;
  	cout<<endl;

	//Matrix Declaration
	ogdf::Array2D<double> matrix1(0,3,0,3);
        ogdf::Array2D<double> matrix2(0,3,0,3);
	
	//Matrix Initialization
	initializeMatrix(&matrix1);
	initializeMatrix(&matrix2);
	
  	//Displaying the two matrices that were initialized
	cout<<"===== Matrices whose product needs to be computed ======"<<endl;
        cout<<endl;
	displayMatrix(&matrix1);
	displayMatrix(&matrix2);	
	
 	//Strassen Algorithm
        ogdf::Array2D<double> product = computeProductStrassen(matrix1,matrix2);	
 
   	//Displaying the result
        cout<<"== Product Matrix computed using Strassen's Algorithm =="<<endl;
	cout<<endl;
	displayMatrix(&product);	
	return 0;
}


/*										
 * Function   : initializeMatrix						*
 * Parameters : matrix - Pointer to Matrix of type ogdf::Array2D	        *	
 * Returns    : void								*
 * ============================================================================ *
 * This function initializes the (i,j)th entry of the input matrix to be i+j    *
 * We accept a pointer to the original matrix, and the original matrix is	*
 * modified.									* 
 * =============================================================================*/

void initializeMatrix(ogdf::Array2D<double>* matrix)
{
	int size1 = matrix->size1(); 	
	int size2 = matrix->size2();
 	for(int i=0;i<size1;i++){
		for(int j=0;j<size2;j++){
			(*matrix)(i,j) = i+j;
		}
	}
	
}


/*										
 * Function   : displayMatrix							*
 * Parameters : matrix - Pointer to Matrix of type ogdf::Array2D		*	
 * Returns    : void								*
 * ============================================================================ *
 * This function displays the matrix passed in as parameter		        *
 * =============================================================================*/

void displayMatrix(ogdf::Array2D<double>* matrix)
{
	int size1 = matrix->size1(); 	
	int size2 = matrix->size2();
	cout<<"Displaying Matrix"<<endl<<endl;;
	for(int i=0;i<size1;i++){
		for(int j=0;j<size2;j++){
			cout<<(*matrix)(i,j)<<" ";
		}
		cout<<endl;
	}
	cout<<endl;

}

/*										
 * Function   : computeProductStrassen						*
 * Parameters : A - First Matrix of type ogdf::Array2D				*
 *		B - Second Matrix of type ogdf::Array2D				*	
 * Returns    : result  - Product of the two matrices				*
 * ============================================================================ *
 * This functions uses the strassen algorithm to compute the product of the two *
 * matrices provided as input. We assume that the matrix has the form 2^n X 2^n	* 
 * In the matrix splitting step, we split the 2 matrices A and B into 4 parts as*
 * follows.									*
 *										*	
 * A = | a11 a12 | and B = | b11 b12 |	Let Product Matrix C =  | c11 c12 |	*
 *     | a21 a22 |	   | b21 b22 |				| c21 c22 |	*
 *										*	
 * We then compute the 7 product terms required by strassens algorithm, recursi *		
 * -vely. They're given as..							*
 *										*		
 * q1 = (a11 + a22) * (b11 + b22)						*
 * q2 = (a21 + a22) * b11							*
 * q3 = a11*( b12 – b22)							*
 * q4 = a22 * (b21 – b11)							*
 * q5 = (a11 + a12) * b22 							*			
 * q6 = (a21 – a11) * (b11 + b12)						*			
 * q7 = (a12 – a22) * (b21 + b22)						*
 *									   	*					
 * The terms of the product matrix are then given as				*
 *										*
 * c11 = q1 + q4 – q5 + q7							*			
 * c12 = q3 + q5 								*
 * c21 = q2 + q4 								*	
 * c22 = q1 + q3 – q2 + q6							*
 *										*		
 * =============================================================================*/

ogdf::Array2D<double> computeProductStrassen(ogdf::Array2D<double> A,
			      		     ogdf::Array2D<double> B)
{

	// Size is same in both dimensions since we assume 2^n X 2^n
	int n = A.size1();
 	int std = n/2; //std is sub term dimension
        
	//Splitting and initializing matrices A and B into 4 parts      
	ogdf::Array2D<double> a11(0,std-1,0,std-1),
			      a12(0,std-1,0,std-1),
			      a21(0,std-1,0,std-1),
			      a22(0,std-1,0,std-1),	
			      b11(0,std-1,0,std-1),
			      b12(0,std-1,0,std-1),
			      b21(0,std-1,0,std-1),	
			      b22(0,std-1,0,std-1);
			      
			      
	//Splitting the Matrix
	splitMatrix(A,&a11,&a12,&a21,&a22);
	splitMatrix(B,&b11,&b12,&b21,&b22);
	
	//Computing the product terms
	ogdf::Array2D<double> q1(0,std-1,0,std-1),
			      q2(0,std-1,0,std-1),
			      q3(0,std-1,0,std-1),
			      q4(0,std-1,0,std-1),
			      q5(0,std-1,0,std-1),
			      q6(0,std-1,0,std-1),
			      q7(0,std-1,0,std-1);

	// Straight computation if base case

	if(std == 1){

		q1(0,0) = (a11(0,0) + a22(0,0))*(b11(0,0) + b22(0,0));		 			
		q2(0,0) = (a21(0,0) + a22(0,0))*(b11(0,0));		 			
		q3(0,0) = a11(0,0)*(b12(0,0) - b22(0,0));		 			
		q4(0,0) = a22(0,0)*(b21(0,0) - b11(0,0));		 			
		q5(0,0) = (a11(0,0) + a12(0,0))*(b22(0,0));		 			
		q6(0,0) = (a21(0,0) - a11(0,0))*(b11(0,0) + b12(0,0));		 			
		q7(0,0) = (a12(0,0) - a22(0,0))*(b21(0,0) + b22(0,0));		 			

	}else{
	
	//Computing the product terms recursively if not base case

	        q1 = computeProductStrassen(addMatrix(a11,a22),
	                	            addMatrix(b11,b22));
	 	q2 = computeProductStrassen(addMatrix(a21,a22),
	    			            b11);
	 	q3 = computeProductStrassen(a11,
				            subMatrix(b12,b22));
                q4 = computeProductStrassen(a22,
				            subMatrix(b21,b11));
	        q5 = computeProductStrassen(addMatrix(a11,a12),
				            b22);
	        q6 = computeProductStrassen(subMatrix(a21,a11),
				            addMatrix(b11,b12));
                q7 = computeProductStrassen(subMatrix(a12,a22),
				            addMatrix(b21,b22));

	}

	// Computing the terms of the product matrix 		 

        ogdf::Array2D<double> c11(0,std-1,0,std-1),
			      c12(0,std-1,0,std-1),
			      c21(0,std-1,0,std-1),
			      c22(0,std-1,0,std-1);

	c11 = addMatrix(addMatrix(q1,q4),subMatrix(q7,q5));
        c12 = addMatrix(q3,q5);
	c21 = addMatrix(q2,q4);
	c22 = addMatrix(addMatrix(q1,q3),subMatrix(q6,q2));

	// Re-assembling the product Matrix

	ogdf::Array2D<double> productMatrix(0,2*std-1,0,2*std-1);
	assembleMatrix(&productMatrix,c11,c12,c21,c22);
		

	return productMatrix;
}

/* Function   : addMatrix							*
 * Parameters : a,b = Matrices to be added					*
 * Returns    : ogdf::Array2D<double> which is the addition matrix 		*
 * ============================================================================ *
 * Adds two matrices and returns the resulting matrix.				*
 * ============================================================================ */

ogdf::Array2D<double> addMatrix(ogdf::Array2D<double> a,
				ogdf::Array2D<double> b)
{
	//Size is same for all dimensions
	int size = a.size1();

	//Adding the individual entries
	ogdf::Array2D<double> result(0,size-1,0,size-1);
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			result(i,j) = a(i,j) + b(i,j);
		}
	}
	
	return result;
}

/* Function   : subMatrix							*
 * Parameters : a,b = Matrices to be subtracted					*
 * Returns    : ogdf::Array2D<double> which is the subtraction matrix 		*
 * ============================================================================ *
 * Subtracts b from a(a - b) and returns the resulting matrix.			*
 * ============================================================================ */

ogdf::Array2D<double> subMatrix(ogdf::Array2D<double> a,
				ogdf::Array2D<double> b)
{
	//Size is same for all dimensions
	int size = a.size1();

	//Subtracting the individual entries
	ogdf::Array2D<double> result(0,size-1,0,size-1);
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			result(i,j) = a(i,j) - b(i,j);
		}
	}

	return result;
}

/*										
 * Function   : splitMatrix							*
 * Parameters : A - Pointer to Matrix of type ogdf::Array2D that needs to be	*	
 * 		split.								*
 * 		a11,a12,a21,a22 - Submatrices in which the split terms are sto  *
 *		-red								*
 * Returns    : void								*
 * ============================================================================ *
 * This function splits the input matrices into 4 parts and stores the result	*
 * int the submatrices given as input(by reference)			        *
 * =============================================================================*/

void splitMatrix(ogdf::Array2D<double> A,
		 ogdf::Array2D<double>* a11,
		 ogdf::Array2D<double>* a12,
		 ogdf::Array2D<double>* a21,
		 ogdf::Array2D<double>* a22)
{

	//Size is same in both dimensions
	int size = a11->size1();		
	
	//Simply storing relevant entries in relevant places.
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			(*a11)(i,j) = A(i,j);
		}	
	}

	for(int i=0;i<size;i++){
		for(int j=size;j<2*size;j++){
			(*a12)(i,j - size) = A(i,j);
		}	
	}

	for(int i=size;i<2*size;i++){
		for(int j=0;j<size;j++){
			(*a21)(i - size,j) = A(i,j);
		}	
	}

	for(int i=size;i<2*size;i++){
		for(int j=size;j<2*size;j++){
			(*a22)(i - size,j - size) = A(i,j);
		}	
	}

}

/*										
 * Function   : assembleMatrix							*
 * Parameters : A - Matrix into which the submatrices need to be assembled      *
 * 		a11,a12,a21,a22 - Submatrices in which the split terms are sto  *
 *		-red								*
 * Returns    : void								*
 * ============================================================================ *
 * This function assembles the entries given  in the 4 submatries passed as     * 
 * parameters and stores them into the top level A matrix which is passed by	*
 * reference.									*		
 * =============================================================================*/

void assembleMatrix(ogdf::Array2D<double>* A,
		    ogdf::Array2D<double> a11,
		    ogdf::Array2D<double> a12,
		    ogdf::Array2D<double> a21,
		    ogdf::Array2D<double> a22)
{
	//Size is same in both dimensions
	int size = a11.size1();

	// Re-assmebling process for all 4 submatrices
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			(*A)(i,j) = a11(i,j);
		}
	}	

	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			(*A)(i,size + j) = a12(i,j);
		}
	}	

	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			(*A)(i + size,j) = a21(i,j);
		}
	}	

	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			(*A)(i + size,j + size) = a22(i,j);
		}
	}	

}
