#pragma once
#include<vector>
#include "Polynomial.h"

class DifferenceEquation
{
	public:
		DifferenceEquation(std::vector<double> coefficients, std::vector<double> initialConditions); 
		std::vector<double> generate(long n); 
		int getDegree() const;
		std::vector<double> getCoeffs() const; 
		std::vector<double> getInitConditions() const;

	private:
		std::vector<double> m_coeffs; 
		std::vector<double> m_initConditions;
		int m_degree;

};

void testDifferenceEquations();