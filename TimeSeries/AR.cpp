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
	// TODO : implement 
	return 0.0;
}

bool AR::isStationary() const
{
	return m_isStationary;
}

double AR::getAutoCorrelation(int lag) const
{
	// we will solve this using difference equations. 
	// first we need to set up the p initial conditions 
	// then the AR coefficients will define the Autocovariance process for lags >= p. 

	std::vector<std::vector<double>> initialConditionsCoeffs;
	std::vector<double> eqtnVals(m_p); 
	for (unsigned int lag = 0; lag < m_p; lag++)
	{
		if (lag == 0)
		{
			// in this case we have a trivial equation which gives us correlation lag = 0 is 1.0. 
			std::vector<double> row(m_p, 0.0);
			row[0] = 1.0; 
			initialConditionsCoeffs.push_back(row); 
			eqtnVals[lag] = 1.0; 
		}
		else
		{
			// we use the definition of an AR(p) process to set the equations up
			std::vector<double> row(m_p); 
			for (unsigned int idx = 0; idx < m_p; idx++)
			{
				double coeffVal = 0.0; 
				if (idx == 0)
				{
					coeffVal = m_coeffs[lag - 1]; 
				}
				else
				{
					if (lag + idx <= m_p)
					{
						coeffVal += m_coeffs[lag + idx - 1L];
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
	
	auto solutions = solveMatrixEqtn(Matrix(initialConditionsCoeffs), eqtnVals);
	for (auto val : solutions)
	{
		std::cout << val << std::endl;
	}
	return 0.0;
}
