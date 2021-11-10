#include "ComplexPolynomial.h"

ComplexPolynomial::ComplexPolynomial(std::vector<std::complex<double>> coefficients)
{
	m_coeffs = coefficients;
	m_degree = int(m_coeffs.size()) - 1;
}

int ComplexPolynomial::getDegree() const
{
	return m_degree;
}

std::vector<std::complex<double>> ComplexPolynomial::getCoeffs() const
{
	return m_coeffs;
}

