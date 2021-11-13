/*
Implementation of Gaussian elimination for a set of linear equations in the complex field. 
Credit to https://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/
*/

#include "GaussElimination.h"

inline double normSq(std::complex<double> x) 
{
    return x.real() * x.real() + x.imag() * x.imag();
}

std::vector<std::complex<double>> GaussElimination(std::vector<std::vector<std::complex<double>>> A)
{
    size_t n = A.size();

    for (size_t i = 0; i < n; i++) {
        // Search for norm maximum in this column
        double maxEl = normSq(A[i][i]);
        size_t maxRow = i;
        for (size_t k = i + 1; k < n; k++) {
            if (normSq(A[k][i]) > maxEl) {
                maxEl = normSq(A[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (size_t k = i; k < n + 1; k++) {
            std::complex<double> tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (size_t k = i + 1; k < n; k++) {
            std::complex<double> c = -A[k][i] / A[i][i];
            for (size_t j = i; j < n + 1; j++) {
                if (i == j) {
                    A[k][j] = 0;
                }
                else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    std::vector<std::complex<double>> x(n);
    for (int i = int(n - 1); i >= 0; i--) {
        x[i] = A[i][n] / A[i][i];
        for (int k = i - 1; k >= 0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}

std::vector<double> GaussElimination(std::vector< std::vector<double> > A) {
    int n = int(A.size());

    for (int i = 0; i < n; i++) {
        // Search for maximum in this column
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k = i; k < n + 1; k++) {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k = i + 1; k < n; k++) {
            double c = -A[k][i] / A[i][i];
            for (int j = i; j < n + 1; j++) {
                if (i == j) {
                    A[k][j] = 0;
                }
                else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = A[i][n] / A[i][i];
        for (int k = i - 1; k >= 0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}

//TODO -- move to unit testing 
void testGaussianElimination()
{
    /*
    Consider the system of equations: 
    x_1 + x_2 = 1
    i * x_1 - i * x_2 = 2*sqrt(2)
    
    Then the solutions are 
    x_1 = (1/2) - sqrt(2) i 
    x_2 = (1/2) + sqrt(2) i 
    */

    // create the augmented matrix: 
    std::vector<std::vector<std::complex<double>>> A; 

    // first row: 
    A.push_back(std::vector<std::complex<double>> {std::complex<double> {1.0, 0.0}, std::complex<double> {1.0, 0.0}, std::complex<double> {1.0, 0.0}});
    
    // second row: 
    A.push_back(std::vector<std::complex<double>> {std::complex<double> {0.0, 1.0}, std::complex<double> {0.0, -1.0}, std::complex<double> {2 * sqrt(2.0), 0.0}});

    std::vector<std::complex<double>> solutions = GaussElimination(A); 

    for (auto& val : solutions) 
    {
        std::cout << val << std::endl;
    }

}

std::vector<double> solveMatrixEqtn(const std::vector<std::vector<double>>& A, const std::vector<double>& b)
{
    // create the augmented matrix and call gauss elimination 
    std::vector<std::vector<double>> augmentedMat; 
    
    for (size_t r_idx = 0; r_idx < A.size(); r_idx++)
    {
        std::vector<double> rowCopy(A[r_idx]); 
        rowCopy.push_back(b[r_idx]);
        augmentedMat.push_back(rowCopy);
    }
    return GaussElimination(augmentedMat);
}

std::vector<double> solveMatrixEqtn(const Matrix& A, const Matrix& b)
{
    std::vector<double> v_b; 
    for (int idx = 0; idx < b.getNumRows(); idx++)
    {
        v_b.push_back(b.get(idx, 0));
    }

    return solveMatrixEqtn(A.getData(), v_b);
}

std::vector<double> solveMatrixEqtn(const Matrix& A, const std::vector<double>& b)
{
    return solveMatrixEqtn(A.getData(), b); 
}
