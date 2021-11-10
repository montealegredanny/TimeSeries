#define _USE_MATH_DEFINES
#include "Polynomial.h"
#include <math.h>

Polynomial::Polynomial(std::vector<double> coefficients)
{
	m_coeffs =  coefficients;
	m_degree = int(m_coeffs.size()) - 1;
}

std::ostream& operator<<(std::ostream& output, const Polynomial& poly)
{
	output << poly.m_coeffs[0]; 
	for (int deg = 1; deg <= poly.m_degree; deg++)
	{
		if (poly.m_coeffs[deg] < 0)
		{
			output << poly.m_coeffs[deg] << "x^" << deg;
		}
		else if (poly.m_coeffs[deg] > 0)
		{
			output << "+" << poly.m_coeffs[deg] << "x^" << deg;
		}
		else {
			continue;
		}
	}
	return output;
}

std::vector<Root> Polynomial::findRoots(const double precision, const unsigned long maxIter) const
{
	// we find the roots (in complex numbers) for our polynomial using the Durand-Kerner method
	// create vectors where we will store the current and new solutions 
	std::vector<std::complex<double>> currentSolutions;
	std::vector<std::complex<double>> newSolutions;

	// initialize the solutions to roots of unity
	currentSolutions = AlgebraHelper::rootsUnit(this->m_degree);

	unsigned long numIters = 0;
	bool quit = false;
	double distance; 
	while (!quit)
	{
		newSolutions = AlgebraHelper::iterateDurandKerner(*this, currentSolutions);
		numIters += 1; 

		// check if the precision is met
		distance = AlgebraHelper::maxDistance(currentSolutions, newSolutions);
		if (distance < precision || numIters > maxIter)
		{
			quit = true;
		}
		
		currentSolutions = newSolutions;
	}

	// create a vector of Roots
	std::vector<Root> v_roots; 
	bool isNewRoot; 
	for (size_t idx = 0 ; idx < currentSolutions.size() ; idx ++)
	{
		std::complex<double> solution = currentSolutions[idx];
		isNewRoot = true;

		for (Root& root : v_roots)
		{
			if (solution == root)
			{
				isNewRoot = false;
				root.increaseMultiplicity();
			}
		}
		if (isNewRoot)
		{
			v_roots.push_back(Root{ solution });
		}
	}
	//std::cout << numIters << std::endl;
	return v_roots;
}

int Polynomial::getDegree() const
{
	return m_degree;
}

std::vector<double> Polynomial::getCoeffs() const
{
	return m_coeffs;
}

double AlgebraHelper::maxDistance(const std::vector<std::complex<double>>& v1, const std::vector<std::complex<double>>& v2)
{
	// given two vectors of equal size, we return the max_i (||v1[i] - v2[i]||)
	// where ||*|| is the L2 norm 

	double currentDistance = 0.0; 
	double newDistance;
	for (size_t idx = 0; idx < v1.size(); idx++)
	{
		newDistance = normSquare(v1[idx] - v2[idx]); 
		currentDistance = newDistance > currentDistance ? newDistance : currentDistance;
	}
	return pow(currentDistance, 0.5);
}

std::vector<std::complex<double>> AlgebraHelper::rootsUnit(const unsigned int n)
{
	std::vector<std::complex<double>> roots{};
	for (size_t idx = 0; idx < n; idx++)
	{
		roots.push_back(std::complex<double>{cos(2.0 * M_PI * idx / n), sin(2.0 * M_PI * idx / n)});
	}
	return roots;
}

std::vector<std::complex<double>> AlgebraHelper::iterateDurandKerner(const Polynomial& poly, std::vector<std::complex<double>>& currentSolutions)
{
	std::vector<std::complex<double>> newSolutions{}; 
	const unsigned int degree = poly.getDegree();

	for (unsigned int idx = 0; idx < degree; idx++)
	{
		std::complex<double> newRoot = currentSolutions[idx];
		std::complex<double> offset = poly(newRoot); 
		for (unsigned int m = 0; m < idx; m++)
		{
			offset /= (newRoot - newSolutions[m]);
		}
		for (unsigned int k = idx + 1; k < degree; k++)
		{
			offset /= (newRoot - currentSolutions[k]);
		}
		newSolutions.push_back(newRoot - offset);
	}
	return newSolutions;
}

