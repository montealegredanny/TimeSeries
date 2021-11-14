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

int main()
{
	double sigma = 2.0;
	double c = -0.95;
	AR test1{ std::vector<double>{c},sigma };

	auto series = test1.generate(1000);

	print(DataAnalysis::acf(series, 0, 10));

	// we are going to regress x_t against x_{t-1} 
	auto x_t = Matrix(std::vector<double>(series.begin() + 1, series.end())); // this is X
	auto x_lag = Matrix(std::vector<double>(series.begin(), series.end() - 1)); // this is Z
	x_lag = x_lag.transpose();

	std::cout << OLS::runRegression(x_t, x_lag); // note that it prints the 0 intercept and the c intercept
	return 0; 
}
