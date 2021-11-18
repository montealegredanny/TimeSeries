#pragma once
#include "TimeSeries.h"
#include "../Algebra/Polynomial.h"
#include "../LinearAlgebra/Matrix.h"
#include "../LinearAlgebra/GaussElimination.h"
#include "../Algebra/DifferenceEquations.h"

/*
	If we give it coefficients = {c_1,...,c_q} then we model

	x_n = w_n + c_1 w_{n-1} +... + c_q w_{n-q}

	where w_n ~ N(0, sigma^2) are iid 
*/

class MA : public TimeSeries
{
public:
	MA(std::vector<double> coeffs, double sigma);
	std::vector<double> generate(unsigned long n);
	double var() const;
	bool isStationary() const;
	double getAutoCovariance(int lag) const;
	double getAutoCorrelation(int lag) const;

private:
	// variables that define the model 
	unsigned int m_q;
	double m_sigma;
	std::vector<double> m_coeffs;
	NormalDistribution m_noiseGenerator;
	bool m_isStationary = true;
	double getCoeff(int k) const;
};