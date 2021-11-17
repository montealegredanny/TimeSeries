#pragma once 
# include "Algebra/DifferenceEquationSolver.h"
# include "TimeSeries/AR.h"
# include "TimeSeries/DataAnalysis.h"
# include "LinearAlgebra/Matrix.h"
# include "LinearAlgebra/OLS.h"
# include "examples.h"


int main()
{	
	examplePolynomial(); 
	examplePolynomial2();
	exampleGaussianElimination();
	exampleSolveMatrixEquation();
	exampleAR();
	
	return 0; 
}
