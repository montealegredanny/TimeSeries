#pragma once
#include<vector>
#include "Polynomial.h"

class DifferenceEquation
{
	public:
		DifferenceEquation() : m_coeffs({}), m_initConditions({}), m_degree(0) {};
		DifferenceEquation(std::vector<double> coefficients, std::vector<double> initialConditions); 
		std::vector<double> generate(long n) const; 
		int getDegree() const;
		std::vector<double> getCoeffs() const; 
		std::vector<double> getInitConditions() const;

	private:
		std::vector<double> m_coeffs; 
		std::vector<double> m_initConditions;
		int m_degree;

};

void testDifferenceEquations();