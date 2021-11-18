#pragma once 
# include "Algebra/DifferenceEquationSolver.h"
# include "TimeSeries/AR.h"
# include "TimeSeries/DataAnalysis.h"
# include "LinearAlgebra/Matrix.h"
# include "LinearAlgebra/OLS.h"
# include "examples.h"
# include "TimeSeries/MA.h"

void exampleMA()
{
	MA maProcess{ {-.85,0.6}, .70 };
	auto sample = maProcess.generate(50000);
	std::cout << maProcess.var() << std::endl;
	std::cout << DataAnalysis::var(sample) << std::endl;

	std::cout << DataAnalysis::autoCovariance(sample, 1) << std::endl;
	std::cout << maProcess.getAutoCovariance(1) << std::endl;

	std::cout << DataAnalysis::autoCovariance(sample, 2) << std::endl;
	std::cout << maProcess.getAutoCovariance(2) << std::endl;

	std::cout << DataAnalysis::autoCovariance(sample, 3) << std::endl;
	std::cout << maProcess.getAutoCovariance(3) << std::endl;
	/*
	std::cout << DataAnalysis::acf(sample, 0) << std::endl;
	std::cout << DataAnalysis::acf(sample, 1) << std::endl;
	std::cout << DataAnalysis::acf(sample, 2) << std::endl;
	std::cout << DataAnalysis::acf(sample, 3) << std::endl;
	std::cout << DataAnalysis::acf(sample, 4) << std::endl;

	std::cout << "PACF \n"; 
	std::cout << DataAnalysis::pacf(sample, 0) << std::endl;
	std::cout << DataAnalysis::pacf(sample, 1) << std::endl;
	std::cout << DataAnalysis::pacf(sample, 2) << std::endl;
	std::cout << DataAnalysis::pacf(sample, 3) << std::endl;
	std::cout << DataAnalysis::pacf(sample, 4) << std::endl;
	
	*/
}

int main()
{	
	
	examplePolynomial(); 
	examplePolynomial2();
	exampleGaussianElimination();
	exampleSolveMatrixEquation();
	exampleOLS(); 
	exampleAR();
	exampleAR2();
	
	exampleMA();
	return 0; 
}
