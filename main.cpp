#pragma once 
# include "Algebra/DifferenceEquationSolver.h"
# include "TimeSeries/AR.h"
# include "TimeSeries/DataAnalysis.h"
# include "LinearAlgebra/Matrix.h"
# include "LinearAlgebra/OLS.h"
# include "examples.h"
# include "TimeSeries/MA.h"
# include  "Algebra/Interpolator2D.h"
# include "PDE/BlackScholesPDE.h"


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
	exampleFitAR();
	exampleInterpolator2D();
	exampleHeatEquation();
	exampleBSPDE();

	// TODO : create a method to evaluate the calls using MC simulations. 
	// we will crate a set of paths, and then save the endpoints
	// using these endpoints we will find the expected payoff. 
	return 0; 
}

