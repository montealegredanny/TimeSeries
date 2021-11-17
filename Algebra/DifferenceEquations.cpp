#include "DifferenceEquations.h"
#include <assert.h>

/*
The coefficients are interpreted as follows. If the coeffs given = {c_1, .., c_q} 
then the recursion is given by u_n = c_1 u_{n-1} + .. + c_q u_{n-q} 
and we must specify a total of q initial values. 
*/

DifferenceEquation::DifferenceEquation(std::vector<double> coefficients, std::vector<double> initialConditions)
{
	m_coeffs = coefficients; 
	m_initConditions = initialConditions;
	assert(m_coeffs.size() == m_initConditions.size() && "Size of coefficients and initial conditions must be the same");
	m_degree = int(coefficients.size());
}

std::vector<double> DifferenceEquation::generate(long n) const
{
	std::vector<double> values{ m_initConditions };
	
	for (long idx = 0; idx < n - m_degree; idx++)
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

int DifferenceEquation::getDegree() const
{
	return m_degree;
}

std::vector<double> DifferenceEquation::getCoeffs() const
{
	return m_coeffs;
}

std::vector<double> DifferenceEquation::getInitConditions() const
{
	return m_initConditions;
}

void testDifferenceEquations()
{
	DifferenceEquation diffEqtn{ std::vector<double>{0.0, 0.5}, std::vector<double>{1.0, 3.0} };
	auto vals = diffEqtn.generate(10);
	for (auto& val : vals)
	{
		std::cout << val << std::endl;
	}
}
