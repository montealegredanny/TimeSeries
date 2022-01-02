#include "FTCS.h"

FTCS::FTCS(double a, point xBounds, point tBounds, long xSteps, long tSteps, double(*lowerXLambda)(double), double(*upperXLambda)(double), double(*lowerTLambda)(double))
{
	// set the variables 
	m_a = a; 
	m_xMax = xBounds.second; 
	m_xMin = xBounds.first; 
	m_tMax = tBounds.second; 
	m_tMin = tBounds.first; 
	m_xSteps = xSteps; 
	m_tSteps = tSteps; 
	m_lowerXLambda = lowerXLambda; 
	m_upperXLambda = upperXLambda;
	m_lowerTLambda = lowerTLambda;
	m_deltaX = (m_xMax - m_xMin) / m_xSteps; 
	m_deltaT = (m_tMax - m_tMin) / m_tSteps; 
	// create the vectors that will define the grid points: 
	m_xVec.reserve(xSteps + 1L); 
	m_tVec.reserve(tSteps + 1L);
	for (long idx = 0; idx <= m_xSteps; idx++)
	{
		m_xVec.push_back(m_xMin + idx * m_deltaX);
	}
	for (long idx = 0; idx <= m_tSteps; idx++)
	{
		m_tVec.push_back(m_tMin + idx * m_deltaT); 
	}
}

void FTCS::fit()
{
	// check if the problem will converge -- 
	const double r = m_a * m_deltaT / m_deltaX / m_deltaX; 
	std::cout << "r = " << r << std::endl;
	assert(r <= 0.5 && "Scheme is unstable!");

	// create the boundary points 

	// boundary for xMin: 
	for (const auto& t : m_tVec)
	{
		m_grid[{m_xVec[0], t}] = m_lowerXLambda(t);
	}

	// boundary for xMax: 
	for (const auto& t : m_tVec)
	{
		m_grid[{m_xVec.back(), t}] = m_upperXLambda(t);
	}

	// boundary for min t
	for (const auto& x : m_xVec)
	{
		m_grid[{x, m_tVec[0]}] = m_lowerTLambda(x);
	}

	// create the forward time, centered space scheme
	for (long timeIdx = 0; timeIdx <= m_tSteps - 1L; timeIdx++)
	{
		for (long xIdx = 1L; xIdx <= m_xSteps - 1L; xIdx++)
		{
			m_grid[{m_xVec[xIdx], m_tVec[timeIdx + 1L]}] = r * (m_grid[{m_xVec[xIdx - 1L], m_tVec[timeIdx]}] + m_grid[{m_xVec[xIdx + 1L], m_tVec[timeIdx]}]) + (1.0 - 2.0 * r) * (m_grid[{m_xVec[xIdx], m_tVec[timeIdx]}]);
		}
	}
}

std::map<point, double> FTCS::getGrid() const
{
	return m_grid;
}

std::vector<double> FTCS::getXVec() const
{
	return m_xVec;
}

std::vector<double> FTCS::getTVec() const
{
	return m_tVec;
}
