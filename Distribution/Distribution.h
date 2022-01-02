#pragma once
# include <vector>
# include <random>

class Distribution
{
public: 
	virtual double generate() = 0 ; 
	virtual std::vector<double> generate(int n) = 0;
	// todo -- implement pdf and cdf 
};