#pragma once
#include <vector>
#include <complex> 
#include <iostream>
#include "Matrix.h"

std::vector<std::complex<double>> GaussElimination(std::vector < std::vector<std::complex<double>>> A); 
std::vector<double> GaussElimination(std::vector< std::vector<double> > A);
void testGaussianElimination();

// solves the equation Ax = b 
std::vector<double> solveMatrixEqtn(std::vector<std::vector<double>> A, std::vector<double> b);
std::vector<double> solveMatrixEqtn(Matrix A, std::vector<double> b);

