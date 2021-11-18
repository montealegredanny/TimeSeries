#include "examples.h"

void examplePolynomial()
{
	// create the polynomial x^2 + 5x + 6
	//evaluate it at some points and find its roots 
	Polynomial poly{ {6.,5.,1.} };
	std::cout << "============= Example # 1 for polynomials ============= \n\n";
	std::cout << "f(x) = " << poly << std::endl;
	std::cout << "f(x) evaluated at some points...\n"; 
	std::cout << "f(1) = " << poly(1.0) << std::endl;
	std::cout << "f(0) = " << poly(0.) << std::endl;

	std::cout << "roots of f(x) :\n"; 
	std::vector<Root> roots = poly.findRoots();
	for (Root& rt : roots)
	{
		std::cout << rt ;
	}
	std::cout << std::endl;
}

void examplePolynomial2()
{
	// create the polynomial x^2 + 1 
	// evaluate it and find its complex roots. 
	std::cout << "============= Example # 2 for polynomials ============= \n\n";
	Polynomial poly{ {1.0, 0.0, 1.0} }; 
	std::cout << "f(x) = " << poly << std::endl;
	std::cout << "f(x) evaluated at some points...\n";
	std::cout << "f(1) = " << poly(1.0) << std::endl;
	std::cout << "f(0) = " << poly(0.) << std::endl;
	std::cout << "roots of f(x) :\n";
	std::vector<Root> roots = poly.findRoots();
	for (Root& rt : roots)
	{
		std::cout << rt;
	}
	std::cout << std::endl;
}

void exampleGaussianElimination()
{
	/*
	Consider the system of equations:
	x_1 + x_2 = 1
	i * x_1 - i * x_2 = 2*sqrt(2)

	Then the solutions are
	x_1 = (1/2) - sqrt(2) i
	x_2 = (1/2) + sqrt(2) i
	*/
	std::cout << "============= Example # 1 for gauss elimination ============= \n\n";
	std::cout << "Solving the following set of equations .. \n";
	std::cout << "x_1 + x_2 = 1\n";
	std::cout << "i * x_1 - i * x_2 = 2*sqrt(2) \n";

	std::vector<std::vector<std::complex<double>>> A;
	A.push_back(std::vector<std::complex<double>> {std::complex<double> {1.0, 0.0}, std::complex<double> {1.0, 0.0}, std::complex<double> {1.0, 0.0}});
	A.push_back(std::vector<std::complex<double>> {std::complex<double> {0.0, 1.0}, std::complex<double> {0.0, -1.0}, std::complex<double> {2 * sqrt(2.0), 0.0}});
	std::vector<std::complex<double>> solutions = GaussElimination(A);
	
	std::cout << "solutions .... (in order ):\n";
	for (auto& val : solutions)
	{
		std::cout << val << std::endl;
	}

}

void exampleSolveMatrixEquation()
{
	/*
	we are going to solve the following system	
	
	3x -2y + 5z  =  2

	4x - 7y - z  =  19

	5x - 6y + 4z  =  13

	which gives us : x = 1, y = -2, z = -1

	we set them up as a system AX = b 
	*/
	std::cout << "============= Example # 1 for solving matrix equation ============= \n\n";
	Matrix A{ {{3., -2., 5.}, {4., -7., -1.}, {5., -6., 4.}} };
	Matrix b{ {2., 19., 13.} }; // note that this gets created as a 3 by 1 matrix. 

	std::cout << "solving the system of equations AX = b. Where: \n"; 
	std::cout << "A = \n" << A << std::endl;
	std::cout << "b = \n" << b << std::endl;

	std::cout << "Solutions = " << std::endl; 

	std::vector<double> solutions = solveMatrixEqtn(A, b); 
	for (double& sol : solutions)
	{
		std::cout << sol << std::endl; 
	}
}

void exampleAR()
{
	std::cout << "============= Example for an AR(6) process =============\n";
	double sigma = 2.0;
	std::vector<double> coeffs{ 0.225 , -0.8, 0.5, -0.27, 0.01, -0.2 };
	AR arProcess{ coeffs, sigma };
	for (size_t idx = 0; idx < coeffs.size(); idx++)
	{
		std::cout << "phi_" << idx + 1 << " = " << coeffs[idx] << std::endl;
	}
	std::cout << std::endl;
	exampleTimeSeries(arProcess);
}

void exampleAR2()
{
	std::cout << "============= Example for an AR(2) process =============\n";
	double sigma = 2.0;
	std::vector<double> coeffs{ -1.4, -0.45 };
	AR arProcess{ coeffs, sigma };
	for (size_t idx = 0; idx < coeffs.size(); idx++)
	{
		std::cout << "phi_" << idx + 1 << " = " << coeffs[idx] << std::endl;
	}
	std::cout << std::endl;
	exampleTimeSeries(arProcess);
}

void exampleMA()
{
	std::cout << "============= Example for an MA(1) process =============\n";
	double sigma = 2.0;
	std::vector<double> coeffs{ 0.9 };
	MA maProcess{ coeffs, sigma };
	for (size_t idx = 0; idx < coeffs.size(); idx++)
	{
		std::cout << "theta_" << idx + 1 << " = " << coeffs[idx] << std::endl;
	}
	std::cout << std::endl;
	exampleTimeSeries(maProcess);
}

void exampleMA2()
{
	std::cout << "============= Example for an MA(3) process =============\n";
	double sigma = 2.0;
	std::vector<double> coeffs{ 0.9, -0.85, 0.5 };
	MA maProcess{ coeffs, sigma };
	for (size_t idx = 0; idx < coeffs.size(); idx++)
	{
		std::cout << "theta_" << idx + 1 << " = " << coeffs[idx] << std::endl;
	}
	std::cout << std::endl;
	exampleTimeSeries(maProcess);
}

void exampleTimeSeries(TimeSeries& ts)
{
	std::cout << "is the process stationary ? " << ts.isStationary() << std::endl;
	std::vector<double> sample{ ts.generate(50000)};
	std::cout << "Variance (theoretically) = " << ts.var() << std::endl;
	std::cout << "Variance (empirically)   = " << DataAnalysis::var(sample) << std::endl;

	for (int idx = 1; idx < 6; idx++)
	{
		std::cout << "ACF (theoretically) lag(" << idx << ") = " << ts.getAutoCorrelation(idx) << std::endl;
		std::cout << "ACF (empirically) lag(" << idx << ") = " << DataAnalysis::acf(sample, idx) << std::endl;
	}
	std::cout << std::endl;

	for (int idx = 1; idx < 6; idx++)
	{
		std::cout << "PACF (theoretically) lag(" << idx << ") = " << ts.getPartialAutoCorrelation(idx) << std::endl;
	}
}

void exampleOLS()
{
	std::cout << "============= Example for OLS regression =============\n";
	Matrix Z({ -2., -1., 0., 1., 2. });
	Z = Z.transpose();
	Matrix X{ {-4., -2., 0., 2., 4. } };
	std::cout << "regressing X ~ Z + 1 \n";
	std::cout << "with X = " << X.transpose();
	std::cout << "and Z = " << Z;
	Matrix betas = OLS::runRegression(X, Z);
	std::cout << "betas = " << betas.transpose() << std::endl;
}