#include "MA.h"

MA::MA(std::vector<double> coeffs, double sigma)
{
	m_coeffs = coeffs;
	m_q = unsigned int(coeffs.size());
	m_sigma = sigma;
	m_noiseGenerator = NormalDistribution{ 0.0, sigma };
}

std::vector<double> MA::generate(unsigned long n)
{
	std::vector<double> noise{ m_noiseGenerator.generate(n) };
	std::vector<double> sample(n); 
	for (unsigned long idx = 0; idx < n; idx++)
	{
		if (idx < m_q)
		{
			sample[idx] = noise[idx];
		}
		else 
		{
			std::vector<double> noiseSliced = std::vector<double>(noise.rbegin() + (n - idx), noise.rbegin() + m_q + (n - idx));
			double newVal = std::inner_product(std::begin(noiseSliced), std::end(noiseSliced), std::begin(m_coeffs), 0.0) + noise[idx];
			sample[idx] = newVal;
		}
	}

	return sample;
}

double MA::var() const
{
	return (std::inner_product(std::begin(m_coeffs), std::end(m_coeffs), std::begin(m_coeffs), 0.0) + 1.0) * m_sigma * m_sigma;
}

bool MA::isStationary() const
{
	return m_isStationary;
}

double MA::getAutoCovariance(int lag) const
{
	if (lag > m_q)
	{
		return 0.0; 
	}
	double total = 0.0; 
	for (int i = lag; i <= m_q; i++)
	{
		total += (this->getCoeff(i - lag)) * (this->getCoeff(i));
	}
	return m_sigma * m_sigma * total;
}

double MA::getAutoCorrelation(int lag) const
{
	return this->getAutoCovariance(lag) / this->var();
}

std::vector<double> MA::getAutoCovariance(int startIdx, int endIdx)
{
	return std::vector<double>();
}

std::vector<double> MA::getAutoCorrelation(int startIdx, int endIdx)
{
	return std::vector<double>();
}

double MA::getCoeff(int k) const
{
	if (k == 0)
	{
		return 1.0;
	}

	return m_coeffs[k-1];
}
