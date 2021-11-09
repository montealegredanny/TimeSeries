#pragma once
#include <vector>
#include <iostream>
#include <complex>


class Polynomial
{
	public:
		Polynomial(std::vector <double> coefficients);
		friend std::ostream &operator<<(std::ostream& os, const Polynomial & poly);
		std::vector<std::complex<double>> findRoots(const double precision, const unsigned long maxIter) const;
		template <typename T> T operator()(T x) const;
		int getDegree() const;
		std::vector<double> getCoeffs() const;

	private: 
		std::vector<double> m_coeffs;
		int m_degree; 
};

namespace AlgebraHelper
{
	double maxDistance(const std::vector<std::complex<double>>& v1, const std::vector<std::complex<double>>& v2);
	std::vector<std::complex<double>> rootsUnit(const unsigned int n);
	std::vector<std::complex<double>> iterateDurandKerner(const Polynomial& poly, std::vector<std::complex<double>>& currentSolutions);
	inline double normSquare(std::complex<double> v) { return v.real() * v.real() + v.imag() * v.imag(); };
}

template<typename T>
inline T Polynomial::operator()(T x) const
{
	T val = 0.0;
	for (int idx = 0; idx <= m_degree; idx++)
	{
		val += (m_coeffs[idx] * pow(x, idx));
	}
	return val;
}
