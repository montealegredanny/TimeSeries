#include "BlackScholesPDE.h"


BlackScholesPDESolution solveBlackScholesPDE(double spot, double strike, double vol, double timeToMaturity, double riskFreeRate, BlackScholesPDEArgs args)
{
	// we reduce the problem to the heat equation example 

	// create a set of bounds for the end point of the lognormal process. 
	const double lowerBoundX = std::log(spot) - args.m_numStdvs * std::sqrt(timeToMaturity) * vol;
	const double upperBoundX = std::log(spot) + args.m_numStdvs * std::sqrt(timeToMaturity) * vol;

	// create a lambda function that will let us go from the space where we solve the PDE to the spot space. 
	auto xToSpot = [riskFreeRate, timeToMaturity, vol](double x, double tau)->double
	{
		return std::exp(x + (riskFreeRate - vol * vol / 2.0) * (timeToMaturity - tau));
	};

	// create the lambda functions for the boundary conditions 
	auto lowerTLambda = [xToSpot, strike](double x) -> double {return std::max(xToSpot(x, 0.0) - strike, 0.0); };
	auto upperXLambda = [xToSpot, strike, upperBoundX, riskFreeRate](double tau) -> double {return xToSpot(upperBoundX, tau) - std::exp(-riskFreeRate * tau) * strike; };
	auto lowerXLambda = [](double tau)->double {return 0.0; };

	// note that lambdas w capture lists cannot be casted to function ptrs
	// thus we need the following cast: 
	static auto lowerTLambdaCast = lowerTLambda;
	double (*lowerTLambdaCastPtr)(double) = [](double x) { return lowerTLambdaCast(x); };
	static auto upperXLambdaCast = upperXLambda;
	double (*upperXLambdaCastPtr)(double) = [](double tau) { return upperXLambdaCast(tau); };

	// define the scheme for the PDE
	double a = vol * vol / 2.0; // this is the coeff for the simplified pde
	point xBounds{ lowerBoundX , upperBoundX };
	point tBounds{ 0.0, timeToMaturity };

	// solve the simplified heat equation
	FTCS scheme{ a , xBounds, tBounds, args.m_numXSteps, args.m_numTSteps, lowerXLambda, upperXLambdaCastPtr, lowerTLambdaCastPtr };
	scheme.fit();
	Interpolator2D inter{ scheme.getXVec(), scheme.getTVec(), scheme.getGrid() };

	// return the solution in our solution wrapper
	return BlackScholesPDESolution{ inter, vol, strike, riskFreeRate, timeToMaturity };
}

double BlackScholesPDESolution::operator()(double spot, double tau) const
{
	double x = std::log(spot) - (m_riskFreeRate - m_vol * m_vol / 2.0) * (m_timeToMaturity - tau);
	return std::exp(-m_riskFreeRate * tau) * m_xGrid(x, tau); 
}
