#pragma once
#include <vector>
#include <numeric>
#include "../Distribution/NormalDistribution.h"

// pure abstract class
class TimeSeries
{

public: 

	virtual std::vector<double> generate(unsigned long n) = 0; 
	virtual bool isStationary() const = 0; 
	virtual double var() const = 0; 
	virtual double getAutoCorrelation(int lag) const = 0; 

	/*
	
	// theoretical values given model params
	virtual double getAutoCovariance(int lag) const = 0; 
	virtual double getPartialAutoCorrelation(int lag) = 0; 
	
	// vector versions of the above functions 
	virtual std::vector<double> getAutoCovariance(int startIdx, int endIdx) = 0; 
	virtual std::vector<double> getAutoCorrelation(int startIdx, int endIdx) = 0;
	virtual std::vector<double> getPartialAutoCorrelation(int startIdx, int endIdx) = 0;
	*/
};