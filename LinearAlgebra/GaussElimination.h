#pragma once
#include <vector>
#include <complex> 
#include <iostream>
#include "Matrix.h"

std::vector<std::complex<double>> GaussElimination(std::vector < std::vector<std::complex<double>>> A); 
std::vector<double> GaussElimination(std::vector< std::vector<double> > A);

// solves the equation Ax = b 
std::vector<double> solveMatrixEqtn(const std::vector<std::vector<double>>& A, const std::vector<double>& b);
std::vector<double> solveMatrixEqtn(const Matrix& A, const Matrix& b); 
std::vector<double> solveMatrixEqtn(const Matrix& A, const std::vector<double>& b);

