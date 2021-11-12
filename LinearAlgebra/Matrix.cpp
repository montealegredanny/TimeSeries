# include "Matrix.h"
#include <assert.h>

// constructor
// note that we make a copy of data when the function is invoked 
// and then we can move the data into the vector (so a total of one copy). 
Matrix::Matrix(std::vector<std::vector<double>> mat)
{
    m_data = std::move(mat);
}

// copy constructor
// note that we do not use move here since we want to leave other untouched. 
Matrix::Matrix(const Matrix& other)
{
    m_data = std::vector<std::vector<double>>(other.m_data);
}

// move constructor
// receives an r value reference
Matrix::Matrix(Matrix&& other) noexcept
{
    m_data = std::move(other.m_data);
    // other.data is now some giberish legal data (i.e., we can read it, but its some random non-sense).
}

// copy assigment
Matrix& Matrix::operator=(const Matrix& other)
{
    if (&other != this)
    {
        m_data = other.m_data;
    }
    return *this;
}

// move assigment 
Matrix& Matrix::operator=(Matrix&& other) noexcept
{
    if (&other != this)
    {
        m_data = std::move(other.m_data);
        // other.data is now some giberish legal data (i.e., we can read it, but its some random non-sense).
    }
    return *this;
}

// destructor
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
