#pragma once 
#include "DifferenceEquationSolver.h"

int main()
{
	DifferenceEquation diffEqtn{ std::vector<double>{1.0, -2.0, -1.0}, std::vector<double>{0.0, 1.0,2.0} };
	DifferenceEquationSolver solver{ diffEqtn }; 	
	solver.solve(); 
	return 0; 
}
