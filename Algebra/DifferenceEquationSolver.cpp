#include "DifferenceEquationSolver.h"

DifferenceEquationSolver::DifferenceEquationSolver(DifferenceEquation& diffEqtn)
{
	// we create the char polynomial of the diff equation 
	std::vector<double> diffEqtnCoeffs = diffEqtn.getCoeffs(); 
	std::vector<double> polyCoeffs;
	for (int idx = diffEqtn.getDegree() - 1; idx >= 0; idx--)
	{
		polyCoeffs.push_back(-1.0* diffEqtnCoeffs[idx]);
	}
	polyCoeffs.push_back(1.0);
	m_charPolynomial = Polynomial{ polyCoeffs } ;
	
	m_degree = diffEqtn.getDegree();
	m_initConditions = diffEqtn.getInitConditions();
}

void DifferenceEquationSolver::solve()
{
	// first get the roots of the char polynomial
	std::cout << "char poly = " << m_charPolynomial << std::endl; 
	std::vector<Root> roots = m_charPolynomial.findRoots();
	std::cout << "roots for the polynomial..." << std::endl; 
	for (auto& rt : roots)
	{
		std::cout << rt << std::endl;
	}
	
	// second, set up the set of equations
	std::vector<std::vector<std::complex<double>>> augmentedMatrix; 
	for (int j = 0; j < m_degree; j++)
	{
		std::vector<std::complex<double>> row; 
		for (const Root& rt : roots)
		{
			std::complex<double> rootVal = rt.getValue();
			for (unsigned int m = 0; m < rt.getMultiplicity(); m++)
			{
				row.push_back(pow(rootVal, j) * (pow(j, m))); 
			}
		}
		row.push_back(m_initConditions[j]);
		augmentedMatrix.push_back(row); 
	}

	// third -- using Guass elimination we will solve for the coefficients: 
	std::vector<std::complex<double>> v_coeffs = GaussElimination(augmentedMatrix); 

	// last -- we pack them into a vector of SolutionTerms: 
	std::vector<SolutionTerm> v_solutionTerms; 
	unsigned int offset = 0;
	for (Root& rt : roots)
	{
		std::vector<std::complex<double>> root_coeffs; 
		for (unsigned int m = 0; m < rt.getMultiplicity(); m++)
		{
			root_coeffs.push_back(v_coeffs[offset + m]);
		}
		v_solutionTerms.push_back(SolutionTerm{ ComplexPolynomial{root_coeffs}, rt });
		offset += rt.getMultiplicity(); 
	}
	
	for (int n = 0; n < 20; n++)
	{
		std::complex<double> total = 0.0; 
		for (SolutionTerm& st : v_solutionTerms)
		{
			total += st(n); 
		}
		if (abs(total.imag()) > 1e-6)
		{
			std::cout << "ERROR! WE GOT A COMPLEX NUMBER IN THE SERIES!\n";
		}
		double d_total = total.real(); 
		d_total = abs(d_total) > 1e-6 ? d_total : 0;
		std::cout << n << " : " << d_total << std::endl;
	}
}

std::complex<double> SolutionTerm::operator()(unsigned int n) const
{
	return m_poly(n) * pow(m_root.getValue(), n); 

}
