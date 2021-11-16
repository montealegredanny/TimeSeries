#pragma once
#include "TimeSeries.h"
#include "../Algebra/Polynomial.h"
#include "../LinearAlgebra/Matrix.h"
#include "../LinearAlgebra/GaussElimination.h"

/*
	If we give it coefficients = {c_1,...,c_p} then we model 

	x_n = c_1 x_{n-1} +... + c_p x_{n-p} + w_n

	where w_n ~ N(0, sigma^2).
*/

class AR : public TimeSeries
{
	public: 
		AR(std::vector<double> coeffs, double sigma, std::vector<double> initConditions);
		AR(std::vector<double> coeffs, double sigma) : AR(coeffs, sigma, std::vector<double>(coeffs.size(), 0.0)) {};
		std::vector<double> generate(unsigned long n);
		double var() const;
		bool isStationary() const;
		double getAutoCorrelation(int lag) const;

	private:
		// variables that define the model 
		unsigned int m_p; 
		double m_sigma; 
		std::vector<double> m_coeffs; 
		std::vector<double> m_initConditions; 
		NormalDistribution m_noiseGenerator; 

		// tools that we use to study the AR process 
		bool m_isStationary; 
		Polynomial m_charPoly;
		std::vector<Root> m_roots; 
};