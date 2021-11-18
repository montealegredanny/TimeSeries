#include "TimeSeries.h"

std::vector<double> TimeSeries::getAutoCovariance(int startIdx, int endIdx)
{
	std::vector<double> covariances;
	covariances.reserve(endIdx - startIdx);
	for (int curr = startIdx; curr <= endIdx; curr++)
	{
		covariances.push_back(this->getAutoCovariance(curr));
	}
	return covariances;
}

std::vector<double> TimeSeries::getAutoCorrelation(int startIdx, int endIdx)
{
	std::vector<double> correlations;
	double var = this->var();
	correlations.reserve(endIdx - startIdx);
	for (int curr = startIdx; curr <= endIdx; curr++)
	{
		correlations.push_back(this->getAutoCovariance(curr) / var);
	}
	return correlations;
}

double TimeSeries::getPartialAutoCorrelation(int lag)
{
	// first we find the set of correlations. 
	std::vector<double> autocorrelations = this->getAutoCorrelation(0, lag);
	if (lag == 1)
	{
		return autocorrelations[lag];
	}

	// set up the matrices for the determinants 
	Matrix numeratorMatrix(lag, lag, 0.0);
	Matrix denominatorMatrix(lag, lag, 0.0);

	for (int rowIdx = 0; rowIdx < lag; rowIdx++)
	{
		for (int colIdx = 0; colIdx < lag - 1; colIdx++)
		{
			numeratorMatrix.set(rowIdx, colIdx, autocorrelations[abs(rowIdx - colIdx)]);
			denominatorMatrix.set(rowIdx, colIdx, autocorrelations[abs(rowIdx - colIdx)]);
		}
		numeratorMatrix.set(rowIdx, lag - 1, autocorrelations[rowIdx + 1]);
		denominatorMatrix.set(rowIdx, lag - 1, autocorrelations[lag - 1 - rowIdx]);
	}


	return numeratorMatrix.determinant() / denominatorMatrix.determinant();
}
