#include "AR.h"

AR::AR(std::vector<double> coeffs, double sigma, std::vector<double> initConditions)
{
	m_coeffs = coeffs; 
	m_p = unsigned int(coeffs.size());
	m_sigma = sigma;
	m_noiseGenerator = NormalDistribution{ 0.0, sigma };
	m_initConditions = initConditions; 

	// create the char polynomial
	std::vector<double> charPolyCoeffs(m_p);
	for (unsigned int idx = 0; idx < m_p; idx++)
	{
		charPolyCoeffs[idx] = coeffs[m_p - idx - 1];
	}
	charPolyCoeffs.push_back(1.0);
	m_charPoly = Polynomial{ charPolyCoeffs };

	// find the roots of the char poly 
	std::vector<Root> m_roots{ m_charPoly.findRoots() };
	
	// we only have a stationary process if all the roots are less than 1.0 in abs. 
	m_isStationary = true;
	for (const Root& rt : m_roots)
	{
		if (abs(rt.getValue()) > 1.0)
		{
			m_isStationary = false; 
			break;
		}
	}

}

std::vector<double> AR::generate(unsigned long n)
{
	std::vector<double> v_lastVals;
	double newVal;
	std::vector<double> series(n); 
	for (unsigned int idx = 0; idx < n; idx++)
	{
		if (idx < m_p)
		{
			series[idx] = m_initConditions[idx];
		}
		else
		{
			v_lastVals = std::vector<double>(series.rbegin() + (n - idx), series.rbegin() + m_p + (n-idx));
			newVal = std::inner_product(std::begin(v_lastVals), std::end(v_lastVals), std::begin(m_coeffs), 0.0);
			newVal += m_noiseGenerator.generate();
			series[idx] = newVal;
		}
	}
	return series;
}

double AR::var() const
{
	// TODO : implement 
	return 0.0;
}

bool AR::isStationary() const
{
	return m_isStationary;
}
