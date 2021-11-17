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
		charPolyCoeffs[idx] = -1.0* coeffs[m_p - idx - 1];
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

	// in the case of stationary time series we can set up and solve for the 
	// difference equation which gives us the autocovariance function. 
	if (m_isStationary)
	{
		setDifferenceEqtn(); 
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
			double noise = m_noiseGenerator.generate();
			newVal += noise;
			series[idx] = newVal;
		}
	}
	return series;
}

double AR::var() const
{
	return getAutoCovariance(0);
}

bool AR::isStationary() const
{
	return m_isStationary;
}

double AR::getAutoCovariance(int lag) const
{
	return m_autoCovarianceDiffEqtn.generate(lag+1)[lag]; 
}

double AR::getAutoCorrelation(int lag) const
{
	double var = this->var();
	double autocovariance = this->getAutoCovariance(lag); 
	return autocovariance / var;
}

void AR::setDifferenceEqtn()
{
	// first find the initial conditions by setting up a system of equations
	m_autoCovarianceDiffEqtn = DifferenceEquation(m_coeffs, findInitialConditions());
}

std::vector<double> AR::findInitialConditions()
{
	// we want to find the p initial values for the autocovariance function. 
	std::vector<std::vector<double>> initialConditionsCoeffs;
	std::vector<double> eqtnVals(m_p);
	for (int lag = 0; lag < int(m_p); lag++)
	{
		if (lag == 0)
		{
			std::vector<double> row(m_p);
			row[0] = 1. - std::inner_product(std::begin(m_coeffs), std::end(m_coeffs), std::begin(m_coeffs), 0.0);
			for (int i = 1; i < int(m_p); i++)
			{
				double coeff_i = 0.0;
				for (int j = i + 1; j <= int(m_p); j++)
				{
					coeff_i += m_coeffs[j - 1] * m_coeffs[j - i - 1];
				}
				coeff_i *= -2.0;
				row[i] = coeff_i;
			}
			initialConditionsCoeffs.push_back(row);
			eqtnVals[lag] = m_sigma * m_sigma;
		}
		else
		{
			// we use the definition of an AR(p) process to set the equations up
			std::vector<double> row(m_p);
			for (int idx = 0; idx < int(m_p); idx++)
			{
				double coeffVal = 0.0;
				if (idx == 0)
				{
					coeffVal = m_coeffs[lag - 1];
				}
				else
				{
					if (lag + idx <= int(m_p))
					{
						coeffVal += m_coeffs[lag + idx - 1];
					}
					if (lag - idx > 0)
					{
						coeffVal += m_coeffs[lag - idx - 1];
					}
					if (lag == idx)
					{
						coeffVal -= 1.0;
					}
				}
				row[idx] = coeffVal;
			}
			initialConditionsCoeffs.push_back(row);
		}
	}
	return solveMatrixEqtn(Matrix(initialConditionsCoeffs), eqtnVals);
}