#pragma once
#include <vector>
#include <iostream>
#include <complex>

class ComplexPolynomial
{
	public: 
		ComplexPolynomial(std::vector<std::complex<double>> coefficients);
		template <typename T> std::complex<double> operator()(T x) const;
		int getDegree() const;
		std::vector<std::complex<double>> getCoeffs() const;
	private: 
		std::vector<std::complex<double>> m_coeffs;
		int m_degree;
};


template<typename T>
inline std::complex<double> ComplexPolynomial::operator()(T x) const
{
	std::complex<double> val = 0.0;
	for (int idx = 0; idx <= m_degree; idx++)
	{
		val += (m_coeffs[idx] * pow(x, idx));
	}
	return val;
}
