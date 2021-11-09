#pragma once
#include<vector>

class DifferenceEquation
{
	public:
		DifferenceEquation(std::vector<double> coefficients, std::vector<double> initialConditions); 
		std::vector<double> generate(long n); 



	private:
		std::vector<double> m_coeffs; 
		std::vector<double> m_initConditions;
		int m_degree;
		std::vector<double>* m_solutionsPolynomialPtr = nullptr;

};