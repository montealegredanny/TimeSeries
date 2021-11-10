#pragma once
# include "Polynomial.h"
# include "ComplexPolynomial.h"
# include "Root.h"
# include "DifferenceEquations.h"
# include "GaussElimination.h"

struct SolutionTerm
{
	SolutionTerm(ComplexPolynomial p, Root r) : m_poly(p), m_root(r) {};
	ComplexPolynomial m_poly;
	Root m_root; 
	std::complex<double> operator()(unsigned int n) const; 
};

class DifferenceEquationSolver
{
	public: 
		DifferenceEquationSolver(DifferenceEquation& diffEqtn);
		void solve(); 

	private:
		Polynomial m_charPolynomial; 
		int m_degree; 
		std::vector<double> m_initConditions; 
		std::vector<SolutionTerm> m_solution;

};
