#pragma once 
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <complex>
#include "Polynomial.h"
#include "DifferenceEquations.h"

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
	Polynomial test{ std::vector<double> {1.0, 2.0, 1.0} };
	auto solutions = test.findRoots(1e-6, 10000L);
	std::cout << "solutions :\n";
	print(solutions);
	return 0; 
}
