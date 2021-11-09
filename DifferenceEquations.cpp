#include "DifferenceEquations.h"
#include <assert.h>

DifferenceEquation::DifferenceEquation(std::vector<double> coefficients, std::vector<double> initialConditions)
{
	m_coeffs = coefficients; 
	m_initConditions = initialConditions;
	assert(m_coeffs.size() == m_initConditions.size() && "Size of coefficients and initial conditions must be the same");
	m_degree = int(coefficients.size());
}

std::vector<double> DifferenceEquation::generate(long n) 
{
	std::vector<double> values{ m_initConditions };
	
	for (long idx = 0; idx < n; idx++)
	{
		double value = 0.0;
		for (int j = 0; j < m_degree; j++)
		{
			value += (m_coeffs[j] * values[values.size() - 1 - j]);
		}
		values.push_back(value); 
	}
	return values;
}