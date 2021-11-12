#pragma once
#include "Distribution.h"

class NormalDistribution : public Distribution
{
	public: 
		NormalDistribution(double mean, double sigma) ;
		NormalDistribution(double mean) ;
		NormalDistribution() ;
		double generate(); 
		std::vector<double> generate(int n);
	private: 
		double m_mean; 
		double m_sigma; 
		std::default_random_engine m_generator;
		std::normal_distribution<double> m_distribution; 
};
