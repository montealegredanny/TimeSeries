# include "Matrix.h"
#include <assert.h>

Matrix::Matrix(std::vector<std::vector<double>> mat)
{
    m_data = std::move(mat);
}

Matrix::Matrix(const Matrix& other)
{
    m_data = std::vector<std::vector<double>>(other.m_data);
}

Matrix::Matrix(Matrix&& other) noexcept
{
    m_data = std::move(other.m_data);
    // other.data is now some giberish legal data (i.e., we can read it, but its some random non-sense).
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (&other != this)
    {
        m_data = other.m_data;
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
    if (&other != this)
    {
        m_data = std::move(other.m_data);
        // other.data is now some giberish legal data (i.e., we can read it, but its some random non-sense).
    }
    return *this;
}

Matrix::~Matrix()
{
    // do nothing..
}

int Matrix::getNumRows() const
{
    return int(m_data.size());
}

int Matrix::getNumCols() const
{
    return int (m_data[0].size());
}

double Matrix::get(int i, int j) const
{
    return (m_data)[i][j];
}

void Matrix::set(int i, int j, double val)
{
    (m_data)[i][j] = val;
}

Matrix Matrix::transpose() const
{
    std::vector<std::vector<double>> transposed; 
    int numRows = this->getNumRows();
    int numCols = this->getNumCols(); 

    for (int r_idx = 0; r_idx < numCols; r_idx++)
    {
        std::vector<double> row; 
        for (int c_idx = 0; c_idx < numRows; c_idx++)
        {
            row.push_back(this->get(c_idx, r_idx));
        }
        transposed.push_back(row);
    }
    return Matrix(transposed);
}


Matrix Matrix::MatMul(const Matrix& left, const Matrix& right)
{
    int dim1_left = left.getNumRows();
    int dim2_left = left.getNumCols();
    int dim1_right = right.getNumRows();
    int dim2_right = right.getNumCols();

    // assert that dim2 left == dim1 right. 
    assert(dim2_left == dim1_right);

    std::vector<std::vector<double>> rows;
    rows.reserve(dim1_left);

    for (int r_num = 0; r_num < dim1_left; r_num++)
    {
        std::vector<double> row;
        row.reserve(dim2_right);
        for (int c_num = 0; c_num < dim2_right; c_num++)
        {
            double val = 0;
            for (int inner = 0; inner < dim2_left; inner++)
            {
                val += left.get(r_num, inner) * right.get(inner, c_num);
            }
            row.push_back(val);
        }
        rows.push_back(row);
    }

    return Matrix(rows);
}

std::vector<std::vector<double>> Matrix::getData() const
{
    return m_data;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat)
{
    int numRows = mat.getNumRows(); 
    int numCols = mat.getNumCols(); 

    for (int r_idx = 0; r_idx < numRows; r_idx++)
    {
        for (int c_idx = 0; c_idx < numCols; c_idx++)
        {
            std::cout << mat.get(r_idx, c_idx) << " "; 
        }
        std::cout << std::endl;
    }
    return os;
}

Matrix operator*(const double scale, const Matrix& mat)
{
    int numRows = mat.getNumRows();
    int numCols = mat.getNumCols();

    std::vector<std::vector<double>> scaledMat;
    for (int r_idx = 0; r_idx < numRows; r_idx++)
    {
        std::vector<double> row;
        for (int c_idx = 0; c_idx < numCols; c_idx++)
        {
            row.push_back(mat.get(r_idx, c_idx) * scale);
        }
        scaledMat.push_back(row);
    }
    return Matrix(scaledMat);
}

Matrix operator*(const Matrix& mat, const double scale)
{
    return scale * mat;
}

Matrix operator+(const Matrix& left, const Matrix& right)
{
    assert(left.getNumCols() == right.getNumCols());
    assert(left.getNumRows() == right.getNumRows());

    int numRows = left.getNumRows();
    int numCols = left.getNumCols();

    std::vector<std::vector<double>> mat;
    for (int r_idx = 0; r_idx < numRows; r_idx++)
    {
        std::vector<double> row;
        for (int c_idx = 0; c_idx < numCols; c_idx++)
        {
            row.push_back(left.get(r_idx, c_idx) + right.get(r_idx, c_idx));
        }
        mat.push_back(row);
    }
    return Matrix(mat);
}

Matrix operator-(const Matrix& left, const Matrix& right)
{
    assert(left.getNumCols() == right.getNumCols());
    assert(left.getNumRows() == right.getNumRows());

    int numRows = left.getNumRows();
    int numCols = left.getNumCols();

    std::vector<std::vector<double>> mat;
    for (int r_idx = 0; r_idx < numRows; r_idx++)
    {
        std::vector<double> row;
        for (int c_idx = 0; c_idx < numCols; c_idx++)
        {
            row.push_back(left.get(r_idx, c_idx) - right.get(r_idx, c_idx));
        }
        mat.push_back(row);
    }
    return Matrix(mat);
}

Matrix operator*(const Matrix& left, const Matrix& right)
{
    return Matrix::MatMul(left, right);
}
