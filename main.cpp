#pragma once 
#include <iostream>
#include "DifferenceEquations.h"
#include <vector>
#include "Polynomial.h"

#include <iterator>
#include <algorithm>
#include <complex>

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
	DifferenceEquation diffEqtn{ std::vector<double>{0.5, 0.5}, std::vector<double>{2.0, 1.0} };
	std::vector<double> series = diffEqtn.generate(10);


	Polynomial test{ std::vector<double> {1.0, 2.0, 1.0} };
	std::cout << "polynomial f(x) = " << test << std::endl;
	auto solutions = test.findRoots(1e-6, 1e6);
	std::cout << "solutions :\n";
	print(solutions);
	return 0; 
}
