#pragma once
# include "Matrix.h"
# include "GaussElimination.h"

/*
Perform the regression x_t = beta_0 + beta_1 z_{ 1t } + ... + beta_q z_{ qt }

Z is a matrix shape(q, n) (note that later it will be q + 1 once we fit the intercept).
X is an a vector of size n. 
*/
namespace OLS
{
	std::vector<double> runRegression(std::vector<double> X, Matrix Z, bool add_intercept = true);
}