#pragma once 
# include "Algebra/DifferenceEquationSolver.h"
# include "TimeSeries/AR.h"
# include "TimeSeries/DataAnalysis.h"
# include "LinearAlgebra/Matrix.h"
# include "LinearAlgebra/OLS.h"

template <typename T>
void print(T x)
{
	for (auto val : x)
	{
		std::cout << val << std::endl;
	}
}

void exampleAR2()
{
	// example of the acf of an AR(2) process. 
	// we can work out that the first two values for ACF are 1.0 and phi_1 / (1-phi_2). 
	// then the next values will be given by rho_h = phi_1 * rho_{h-1} + phi_2 * rho_{h-2}
	// then we can compute the ACF via a difference equation! 
	double phi1 = 0.9;
	double phi2 = -0.8; 
	double phi3 = 0.5; 
	double sigma = 1.0; 
	AR arProcess{ {phi1/4.0,phi2, phi3, phi2 /3.0, 0.01, -0.2}, sigma };
	std::cout << arProcess.isStationary() << std::endl;
	print(DataAnalysis::acf(arProcess.generate(50000), 0, 5));
	//std::cout << "------------------\n";
	//DifferenceEquation diffEqtn{ {phi1, phi2} , {1.0, phi1 / (1. - phi2) }};

	//print(diffEqtn.generate(11)); 

	arProcess.getAutoCorrelation(0);
}
int main()
{
	exampleAR2();
	double sigma = 2.0;
	double c = 0.95;
	AR test1{ std::vector<double>{1.73574, -(0.95* 0.95)},sigma };
	auto series = test1.generate(10000);
	// we are going to regress x_t against x_{t-1} 
	auto x_t = Matrix(std::vector<double>(series.begin() + 1, series.end())); // this is X
	auto x_lag = Matrix(std::vector<double>(series.begin(), series.end() - 1)); // this is Z
	x_lag = x_lag.transpose();

	//std::cout << OLS::runRegression(x_t, x_lag); // note that it prints the 0 intercept and the c intercept
	return 0; 
}
