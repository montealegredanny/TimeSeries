#pragma once
#pragma once
#include <vector>
#include <iostream>

class Matrix 
{
    private:
        std::vector<std::vector<double>> m_data;

    public:
        Matrix(std::vector<std::vector<double>> mat); // constructor
        Matrix(const Matrix& other); // copy constructor
        Matrix(Matrix&& other) noexcept; // move constructor
        Matrix& operator=(const Matrix& other); // copy assigment
        Matrix& operator=(Matrix&& other) noexcept; // move assigment                                   
        ~Matrix(); // destructor
        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

        static Matrix MatMul(const Matrix& left, const Matrix& right);
        std::vector<std::vector<double>> getData() const; 
        double get(int i, int j) const;
        int getNumRows() const;
        int getNumCols() const;
        void set(int i, int j, double val);
};

