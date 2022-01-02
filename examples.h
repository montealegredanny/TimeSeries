#pragma once
# include "Algebra/Polynomial.h"
# include "LinearAlgebra/GaussElimination.h"
# include <iostream>
# include "TimeSeries/AR.h"
# include "TimeSeries/MA.h"
# include "TimeSeries/DataAnalysis.h"
# include "LinearAlgebra/OLS.h"
# include "Algebra/Interpolator2D.h"
# include "PDE/BlackScholesPDE.h"
# include "PDE/FTCS.h"
# define _USE_MATH_DEFINES
# include <math.h>


void examplePolynomial();
void examplePolynomial2();
void exampleGaussianElimination();
void exampleSolveMatrixEquation(); 
void exampleTimeSeries(TimeSeries & ts);
void exampleAR(); 
void exampleAR2();
void exampleMA();
void exampleMA2();
void exampleOLS();
void exampleFitAR();
void exampleInterpolator2D();
void exampleHeatEquation(); 
void exampleBSPDE(); 



