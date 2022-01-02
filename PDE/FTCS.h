#pragma once
#include <vector>
#include <map>
#include <assert.h>
#include <iostream>

/*
Solve the heat equation of the form 
\frac{\partial f}{\partial t} = a \frac{\partial^2 f}{\partial x^2}

we pass in the value for a, three functions which gives us the values at the boundaries, 
and some bounds and number of points that will define the grid. 

*/

typedef std::pair<double, double> point;

class FTCS
{
	public:
		FTCS(double a, point xBounds, point tBounds, long xSteps, long tSteps, double (*lowerXLambda)(double) , double (*upperXLambda)(double), double (*lowerTLambda)(double));
		void fit(); 
		std::map<point, double> getGrid() const; 
		std::vector<double> getXVec() const;
		std::vector<double> getTVec() const;
	private:
		double m_a; 
		double m_xMin; 
		double m_xMax; 
		double m_tMin; 
		double m_tMax; 
		long m_xSteps; 
		long m_tSteps;
		double m_deltaX; 
		double m_deltaT;
		std::vector<double> m_xVec; 
		std::vector<double> m_tVec;
		std::map<point, double> m_grid;
		double (*m_upperXLambda)(double);
		double (*m_lowerXLambda)(double);
		double (*m_lowerTLambda)(double);
};