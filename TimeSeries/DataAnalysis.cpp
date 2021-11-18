#include "DataAnalysis.h"

double DataAnalysis::var(const std::vector<double>& series)
{
	double secondMoment = 0.0;
	double firstMoment = 0.0;
	for (const double& x : series)
	{
		secondMoment += x * x;
		firstMoment += x;
	}
	secondMoment /= series.size();
	firstMoment /= series.size();
	return secondMoment - firstMoment * firstMoment;
}

double DataAnalysis::mean(const std::vector<double>& series)
{
	double total = 0.0;
	for (const double& x : series)
	{
		total += x;
	}
	return total / series.size();
}

double DataAnalysis::autoCovariance(const std::vector<double>& series, const int lag)
{
	double mean = DataAnalysis::mean(series); 
	double total = 0.0; 

	for (size_t idx = 0; idx < series.size() - lag; idx++)
	{
		total += ((series[idx] - mean) * (series[idx + lag] - mean));
	}
	return total / series.size();
}


std::vector<double> DataAnalysis::autoCovariance(const std::vector<double>& series, const  int startLag, const int endLag )
{
	double mean = DataAnalysis::mean(series); 
	std::vector<double> v_covs;

	for (int lag = startLag; lag <= endLag; lag++)
	{
		double total = 0.0; 
		for (int idx = 0; idx < series.size() - lag; idx++)
		{
			total += ((series[idx] - mean) * (series[idx + lag] - mean));
		}
		v_covs.push_back(total / series.size()); 
	}
	return v_covs;
}

double DataAnalysis::acf(const std::vector<double>& series, const int lag)
{
	double variance = DataAnalysis::var(series); 
	return DataAnalysis::autoCovariance(series, lag) / variance;
}

std::vector<double> DataAnalysis::acf(const std::vector<double>& series, const int startLag, const int endLag)
{
	std::vector<double> covariances = DataAnalysis::autoCovariance(series, startLag, endLag);
	double variance = DataAnalysis::var(series);
	for (double& cov : covariances)
	{
		cov /= variance;
	}
	return covariances;
}

// todo -- implement the cross correlation functions~
double DataAnalysis::crossCovariance(const std::vector<double>& xSeries, const std::vector<double>& ySeries, const int lag)
{
	return 0.0;
}

std::vector<double> DataAnalysis::crossCovariance(const std::vector<double>& xSeries, const std::vector<double>& ySeries, const int startLag, const int endLag)
{
	return std::vector<double>();
}

double DataAnalysis::ccf(const std::vector<double>& xSeries, const std::vector<double>& ySeries, const int lag)
{
	return 0.0;
}

std::vector<double> DataAnalysis::ccf(const std::vector<double>& xSeries, const std::vector<double>& ySeries, const int startLag, const int endLag)
{
	return std::vector<double>();
}

double DataAnalysis::pacf(const std::vector<double>& series, const int lag)
{
	// first we find the set of correlations. 
	std::vector<double> autocorrelations = DataAnalysis::acf(series, 0, lag);
	if (lag == 1)
	{
		return autocorrelations[lag];
	}

	// set up the matrices for the determinants 
	Matrix numeratorMatrix(lag, lag, 0.0) ; 
	Matrix denominatorMatrix(lag, lag, 0.0); 

	for (int rowIdx = 0; rowIdx < lag ; rowIdx++)
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
