#pragma once 
# include "Algebra/DifferenceEquationSolver.h"
# include "TimeSeries/AR.h"
# include "TimeSeries/DataAnalysis.h"
# include "LinearAlgebra/Matrix.h"

template <typename T>
void print(T x)
{
	for (auto val : x)
	{
		std::cout << val << std::endl;
	}
}

int main()
{
	//DifferenceEquation diffEqtn{ std::vector<double>{1.0, -2.0, -1.0}, std::vector<double>{0.0, 1.0,2.0} };
	//DifferenceEquationSolver solver{ diffEqtn }; 	
	//solver.solve(); 
	//double sigma = 2.0;
	//double c = -.75;
	//
	//AR test1{ std::vector<double>{c},sigma };

	//std::cout << test1.isStationary() << std::endl; 

	std::vector<double> row1{ 1.0, 2.0 }; 
	std::vector<double> row2{ 0.0, 1.0 }; 
	Matrix mat{ std::vector<std::vector<double>> {row1, row2} };

	print(solveMatrixEqtn(mat, std::vector<double>{2.0, 3.0}));

	return 0; 
}
