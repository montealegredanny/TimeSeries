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
