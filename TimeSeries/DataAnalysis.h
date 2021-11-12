# pragma 
# include <vector>
# include <numeric>

namespace DataAnalysis
{
	// variance & mean
	double var(const std::vector<double>& series); 
	double mean(const std::vector<double>& series);

	// autocovariance functions 
	double autoCovariance(std::vector<double> series); 
	std::vector<double> autoCovariance(std::vector<double> series, int lag, int startIdx = 0, int endIdx = 0);

	// autocorrelation functions
	double acf(std::vector<double> series, int lag); 
	std::vector<double> acf(std::vector<double> series, int lag, int startIdx = 0, int endIdx = 0); 

	// cross covariance 
	double crossCovariance(std::vector<double> xSeries, std::vector<double> ySeries, int lag); 
	std::vector<double> crossCovariance(std::vector<double> xSeries, std::vector<double> ySeries, int lag, int startIdx = 0, int endIdx = 0 ); 

	// cross correlation function
	double ccf(std::vector<double> xSeries, std::vector<double> ySeries, int lag);
	std::vector<double> ccf(std::vector<double> xSeries, std::vector<double> ySeries, int lag, int startIdx = 0, int endIdx = 0);

}