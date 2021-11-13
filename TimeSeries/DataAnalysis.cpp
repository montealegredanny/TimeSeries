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

double DataAnalysis::autoCovariance(std::vector<double> series, int lag)
{
	double mean = DataAnalysis::mean(series); 
	double total = 0.0; 

	for (size_t idx = 0; idx < series.size() - lag; idx++)
	{
		total += ((series[idx] - mean) * (series[idx + lag] - mean));
	}
	return total / series.size();
}

std::vector<double> DataAnalysis::autoCovariance(std::vector<double> series, int startLag, int endLag)
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
