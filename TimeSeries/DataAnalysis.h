# pragma 
# include <vector>
# include <numeric>

namespace DataAnalysis
{
	// variance & mean
	double var(const std::vector<double>& series); 
	double mean(const std::vector<double>& series);

	// autocovariance functions 
	double autoCovariance(const std::vector<double>& series, const  int lag);
	std::vector<double> autoCovariance(const std::vector<double>& series, const  int startLag, const int endLag);

	// autocorrelation functions
	double acf(const std::vector<double>& series, const  int lag);
	std::vector<double> acf(const std::vector<double>& series, const  int startLag, const  int endLag);

	// cross covariance 
	double crossCovariance(const std::vector<double>& xSeries, const  std::vector<double>& ySeries, const  int lag);
	std::vector<double> crossCovariance(const std::vector<double>& xSeries, const  std::vector<double>& ySeries, const  int startLag, const  int endLag);

	// cross correlation function
	double ccf(const std::vector<double>& xSeries, const  std::vector<double>& ySeries, const  int lag);
	std::vector<double> ccf(const std::vector<double>& xSeries, const  std::vector<double>& ySeries, const  int startLag, const  int endLag);

}