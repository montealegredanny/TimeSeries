#pragma once
#include <vector>
#include <complex> 
#include <iostream>

std::vector<std::complex<double>> GaussElimination(std::vector < std::vector<std::complex<double>>> A); 
std::vector<double> GaussElimination(std::vector< std::vector<double> > A);
void testGaussianElimination();
