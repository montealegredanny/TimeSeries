#pragma once 
#include <iostream>
#include <vector>
#include <complex>
#include "Polynomial.h"
#include "DifferenceEquations.h"
#include "DifferenceEquationSolver.h"

template <typename T>
void print(T x)
{
	for ( auto& val : x)
	{
		std::cout << val << std::endl;
	}
}

int main()
{

	std::cout << "===================================================================================================================" << std::endl; 
	DifferenceEquation diffEqtn{ std::vector<double>{1.0, 1.0}, std::vector<double>{1.0,1.0} };
	DifferenceEquationSolver solver{ diffEqtn }; 
	auto foo = diffEqtn.generate(20);
	print(foo); 
	std::cout << "===================================================================================================================" << std::endl;

	solver.solve(); 
	int x = 1; 
	return 0; 
}
