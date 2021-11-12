#include "NormalDistribution.h"

NormalDistribution::NormalDistribution(double mean, double sigma)
{
    m_mean = mean; 
    m_sigma = sigma;
    std::random_device rd; 
    m_generator = std::default_random_engine(rd());
    m_distribution = std::normal_distribution<double>{ mean, sigma };
}

NormalDistribution::NormalDistribution(double mean)
{
    NormalDistribution(mean, 1.0);
}

NormalDistribution::NormalDistribution()
{
    NormalDistribution(0.0, 1.0);
}

double NormalDistribution::generate()
{
    return m_distribution(m_generator);
}

std::vector<double> NormalDistribution::generate(int n)
{
    std::vector<double> randNumbers(n); 
    for (int idx = 0; idx < n; idx++)
        randNumbers[idx] = generate(); 
    return randNumbers;
}
