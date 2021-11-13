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
	Matrix runRegression(const std::vector<double>& X, const std::vector<std::vector<double>>& Z, bool add_intercept = true); // main function the others end up calling
	Matrix runRegression(const Matrix& X, const Matrix & Z, bool add_intercept = true);
	Matrix runRegression(const std::vector<double>& X, const Matrix& Z, bool add_intercept = true);
}