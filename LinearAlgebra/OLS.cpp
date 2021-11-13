#include "OLS.h"

Matrix OLS::runRegression(const std::vector<double>& X, const std::vector<std::vector<double>>& Z, bool add_intercept)
{
	std::vector<std::vector<double>> v_Z; 
	size_t n = X.size(); 

	if (add_intercept)
	{
		v_Z.push_back(std::vector<double>(n, 1.0));
	}
	for (std::vector<double> row : Z) 
	{
		v_Z.push_back(row);
	}
	Matrix m_Z(v_Z);

	std::vector<double> beta = solveMatrixEqtn(m_Z * m_Z.transpose(), m_Z * Matrix(X));
	return Matrix(beta);
}

Matrix OLS::runRegression(const Matrix& X, const Matrix& Z, bool add_intercept)
{
	// unravel the X matrix into a 1-dim vector 
	const int n = X.getNumRows();
	std::vector<double> v_X(n); 
	for (int idx = 0; idx < n ; idx++)
	{
		v_X[idx] = X.get(idx, 0);
	}
	return runRegression(v_X, Z.getData(), add_intercept);
}

Matrix OLS::runRegression(const std::vector<double>& X, const Matrix& Z, bool add_intercept)
{
	return runRegression(X, Z.getData(), add_intercept);
}

