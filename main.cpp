#pragma once 
# include "Algebra/DifferenceEquationSolver.h"
# include "TimeSeries/AR.h"
# include "TimeSeries/DataAnalysis.h"
# include "LinearAlgebra/Matrix.h"
# include "LinearAlgebra/OLS.h"
# include "examples.h"
# include "TimeSeries/MA.h"

int main()
{	
	
	examplePolynomial(); 
	examplePolynomial2();
	exampleGaussianElimination();
	exampleSolveMatrixEquation();
	exampleOLS(); 
	exampleAR();
	exampleAR2();
	exampleMA();
	exampleMA2();
	return 0; 
}
