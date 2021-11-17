#pragma once 
# include "Algebra/DifferenceEquationSolver.h"
# include "TimeSeries/AR.h"
# include "TimeSeries/DataAnalysis.h"
# include "LinearAlgebra/Matrix.h"
# include "LinearAlgebra/OLS.h"
# include "examples.h"


int main()
{	
	/*
	examplePolynomial(); 
	examplePolynomial2();
	exampleGaussianElimination();
	exampleSolveMatrixEquation();
	exampleAR();
	exampleOLS(); 
	*/

	Matrix A{
		{{6., 1., 1.},
		{4., -2., 5.},
		{2., 8., 7.}}
	};

	Matrix B{
		{{4.,1.},
		{2.,3.}}
	};

	std::cout << B.determinant() << std::endl;
	return 0; 
}
