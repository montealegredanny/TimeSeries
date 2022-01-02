#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "..\LinearAlgebra\Matrix.h"
#include <assert.h>

class Interpolator2D
{
	public:
		Interpolator2D(const std::vector<double>& xVec, const std::vector<double>& yVec, const std::map<std::pair<double, double>, double>& grid)
			: m_xVec(xVec), m_yVec(yVec), m_grid(grid) {};
		
		double operator() (double x, double y) const; // this point gets interpolated
	private:
		const std::vector<double> m_xVec; 
		const std::vector<double> m_yVec; 
		const std::map<std::pair<double, double>, double> m_grid; 
		long findNeighbors(double val, const std::vector<double>& arr) const; // perform a binary search to find the neighbors in a given direction. 

};