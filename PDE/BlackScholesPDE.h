#pragma once
# include "FTCS.h"
# include "../Algebra/Interpolator2D.h"
# include <algorithm>
#include <functional>

struct BlackScholesPDEArgs
{
	BlackScholesPDEArgs(double numStdvs, long numXSteps, long numTSteps) : m_numStdvs(numStdvs), m_numXSteps(numXSteps), m_numTSteps(numTSteps) {}; 
	double m_numStdvs = 5;
	long m_numXSteps = 100L; 
	long m_numTSteps = 200L; 
};

class BlackScholesPDESolution
{
	public:
		BlackScholesPDESolution(Interpolator2D xGrid, double vol, double strike, double riskFreeRate, double timeToMaturity) :
			m_xGrid(xGrid), m_vol(vol), m_strike(strike), m_riskFreeRate(riskFreeRate), m_timeToMaturity(timeToMaturity) {};
		double operator() (double spot, double tau) const;
	private: 
		Interpolator2D m_xGrid; 
		double m_vol; 
		double m_strike; 
		double m_riskFreeRate;
		double m_timeToMaturity;
};

BlackScholesPDESolution solveBlackScholesPDE(double spot, double strike, double vol, double timeToMaturity, double riskFreeRate, BlackScholesPDEArgs args);